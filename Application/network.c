/*
 * lwip_adin1110_adapter.c
 *
 *  Created on: Jan 29, 2025
 *      Author: Lars Andre Landås (landas@gmail.com)
 */

#include "config.h"
#include "network.h"
#include "stm32_spi.h"
#include "stm32_gpio.h"
#include "no_os_alloc.h"
#include "no_os_gpio.h"
#include "no_os_spi.h"
#include "lwip/etharp.h"
#include "lwip/pbuf.h"

#include "FreeRTOS.h"
#include "task.h"

struct netif *adin1110_netif = NULL;
struct adin1110_desc *adin1110_desc = NULL;

struct stm32_gpio_init_param adin1110_reset_gpio_extra_ip = {
	.mode = GPIO_MODE_OUTPUT_OD,
	.speed = GPIO_SPEED_HIGH,
};

struct stm32_spi_init_param adin1110_spi_extra_ip  = {
	.chip_select_port = ADIN1110_SPI_CS_PORT,
};

struct no_os_spi_init_param adin1110_spi_ip = {
	.device_id = ADIN1110_SPI_DEVICE_ID,
	.max_speed_hz = ADIN1110_SPI_CLK_RATE,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = ADIN1110_SPI_OPS,
	.chip_select = ADIN1110_SPI_CS,
	.extra = ADIN1110_SPI_EXTRA,
};


struct no_os_gpio_init_param adin1110_reset_gpio_ip = {
	.port = ADIN1110_GPIO_RESET_PORT,
	.number = ADIN1110_GPIO_RESET_PIN,
	.pull = NO_OS_PULL_UP,
	.platform_ops = ADIN1110_GPIO_OPS,
	.extra = &adin1110_reset_gpio_extra_ip,
};

uint8_t eth_rx_buff[ADIN1110_BUFF_LEN];

err_t adin1110if_init(struct netif *netif) {

	adin1110_desc = adin1110if_setup();
	adin1110_set_promisc(adin1110_desc, 0, true);

	if(adin1110_desc == NULL)
	{
		return -1;
	}

	netif->hwaddr_len = 6U;
	netif->hwaddr[0] = ADIN1110_MAC_0;
	netif->hwaddr[1] = ADIN1110_MAC_1;
	netif->hwaddr[2] = ADIN1110_MAC_2;
	netif->hwaddr[3] = ADIN1110_MAC_3;
	netif->hwaddr[4] = ADIN1110_MAC_4;
	netif->hwaddr[5] = ADIN1110_MAC_5;
	netif->mtu = 1500;
	netif->name[0] = 'e';
	netif->name[1] = 'n';
	netif->num = 1U;
	netif->state = &adin1110if_state_changed;
	netif->output = &etharp_output;
	netif->linkoutput = &adin1110if_link_output;
	netif->flags |= NETIF_FLAG_ETHARP | NETIF_FLAG_BROADCAST;
#if LWIP_NETIF_HOSTNAME
	netif->hostname = "adin1110";
#endif

	return 0;
}

struct adin1110_desc *adin1110if_setup() {

	struct adin1110_desc *adin1110;
	struct adin1110_init_param adin1110_ip = {
		.chip_type = ADIN1110,
		.comm_param = adin1110_spi_ip,
		.reset_param = adin1110_reset_gpio_ip,
		.append_crc = false,
		.mac_address = {
				ADIN1110_MAC_0,
				ADIN1110_MAC_1,
				ADIN1110_MAC_2,
				ADIN1110_MAC_3,
				ADIN1110_MAC_4,
				ADIN1110_MAC_5
		}
	};

	int ret = adin1110_init(&adin1110, &adin1110_ip);

	if(ret != 0) {
		adin1110 = NULL;
	}

	return adin1110;
}

err_t adin1110if_link_output(struct netif *netif, struct pbuf *p)
{
	if(adin1110_desc == NULL)
		return -1;

	struct adin1110_eth_buff eth_buff = {};
	eth_buff.len = p->len; // - ADIN1110_ETH_HDR_LEN;

	memcpy(eth_buff.mac_dest, p->payload, ADIN1110_ETH_ALEN * sizeof(uint8_t));
	memcpy(eth_buff.mac_source, adin1110_desc->mac_address, ADIN1110_ETH_ALEN * sizeof(uint8_t));
	memcpy(eth_buff.ethertype, (const uint8_t *)p->payload + (ADIN1110_ETH_ALEN * sizeof(uint8_t) * 2), 2 * sizeof(uint8_t));

	eth_buff.payload = &((uint8_t*)p->payload)[ADIN1110_ETH_HDR_LEN];

	osStatus status = osMutexWait(adinHandle, osWaitForever);

	if(status == osOK) {
		int ret = adin1110_write_fifo(adin1110_desc, 0, &eth_buff);
		osMutexRelease(adinHandle);
		return ret;
	}
	else {
		return 1;
	}
	return 0;
}

err_t adin1110if_poll(struct netif *netif)
{
	struct adin1110_eth_buff eth_buff = {
			.payload = eth_rx_buff,
			.len = 0
		};

	osStatus status = osMutexWait(adinHandle, osWaitForever);

	if(status == osOK) {
		int read_ret = adin1110_read_fifo(adin1110_desc, 0, &eth_buff);
		osMutexRelease(adinHandle);

		if(read_ret == 0
				&& eth_buff.len > 0) {

			struct pbuf *p = pbuf_alloc(PBUF_RAW_TX, eth_buff.len, PBUF_RAM);

			if(p == NULL) {
				printf("adin1110if_poll: Pbuf allocation failed\r\n");
				return 1;
			}

			memcpy(p->payload, eth_buff.mac_dest, ADIN1110_ETH_ALEN * sizeof(uint8_t));
			memcpy(&((uint8_t*)p->payload)[ADIN1110_ETH_ALEN], eth_buff.mac_source, ADIN1110_ETH_ALEN * sizeof(uint8_t));
			memcpy(&((uint8_t*)p->payload)[ADIN1110_ETH_ALEN*2], eth_buff.ethertype, 2 * sizeof(uint8_t));
			memcpy(&((uint8_t*)p->payload)[ADIN1110_ETH_ALEN*2 + 2], eth_buff.payload, (eth_buff.len - ADIN1110_ETH_HDR_LEN) * sizeof(uint8_t));

			return netif->input(p, netif);
		}
	}
	else {
		return 1;
	}


	return 0;
}


err_t adin1110if_state_changed(struct netif *netif)
{
	//todo: should bring down/reset the adin1110...
	return 0;
}

void adin1110_tcpip_init_done(void *arg)
{
	return;
}

void network_init() {
	adin1110_netif = pvPortMalloc(sizeof(struct netif));

	tcpip_init(&adin1110_tcpip_init_done, NULL);

	//Setting up adin1110
	ip4_addr_t ip;
	IP4_ADDR(&ip,
			ADIN1110_DEFAUL_IP_0,
			ADIN1110_DEFAUL_IP_1,
			ADIN1110_DEFAUL_IP_2,
			ADIN1110_DEFAUL_IP_3);
	ip4_addr_t netmask;
	IP4_ADDR(&netmask,
			ADIN1110_DEFAUL_NETMASK_0,
			ADIN1110_DEFAUL_NETMASK_1,
			ADIN1110_DEFAUL_NETMASK_2,
			ADIN1110_DEFAUL_NETMASK_3);
	ip4_addr_t gw;
	IP4_ADDR(&gw,
			ADIN1110_DEFAUL_GW_0,
			ADIN1110_DEFAUL_GW_1,
			ADIN1110_DEFAUL_GW_2,
			ADIN1110_DEFAUL_GW_3);

	netif_add(adin1110_netif, &ip, &netmask, &gw, NULL, &adin1110if_init, &tcpip_input);
	netif_set_default(adin1110_netif);
	netif_set_up(adin1110_netif);
	netif_set_link_up(adin1110_netif);

	if(ADIN1110_DHCP_ENABLED == 1)
		dhcp_start(adin1110_netif);
}

void adin1110_poll()
{
	adin1110if_poll(adin1110_netif);
}



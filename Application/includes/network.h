/*
 * lwip_adin1110_adapter.h
 *
 *  Created on: Jan 29, 2025
 *      Author: Lars Andre Landås (landas@gmail.com)
 */

#ifndef INC_LWIP_ADIN1110_ADAPTER_H_
#define INC_LWIP_ADIN1110_ADAPTER_H_

#include "network.h"

#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "lwip/dhcp.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/tcp.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
#include "lwip/inet.h"

#include "adin1110.h"
#include "cmsis_os.h"
#include "stm32_spi.h"
#include "stm32_gpio.h"

#define ADIN1110_SPI_CLK_RATE		25000000
#define ADIN1110_GPIO_OPS			&stm32_gpio_ops
#define ADIN1110_SPI_OPS         &stm32_spi_ops
#define ADIN1110_SPI_EXTRA       &adin1110_spi_extra_ip

extern struct stm32_gpio_init_param adin1110_reset_gpio_extra_ip;
extern struct stm32_spi_init_param adin1110_spi_extra_ip;

void network_init(void);
void adin1110_poll(void);

err_t adin1110if_init(struct netif *netif);
struct adin1110_desc *adin1110if_setup();
err_t adin1110if_poll(struct netif *netif);
err_t adin1110if_link_output(struct netif *netif, struct pbuf *p);
err_t adin1110if_state_changed(struct netif *netif);

extern struct netif *adin1110_netif;
extern struct adin1110_desc *adin1110_desc;

extern struct no_os_spi_init_param adin1110_spi_ip;
extern struct no_os_gpio_init_param adin1110_reset_gpio_ip;

extern osMutexId adinHandle;

#endif /* INC_LWIP_ADIN1110_ADAPTER_H_ */

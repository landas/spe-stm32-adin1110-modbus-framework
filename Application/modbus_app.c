/*
 * modbus_app.c
 *
 * Created on: Jun 06, 2025
 * Author: Lars Andre Landås <landas@gmail.com>
 */

#include <modbus.h>
#include "stm32l4xx_hal.h"
#include "config.h"
#include "network.h"
#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <string.h>

uint8_t modbus_read_words_callback(uint8_t function_code, uint8_t data_table_type, uint16_t starting_address, uint16_t quantity_of_registers, uint16_t* data) {

	// implement 16 bit register reads
	return MODBUS_ERROR_OK;
}

uint8_t modbus_write_words_callback(uint8_t function_code, uint8_t data_table_type,uint16_t starting_address, uint16_t quantity_of_registers, uint16_t* data) {

	//implement 16 bit register writes
	return MODBUS_ERROR_OK;
}


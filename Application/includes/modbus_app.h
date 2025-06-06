/*
 * modbus_app.h
 *
 *  Created on: Jun 06, 2025
 *      Author: Lars Andre Landås (landas@gmail.com)
 */

#ifndef INCLUDE_MODBUS_APP_H_
#define INCLUDE_MODBUS_APP_H_

#include "modbus_app.h"

#define DAY_IN_SECONDS 86400
#define HOUR_IN_SECONDS 3600
#define MINUTE_IN_SECONDS 60

uint8_t modbus_read_words_callback(uint8_t function_code, uint8_t data_table_type,uint16_t starting_address, uint16_t quiantity_of_registers, uint16_t* data);
uint8_t modbus_write_words_callback(uint8_t function_code, uint8_t data_table_type,uint16_t starting_address, uint16_t quiantity_of_registers, uint16_t* data);

#endif /* INCLUDE_MODBUS_APP_H_ */

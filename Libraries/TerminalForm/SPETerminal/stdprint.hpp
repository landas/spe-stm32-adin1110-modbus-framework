#pragma once

#include "memory.hpp"
#include "stm32l4xx_hal.h"

extern UART_HandleTypeDef huart2;


namespace speterminal {
	inline static void std_print(const std::string& s) {
		HAL_UART_Transmit(&huart2, (uint8_t*)s.c_str(), s.size(), HAL_MAX_DELAY);
	}
	//inline static void std_print(const std::string& s) { std::cout << s << std::flush; }
}

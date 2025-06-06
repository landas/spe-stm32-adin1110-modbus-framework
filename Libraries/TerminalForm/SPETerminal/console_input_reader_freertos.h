#pragma once

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32l4xx_hal.h"
#include "memory.hpp"
#include "../TermForm/console_input_reader.h"
#include "../TermForm/tools.h"
#include <string>
#include <cstring>

extern UART_HandleTypeDef huart1;

namespace termform   {
	class console_input_reader_freertos : public console_input_reader {
	public:
		int16_t operator()() override {
			osDelay(1000);
			//int16_t key = static_cast<int16_t>(80);

			std::string str = this->read_uart();
			int16_t key = str.c_str()[0];


			if (key == '\033') {
                if (str == "\033[A")
                    key = termform::keycode.arrow_up;
                else if (str == "\033[B")
                    key = termform::keycode.arrow_down;
                else if (str == "\033[C")
                    key = termform::keycode.arrow_right;
                else if (str == "\033[D")
                    key = termform::keycode.arrow_left;
                else
                    key = 0;
            }
			else if(key == 'a') {
				key = termform::keycode.arrow_down;
			}
            return key;
		};
	private:
		std::string read_uart() {

			const uint8_t input_buffer_size = 10;
			uint8_t input_buffer[input_buffer_size];

			memset(input_buffer, '\0', input_buffer_size);
			HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, input_buffer, input_buffer_size, 1000);

			if(status == HAL_OK || (status == HAL_TIMEOUT && input_buffer[0] != '\0')) {
				HAL_UART_Transmit(&huart1, (uint8_t*)&input_buffer[1], input_buffer_size-1, HAL_MAX_DELAY);
				return std::string(reinterpret_cast<const char*>(input_buffer));
				/*
				for(int i = 0; i < input_buffer_size && input_buffer[i] != '\0'; ++i) {
					return input_buffer[i];
				}
				*/
			}

			return std::string("");
		}

	};
}

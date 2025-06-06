#pragma once

#include "memory.hpp"
#include <conio.h>
#include "console_input_reader.h"
#include "tools.h"


namespace termform   {
	class console_input_reader_windows : public console_input_reader {
	public:
		int16_t operator()() override {
            int16_t key = static_cast<int16_t>(_getch());

            if (key == 224) {
                key = static_cast<int16_t>(_getch());
                if (key == 72)
                    key = termform::keycode.arrow_up;
                else if (key == 80)
                    key = termform::keycode.arrow_down;
                else if (key == 75)
                    key = termform::keycode.arrow_left;
                else if (key == 77)
                    key = termform::keycode.arrow_right;
                else
                    key = 0;
            }
            return key;
		};
	};
}

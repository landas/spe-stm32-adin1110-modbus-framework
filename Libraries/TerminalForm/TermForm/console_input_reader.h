#pragma once

#include "memory.hpp"
#include <cstdint>

namespace termform {
	class console_input_reader {
	public:
		console_input_reader() = default;
		virtual ~console_input_reader() = default;
		virtual int16_t operator()() = 0;
	};
}

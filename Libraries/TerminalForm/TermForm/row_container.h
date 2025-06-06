#pragma once

#include "memory.hpp"
#include <memory>
#include <iostream>
#include "container.h"
#include "control.h"

// std::shared_ptr<T>

namespace termform {

	class row_container : public container {
	
	protected:
	
	public:
		paint_return paint(uint16_t x, uint16_t y, bool force) override {
			std::string str{};
			uint16_t y_pos = y;
			for (const auto& c : _components) {
				bool is_invalid = c->invalid();
				auto ret = c->paint(x, y_pos, force);

				if (is_invalid || force)
				{
					if (!c->is_container()) {
						//y_pos -= 1;
						std::string str_plus_padding = ret.string;
						//str_plus_padding.append(_width - ret.width, ' ');
						str += ansi_escape_code::get(x, y_pos, c->get_paint_color(), c->get_paint_background(), str_plus_padding);
					}
					else {
						str += ret.string;
					}
				}
				y_pos += ret.height;
			}
			return { x,static_cast<uint16_t>(y_pos - y), str };
		}
	};
}

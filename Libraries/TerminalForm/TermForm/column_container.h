#pragma once

#include "memory.hpp"
#include <memory>
#include <iostream>
#include "container.h"
#include "control.h"


namespace termform {

	class column_container : public container {

	protected:

	public:
		paint_return paint(uint16_t x, uint16_t y, bool force) override {
			std::string str{};
			uint16_t x_pos = x;
			for (const auto& c : _components) {
				auto ret = c->paint(x_pos, y, force);
				
				if (invalid() || force)
				{
					if (!c->is_container()) {
						std::string str_plus_padding = ret.string;
						str += ansi_escape_code::get(x_pos, y, c->get_paint_color(), c->get_paint_background(), str_plus_padding);
					}
					else {
						str += ret.string;
					}
					
					x_pos += ret.width;
					
					if (padding_right() > 0) {
						str += ansi_escape_code::get(x_pos, y, this->get_paint_color(), this->get_paint_background(), std::string(padding_right(), ' '));
					}

					x_pos += padding_right();
				}
				else {
					x_pos += static_cast<uint16_t>(ret.width + padding_right());
				}
			}

			return { 1 , static_cast<uint16_t>(x_pos - x), str };
		}

		void padding_right(char padding_right) {
			_padding_right = padding_right;
		}

		char padding_right() const {
			return _padding_right;
		}

		bool input(int chr) override {
			if (!_cursor->input(chr)) {
				switch (chr) {
				case keycode.arrow_left:
					move_cursor_to_prev();
					return true;
				case keycode.arrow_right:
					move_cursor_to_next();
					return true;
				default:
					break;
				}

				return false;
			}
			return true;
		}

	private:
		char _padding_right{ 0 };
	};
}

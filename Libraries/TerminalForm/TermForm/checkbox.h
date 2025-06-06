#pragma once

#include "memory.hpp"
#include "component.h"
#include "control.h"

namespace termform {

	class checkbox : public control {

	public:
		checkbox() : control() {
			_focusable = true;
		}

		inline void on_text_change(const std::string& value) override {
			auto size = string_boxsize("[X] " + value);
			_text = value;
			_width = size.width;
			_height = size.height;
		}

		inline bool checked() const {
			return _checked;
		}

		void checked(bool checked) {
			if (_checked != checked) {
				_checked = checked;
				trigger_change();
			}
		}

		bool input(int c) override {
			if (c == 32 || c == 13) {
				checked(!checked());
				invalid(true);
				return true;
			}
			return false;
		}

		paint_return paint(uint16_t x, uint16_t y, bool force) override {
			invalid(false);
			return { _width, _height, control::concat_string(_checked ? "[X] " : "[ ] ", "") };
		}

	private:
		bool _checked{ false };

	};
}

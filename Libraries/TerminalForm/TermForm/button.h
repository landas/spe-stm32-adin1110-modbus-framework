#pragma once

#include "memory.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "tools.h"
#include "ansi_escape_codes.h"
#include "component.h"
#include "control.h"


namespace termform {

	class button : public control {
	protected:
		event_handler* enter_handler{ nullptr };

	public:

		button() : control() {
			_focusable = true;
		}

		ansi_escape_code::color color_selected() const {
			return _color_selected;
		}

		void color_selected(ansi_escape_code::color color) {
			_color_selected = color;
		}
		
		ansi_escape_code::background background_selected() const {
			return _background_selected;
		}

		void background_selected(ansi_escape_code::background background) {
			_background_selected = background;
		}

		ansi_escape_code::color color_selected()
		{
			return _color_selected;
		}

		bool input(int c) override {
			if (c == 13) {
				on_enter();
				return true;
			}
			return false;
		}

		void set_on_enter(event_handler h) {
			enter_handler = h;
		}

		void on_enter() {
			if (enter_handler != nullptr) {
				enter_handler(*this);
			}
		}

	};
}

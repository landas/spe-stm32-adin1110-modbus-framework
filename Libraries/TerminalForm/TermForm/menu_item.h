#pragma once
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

	class menu_item : public control {
	protected:
		std::vector<event_handler> enter_handlers;
		ANSIEscapeCode::color _color_selected{ ANSIEscapeCode::color::black };
		ANSIEscapeCode::background _background_selected{ ANSIEscapeCode::background::white };

	public:

		menu_item() : control() {
			_focusable = true;
		}

		std::string text() {
			return _text;
		}

		void text(const std::string& value) {
			_text = value;
		}

		void text(std::string&& value) {
			_text = std::move(value);
		}

		ANSIEscapeCode::color color_selected() const {
			return _color_selected;
		}

		void color_selected(ANSIEscapeCode::color color) {
			_color_selected = color;
		}
		
		ANSIEscapeCode::background background_selected() const {
			return _background_selected;
		}

		void background_selected(ANSIEscapeCode::background background) {
			_background_selected = background;
		}

		ANSIEscapeCode::color color_selected()
		{
			return _color_selected;
		}

		std::string display() const override {
			if (_has_focus) {
				return ANSIEscapeCode::get(_color_selected) + ANSIEscapeCode::get(_background_selected) + "[ " + _text + " ]";
			}
	
			return control::display("[ ", " ]");
		}

		bool input(int) override {
			return false;
		}

		void enter(event_handler handler) {
			enter_handlers.push_back(handler);
		}

		void on_enter() {
			for (auto& handler : enter_handlers) {
				handler();
			}
		}

	};
}

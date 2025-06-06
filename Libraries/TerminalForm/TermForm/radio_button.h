#pragma once

#include "memory.hpp"
#include <vector>
#include <iostream>
#include "component.h"
#include "control.h"

namespace termform {

	class radio_button : public control {

	public:
		radio_button(const std::string& group) : control() {
			_focusable = true;
			_group_hash = string_hash_16(group);

			if (!group_has_selected()) {
				_selected = true;
			}

			_radio_buttons.push_back(this);
		}

		// Copy Constructor
		radio_button(const radio_button& other) {
			_focusable = true;
			_group_hash = other._group_hash;
			_flags = other._flags;
			_background = other._background;
			_background_selected = other._background_selected;
			_color = other._color;
			_color_selected = other._color_selected;
			_height = other._height;
			_width = other._width;
			_x = other._x;
			_y = other._y;
			_text = other._text;
			_selected = other._selected;
			_on_change = other._on_change;
			_on_focus = other._on_focus;
			_on_leave = other._on_leave;
			_on_input = other._on_input;
			_radio_buttons.push_back(this);
		}

		// Copy Assignment Operator
		radio_button& operator=(const radio_button& other) {
			_focusable = true;
			_group_hash = other._group_hash;
			_flags = other._flags;
			_background = other._background;
			_background_selected = other._background_selected;
			_color = other._color;
			_color_selected = other._color_selected;
			_height = other._height;
			_width = other._width;
			_x = other._x;
			_y = other._y;
			_text = other._text;
			_selected = other._selected;
			_on_change = other._on_change;
			_on_focus = other._on_focus;
			_on_leave = other._on_leave;
			_on_input = other._on_input;
			return *this;
		}

		// Move Constructor (defaults to copy)
		//radio_button(radio_button&& other) noexcept { }

		// Move Assignment Operator (defaults to copy)
		//radio_button& operator=(radio_button&& other) noexcept { }

		~radio_button() {
			auto it = std::find(_radio_buttons.begin(), _radio_buttons.end(), this);
			if (it != _radio_buttons.end()) {
				_radio_buttons.erase(it);
			}
		}

		inline std::string label() {
			return text();
		}

		inline void label(const std::string& label) {
			text(label);
		}

		inline void on_text_change(const std::string& value) override {
			auto size = string_boxsize("(o) " + value);
			_text = value;
			_width = size.width;
			_height = size.height;
		}

		radio_button* get_selected() {
			for (const auto& e : _radio_buttons) {
				if (e->_group_hash == _group_hash && e->is_selected()) {
					return e;
				}
			}
			return nullptr;
		}

		inline bool is_selected() const {
			return _selected;
		}

		inline void set_selected(bool selected) {
			if (_selected != selected) {
				_selected = selected;
				invalid(true);
			}
		}

		void select() {
			if (!_selected) {
				auto prev_selected = get_selected();
				if (prev_selected != nullptr) {
					prev_selected->set_selected(false);
					prev_selected->trigger_change();
				}

				set_selected(true);
				trigger_change();
			}
		}

		bool input(int c) override {
			if (c == 32 || c == 13) {
				select();
				return true;
			}
			return false;
		}

		paint_return paint(uint16_t x, uint16_t y, bool force) override {
			invalid(false);
			return { _width, _height, control::concat_string(is_selected() ? "(o) " : "( ) ", "")};
		}

	private:

		bool group_has_selected() {
			for (const auto& e : _radio_buttons) {
				if (e->_group_hash == _group_hash && e->is_selected()) {
					return true;
				}
			}
			return false;
		}

	private:
		static std::vector<radio_button*> _radio_buttons;
		uint16_t _group_hash{ 0 };
		bool _selected{ false };
	};
}

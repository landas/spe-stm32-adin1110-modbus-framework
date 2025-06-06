#pragma once

#include "memory.hpp"
#include "component.h"
#include "control.h"
#include <iostream>

namespace termform {

	// todo: if max_length > width, scroll within textbox... (need cursor position)

	class textfield : public control {

	public:
		textfield(int16_t input_width, const std::string& text, int16_t max_length) : _max_length(max_length) {
			_input_width = _width = input_width;
			_text = text;
			_height = 1;
			_focusable = true;
		}

		textfield(int16_t width, const std::string& string) : textfield(width, string, 0) { }
		textfield(int16_t width) : textfield(width, "", 0) { }
		textfield() : textfield(10, "", 0) { }

		bool input(int c) override {

			if (c > 255) {
				return false;
			}

			auto ch = static_cast<char>(c);
			if (ch == 8 && _text.size() > 0) {
				_text.erase(_text.size() - 1);
				invalid(true);
				return true;
			}
			else if ( (_max_length == 0 || _max_length > _text.length())
				&& ((_allowed_characters.size() == 0 && is_allowed_characters_standard(ch)) || _allowed_characters.find(ch) != std::string::npos)
			) {
				_text += ch;
				invalid(true);
				return true;
			}
			return false;
		}

		inline std::string allowed_characters() const {
			return _allowed_characters;
		}

		inline void allowed_characters(const std::string& allowed_characters) {
			_allowed_characters = allowed_characters;
		}

		inline void max_length(int16_t max_length) {
			_max_length = max_length;
		}

		inline int16_t max_length() const {
			return _max_length;
		}
		
		inline std::string label() const {
			return _label;
		}

		inline void label(const std::string& label) {
			if (label != _label) {
				_label = label;
				_width = static_cast<uint16_t>(_input_width + (_label.size() == 0 ? 0 : label.size() + 2));
				invalid(true);
			}
		}

		paint_return paint(uint16_t x, uint16_t y, bool force) override {
			std::string str{};

			if (_label.size() != 0) {
				str += _label + ": ";
			}
			
			str += "_" + _text;
			
			for (int16_t pos = static_cast<int16_t>(_text.size()); pos <= _input_width; ++pos) {
				str += '_';
			}

			invalid(false);
			
			return { _width, _height, str };
		}

	private:
		bool is_allowed_characters_standard(char c) {
			if ((c >= 32 && c <= 126)
				|| (c >= 128 && c <= 169)
				|| (c >= 181 && c <= 183)
				|| (c >= 198 && c <= 199)
				|| (c >= 224 && c <= 237)
				)
				return true;

			return false;
		}

	private:
		std::string _label{};
		std::string _allowed_characters{};
		uint16_t _input_width{ 0 };
		uint16_t _max_length{ 0 };
	};
}

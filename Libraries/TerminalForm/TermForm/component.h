#pragma once

#include "memory.hpp"
#include "tools.h"
#include "paint_return.h"

#include "ansi_escape_codes.h"

namespace termform {

	class form;
	class container;

	class component {

	public:
		virtual ~component() = default;
		virtual paint_return paint(uint16_t x, uint16_t y, bool force) = 0;
		virtual bool input(int) = 0;
		virtual form* get_form() const = 0;

		inline int16_t x() const {
			return _x;
		}

		inline int16_t y() const {
			return _y;
		}
		
		inline int16_t width() const {
			return _width;
		}

		inline void width(int16_t width) {
			_width = width;
		}
		
		inline int16_t height() const {
			return _height;
		}

		inline void height(int16_t height) {
			_height = height;
		}

		inline void x(int x) {
			_x = x;
		}

		inline void y(int y) {
			_y = y;
		}

		inline bool has_focus() const {
			return _has_focus;
		}
		
		inline bool invalid() const {
			return _invalid;
		}

		inline bool is_container() const {
			return _is_container;
		}

		void invalid(bool invalid);

		virtual bool try_give_focus() {
			if (_focusable) {
				if (!_has_focus) {
					_has_focus = true;
					invalid(true);
					trigger_focus();
				}
				return true;
			}

			return false;
		}

		virtual bool try_give_focus_back() {
			return try_give_focus();
		}

		virtual void release_focus() {
			if (_has_focus) {
				_has_focus = false;
				invalid(true);
				trigger_leave();
			}
		}

		void set_on_focus(event_handler h) {
			_on_focus = h;
		}
		
		void set_on_leave(event_handler h) {
			_on_leave = h;
		}		
		
		void set_on_input(input_event_handler h) {
			_on_input = h;
		}
		
		container* parent() const {
			return _parent;
		}

		ansi_escape_code::color get_paint_color() const {
			if (has_focus()) {
				return _color_selected;
			}
			return _color;
		}

		ansi_escape_code::background get_paint_background() const {
			if (has_focus()) {
				return _background_selected;
			}
			return _background;
		}

	protected:

		void handle_input(int c) {
			if (trigger_input(c)) {
				return;
			}

			input(c);
		}

		bool trigger_focus() {
			if (_on_focus != nullptr) {
				return _on_focus(*this);
			}
			return false;
		}
		
		bool trigger_leave() {
			if (_on_leave != nullptr) {
				return _on_leave(*this);
			}
			return false;
		}

		bool trigger_input(int c) {
			if (_on_input != nullptr) {
				return _on_input(*this, c);
			}
			return false;
		}

		inline void parent(container* parent) {
			_parent = parent;
		}

	protected:
		// event handlers
		event_handler* _on_focus{ nullptr };
		event_handler* _on_leave{ nullptr };
		input_event_handler* _on_input{ nullptr }; 
		
		container* _parent{ nullptr };
		
		uint16_t _x{ 0 };
		uint16_t _y{ 0 };
		uint16_t _width{ 1 };
		uint16_t _height{ 1 };
		
		union {
			char _flags{ 4 };
			struct {
				bool _focusable : 1;
				bool _has_focus : 1;
				bool _invalid : 1;
				bool _is_container : 1;
				char : 4;
			};
		};
		
		ansi_escape_code::color _color{ ansi_escape_code::color::standard };
		ansi_escape_code::background _background{ ansi_escape_code::background::standard };
		ansi_escape_code::color _color_selected{ ansi_escape_code::color::black };
		ansi_escape_code::background _background_selected{ ansi_escape_code::background::white };

	};
}

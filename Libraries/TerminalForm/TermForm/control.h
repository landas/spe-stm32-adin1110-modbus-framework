#pragma once

#include "memory.hpp"
#include "component.h"
#include "container.h"
#include "tools.h"

namespace termform {

	class control : public component {
	protected:
		std::string _text{ };
		event_handler* _on_change{ nullptr };

	public:
		
		inline paint_return paint(uint16_t x, uint16_t y, bool force) override {
			auto size = string_boxsize(_text);
			invalid(false);
			return { size.width, size.height, _text };
		}
		
		inline std::string concat_string(std::string front, std::string back) const {
			return front + _text + back;
		}

		std::string text() {
			return _text;
		}

		void text(const std::string& value) {
			if (_text != value) {
				auto size = string_boxsize(value);
				width(size.width);
				height(size.height);
				on_text_change(value);
			}
		}

		inline void set_on_change(event_handler* h) {
			_on_change = h;
		}

		bool input(int) override {
			return false;
		}	

		form* get_form() const override {
			auto p = parent();
			if (p != nullptr) {
				return p->get_form();
			}
			return nullptr;
		}

	protected:
		bool trigger_change() {
			if (_on_change != nullptr) {
				return _on_change(*this);
			}
			return false;
		}

		virtual void on_text_change(const std::string& value)
		{
			_text = value;
			_width = static_cast<uint16_t>(_text.length() - ansi_escape_code::metadata_lenght(_text));
			_height = static_cast<uint16_t>(ansi_escape_code::count_newlines(_text) + 1);
			trigger_change();
		}

	friend class container;
	};
}


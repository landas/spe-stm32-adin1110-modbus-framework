#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class status_menu {
	public:
		status_menu(uint16_t width) {
			container_menu = form::make_container<row_container>();
			container_menu->width(width);

			menu_heading = form::make_control<label>();
			menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold) +
				"Status:" +
				ansi_escape_code::get(ansi_escape_code::format::reset) + "\n\nNothing here at the moment\n");
			container_menu->add(menu_heading);

			container_save_discard = form::make_container<column_container>();
			container_save_discard->padding_right(4);

			button_ok = form::make_control<button>();
			button_ok->text("OK");
			button_ok->set_on_enter(&ok_callback);
			container_save_discard->add(button_ok);



			container_menu->add(container_save_discard);
		}

		inline std::shared_ptr<row_container> get() {
			return container_menu;
		}

		static bool ok_callback(termform::component& c);

	private:
		std::shared_ptr<row_container> container_menu{};
		std::shared_ptr<label> menu_heading{};

		std::shared_ptr<column_container> container_save_discard{};
		std::shared_ptr<button> button_ok{};
	};
}

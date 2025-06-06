#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class mqtt_setting_menu {
	public:
		mqtt_setting_menu(uint16_t width) {
			container_menu = form::make_container<row_container>();
			container_menu->width(width);

			menu_heading = form::make_control<label>();
			menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold) + 
				"MQTT SETTINGS:" + 
				ansi_escape_code::get(ansi_escape_code::format::reset) + "\n\nNo options at the moment\n");
			container_menu->add(menu_heading);

			container_save_discard = form::make_container<column_container>();
			container_save_discard->padding_right(4);

			button_save = form::make_control<button>();
			button_save->text("Save");
			button_save->set_on_enter(&save_callback);
			container_save_discard->add(button_save);

			button_dicard = form::make_control<button>();
			button_dicard->text("Discard");
			button_dicard->set_on_enter(&save_callback);
			container_save_discard->add(button_dicard);

			container_menu->add(container_save_discard);
		}

		inline std::shared_ptr<row_container> get() {
			return container_menu;
		}

		static bool save_callback(termform::component& c);

	private:
		std::shared_ptr<row_container> container_menu{};
		std::shared_ptr<label> menu_heading{};

		std::shared_ptr<column_container> container_save_discard{};
		std::shared_ptr<button> button_save{};
		std::shared_ptr<button> button_dicard{};
	};
}

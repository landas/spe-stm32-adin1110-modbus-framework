#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class ssh_setting_menu {
	public:
		ssh_setting_menu(uint16_t width) {
			container_menu = form::make_container<row_container>();
			container_menu->width(width);

			menu_heading = form::make_control<label>();
			menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold)+ 
				"SSH SETTINGS:" + 
				ansi_escape_code::get(ansi_escape_code::format::reset));
			container_menu->add(menu_heading);

			option_disable = form::make_control<radio_button>("enable_disable");
			option_disable->text("Disable");
			container_menu->add(option_disable);

			option_enable = form::make_control<radio_button>("enable_disable");
			option_enable->text("Enable");
			container_menu->add(option_enable);

			textfield_port = form::make_control<textfield>(5, "22", 5);
			textfield_port->label("    Port");
			textfield_port->allowed_characters("0123456789");
			container_menu->add(textfield_port);

			textfield_username = form::make_control<textfield>(32, "", 32);
			textfield_username->label("    Username");
			container_menu->add(textfield_username);

			textfield_password = form::make_control<textfield>(32, "", 32);
			textfield_password->label("    Password");
			container_menu->add(textfield_password);

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

		std::shared_ptr<radio_button> option_enable{};
		std::shared_ptr<radio_button> option_disable{};
		std::shared_ptr<textfield> textfield_port{};
		std::shared_ptr<textfield> textfield_username{};
		std::shared_ptr<textfield> textfield_password{};

		std::shared_ptr<column_container> container_save_discard{};
		std::shared_ptr<button> button_save{};
		std::shared_ptr<button> button_dicard{};
	};
}

#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class network_setting_menu {
	public:
		network_setting_menu(uint16_t width) {
			container_menu = form::make_container<row_container>();
			container_menu->width(width);

			menu_heading = form::make_control<label>();
			menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold) + "NETWORK SETTINGS:" + ansi_escape_code::get(ansi_escape_code::format::reset));
			container_menu->add(menu_heading);

			option_dhcp = form::make_control<radio_button>("dhcp_static");
			option_dhcp->text("DHCP");
			container_menu->add(option_dhcp);

			option_static = form::make_control<radio_button>("dhcp_static");
			option_static->text("Static");
			container_menu->add(option_static);

			textfield_ip = form::make_control<textfield>(15, "0.0.0.0", 15);
			textfield_ip->label("    IP-address");
			textfield_ip->allowed_characters("0123456789.");
			container_menu->add(textfield_ip);

			textfield_subnet = form::make_control<textfield>(15, "0.0.0.0", 15);
			textfield_subnet->label("    Subnet mask");
			textfield_subnet->allowed_characters("0123456789.");
			container_menu->add(textfield_subnet);

			textfield_gateway = form::make_control<textfield>(15, "0.0.0.0", 15);
			textfield_gateway->label("    Gateway");
			textfield_gateway->allowed_characters("0123456789.");
			container_menu->add(textfield_gateway);

			textfield_hostname = form::make_control<textfield>(32, "", 32);
			textfield_hostname->label("    Hostname");
			container_menu->add(textfield_hostname);

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
		std::shared_ptr<radio_button> option_dhcp{};
		std::shared_ptr<radio_button> option_static{};

		std::shared_ptr<textfield> textfield_ip{};
		std::shared_ptr<textfield> textfield_subnet{};
		std::shared_ptr<textfield> textfield_gateway{};
		std::shared_ptr<textfield> textfield_hostname{};

		std::shared_ptr<column_container> container_save_discard{};
		std::shared_ptr<button> button_save{};
		std::shared_ptr<button> button_dicard{};
	};
}

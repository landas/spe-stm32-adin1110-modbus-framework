#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class main_menu {
	public:
		main_menu(uint16_t width) {
			container_main_menu = form::make_container<row_container>();
			container_main_menu->width(width);

			main_menu_heading = form::make_control<label>();
			main_menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold) + 
				"SPE SETTINGS MENU:" +
				ansi_escape_code::get(ansi_escape_code::format::reset));
			container_main_menu->add(main_menu_heading);

			menu_item_network_settings = form::make_control<button>();
			menu_item_network_settings->text("Network  (TCP/IP)");
			menu_item_network_settings->set_on_enter(&network_menu_callback);
			container_main_menu->add(menu_item_network_settings);

			menu_item_mqtt_settings = form::make_control<button>();
			menu_item_mqtt_settings->text("MQTT Server");
			menu_item_mqtt_settings->set_on_enter(&mqtt_menu_callback);
			container_main_menu->add(menu_item_mqtt_settings);

			menu_item_ssh_settings = form::make_control<button>();
			menu_item_ssh_settings->text("SSH Server");
			menu_item_ssh_settings->set_on_enter(&ssh_menu_callback);
			container_main_menu->add(menu_item_ssh_settings);

			menu_item_process_control_settings = form::make_control<button>();
			menu_item_process_control_settings->text("Process control");
			menu_item_process_control_settings->set_on_enter(&process_control_menu_callback);
			container_main_menu->add(menu_item_process_control_settings);
			
			menu_item_status = form::make_control<button>();
			menu_item_status->text("Status");
			menu_item_status->set_on_enter(&status_menu_callback);
			container_main_menu->add(menu_item_status);
			
			menu_item_quit = form::make_control<button>();
			menu_item_quit->text("Quit");
			menu_item_quit->set_on_enter(&quit_callback);
			container_main_menu->add(menu_item_quit);
		}

		inline std::shared_ptr<row_container> get() {
			return container_main_menu;
		}

	private:
		static bool network_menu_callback(termform::component& c);
		static bool mqtt_menu_callback(termform::component& c);
		static bool ssh_menu_callback(termform::component& c);
		static bool process_control_menu_callback(termform::component& c);
		static bool status_menu_callback(termform::component& c);

		static bool quit_callback(termform::component& c) {
			auto f = c.get_form();

			if (f != nullptr) {
				f->quit();
				return true;
			}

			return false;
		}

	private:
		std::shared_ptr<row_container> container_main_menu{};
		std::shared_ptr<label> main_menu_heading{};
		std::shared_ptr<button> menu_item_network_settings{};
		std::shared_ptr<button> menu_item_mqtt_settings{};
		std::shared_ptr<button> menu_item_ssh_settings{};
		std::shared_ptr<button> menu_item_process_control_settings{};
		std::shared_ptr<button> menu_item_status{};
		std::shared_ptr<button> menu_item_quit{};
	};
}

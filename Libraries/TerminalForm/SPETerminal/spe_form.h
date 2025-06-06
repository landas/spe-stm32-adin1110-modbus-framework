#pragma once

#include "memory.hpp"
#include <memory>
#include "../TermForm/form.h"
#include "console_input_reader_freertos.h"
#include "main_menu.h"
#include "network_setting_menu.h"
#include "mqtt_setting_menu.h"
#include "ssh_setting_menu.h"
#include "process_control_setting_menu.h"
#include "status_menu.h"
#include "stdprint.hpp"

#include "FreeRTOS.h"
#include "task.h"

namespace speterminal {
	
	using namespace termform;


	class spe_form  {

	public:
		/*
		spe_form(uint16_t width, uint16_t height, print_function* print) : _termform(width, height, print), container_main_menu(width){
			_termform.set(container_main_menu.get());
		}
		*/

		static void show(uint16_t width, uint16_t height, print_function* print) {
			_termform = std::make_unique<form>(width, height, print);

			change_to_main_menu();

			std::string test{};
			termform::console_input_reader_freertos input_reader{};
			
			while (true) {
				_termform->paint();

				int16_t key = input_reader();

				test = std::to_string(key) + " - Memory: " + std::to_string(xPortGetFreeHeapSize()) + " bytes.";
				_termform->status(test);

				_termform->input(key);

				if (_termform->is_quitting()) {
					std::cout << termform::ansi_escape_code::get_clear_all();
					break;
				}
			}
		}

		static void change_to_main_menu() {
			change_to_clean_up();
			_container_main_menu = std::make_unique<main_menu>(_termform->width());
			_termform->set(_container_main_menu->get());
		}

		static void change_to_network_menu() {
			change_to_clean_up();
			_container_network_menu = std::make_unique<network_setting_menu>(_termform->width());
			_termform->set(_container_network_menu->get());
		}		
		
		static void change_to_mqtt_menu() {
			change_to_clean_up();
			_container_mqtt_menu = std::make_unique<mqtt_setting_menu>(_termform->width());
			_termform->set(_container_mqtt_menu->get());
		}		
		
		static void change_to_ssh_menu() {
			change_to_clean_up();
			_container_ssh_menu = std::make_unique<ssh_setting_menu>(_termform->width());
			_termform->set(_container_ssh_menu->get());
		}
		
		static void change_to_process_control_menu() {
			change_to_clean_up();
			_container_process_control_menu = std::make_unique<process_control_setting_menu>(_termform->width());
			_termform->set(_container_process_control_menu->get());
		}
		
		static void change_to_status_menu() {
			change_to_clean_up();
			_container_status_menu = std::make_unique<status_menu>(_termform->width());
			_termform->set(_container_status_menu->get());
		}

		static void change_to_clean_up() {
			_container_main_menu.reset();
			_container_network_menu.reset(); 
			_termform->clear();
		}


	private:
		static std::unique_ptr<form> _termform;
		static std::unique_ptr<main_menu> _container_main_menu;
		static std::unique_ptr<network_setting_menu> _container_network_menu;
		static std::unique_ptr<mqtt_setting_menu> _container_mqtt_menu;
		static std::unique_ptr<ssh_setting_menu> _container_ssh_menu;
		static std::unique_ptr<status_menu> _container_status_menu;
		static std::unique_ptr<process_control_setting_menu> _container_process_control_menu;
	};
}

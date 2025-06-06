#include "main_menu.h"

#include "spe_form.h"

namespace speterminal {
	bool main_menu::network_menu_callback(termform::component& c) {
		spe_form::change_to_network_menu();
		return true;
	}
	bool main_menu::mqtt_menu_callback(termform::component& c) {
		spe_form::change_to_mqtt_menu();
		return true;
	}	
	
	bool main_menu::ssh_menu_callback(termform::component& c) {
		spe_form::change_to_ssh_menu();
		return true;
	}
	
	bool main_menu::process_control_menu_callback(termform::component& c) {
		spe_form::change_to_process_control_menu();
		return true;
	}	
	
	bool main_menu::status_menu_callback(termform::component& c) {
		spe_form::change_to_status_menu();
		return true;
	}
}
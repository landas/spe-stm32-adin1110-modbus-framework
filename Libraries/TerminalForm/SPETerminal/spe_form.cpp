#include "spe_form.h"

namespace speterminal {
	std::unique_ptr<form> spe_form::_termform{ nullptr };
	std::unique_ptr<main_menu> spe_form::_container_main_menu{ nullptr };
	std::unique_ptr<network_setting_menu> spe_form::_container_network_menu{ nullptr };
	std::unique_ptr<mqtt_setting_menu> spe_form::_container_mqtt_menu{ nullptr };
	std::unique_ptr<ssh_setting_menu> spe_form::_container_ssh_menu{ nullptr };
	std::unique_ptr<process_control_setting_menu> spe_form::_container_process_control_menu{ nullptr };
	std::unique_ptr<status_menu> spe_form::_container_status_menu{ nullptr };
}
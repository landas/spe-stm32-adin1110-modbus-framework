#include "network_setting_menu.h"

#include "spe_form.h"

namespace speterminal {
	bool network_setting_menu::save_callback(termform::component& c) {
		//todo: save routines
		spe_form::change_to_main_menu();
		return true;
	}
}
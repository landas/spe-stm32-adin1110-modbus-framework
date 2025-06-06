#include "status_menu.h"

#include "spe_form.h"

namespace speterminal {
	bool status_menu::ok_callback(termform::component& c) {
		spe_form::change_to_main_menu();
		return true;
	}
}
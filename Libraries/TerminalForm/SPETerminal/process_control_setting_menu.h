#pragma once

#include "memory.hpp"
#include "../TermForm/form.h"

namespace speterminal {

	using namespace termform;

	class process_control_setting_menu {
	public:
		process_control_setting_menu(uint16_t width);

		inline std::shared_ptr<row_container> get() {
			return container_menu;
		}

		static bool save_callback(termform::component& c);

	private:
		std::shared_ptr<row_container> container_menu{};
		std::shared_ptr<label> menu_heading{};

		std::shared_ptr<radio_button> option_raw{};
		std::shared_ptr<radio_button> option_simulated{};
		std::shared_ptr<radio_button> option_calculated{};
		
		std::shared_ptr<label> label_calculated{};
		std::shared_ptr<textfield> textfield_equation{};
		std::shared_ptr<textfield> textfield_unit{};

		std::shared_ptr<column_container> container_save_discard{};
		std::shared_ptr<button> button_save{};
		std::shared_ptr<button> button_dicard{};
	};
}

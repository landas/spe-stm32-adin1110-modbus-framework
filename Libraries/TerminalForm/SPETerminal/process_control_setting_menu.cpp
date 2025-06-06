#include "process_control_setting_menu.h"

#include "spe_form.h"

namespace speterminal {

	process_control_setting_menu::process_control_setting_menu(uint16_t width) {
		container_menu = form::make_container<row_container>();
		container_menu->width(width);

		menu_heading = form::make_control<label>();
		menu_heading->text(ansi_escape_code::get(ansi_escape_code::format::bold) +
			"PROCESS CONTROL SETTINGS:" +
			ansi_escape_code::get(ansi_escape_code::format::reset));
		container_menu->add(menu_heading);

		option_raw = form::make_control<radio_button>("rsc");
		option_raw->text("Output 4 - 20 mA");
		container_menu->add(option_raw);

		option_simulated = form::make_control<radio_button>("rsc");
		option_simulated->text("Simulated data (sine wave)");
		container_menu->add(option_simulated);

		option_calculated = form::make_control<radio_button>("rsc");
		option_calculated->text("Calculated data (equation)");
		container_menu->add(option_calculated);

		label_calculated = form::make_control<label>();
		label_calculated->text("    Use variable x for 4 -20 mA input signal");
		container_menu->add(label_calculated);

		textfield_equation = form::make_control<textfield>(32, "", 32);
		textfield_equation->label("    Equation");
		container_menu->add(textfield_equation);

		textfield_unit = form::make_control<textfield>(10, "", 10);
		textfield_unit->label("        Unit");
		container_menu->add(textfield_unit);

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

	bool process_control_setting_menu::save_callback(termform::component& c) {
		//todo: save routines
		spe_form::change_to_main_menu();
		return true;
	}
}

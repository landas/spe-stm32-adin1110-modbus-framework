#include "spe_terminal_task.hpp"
#include "spe_form.h"
#include "stdprint.hpp"

void spe_terminal_task()
{
    int width = 100;
    int height = 100;
	speterminal::spe_form::show(width, height, &speterminal::std_print);
}

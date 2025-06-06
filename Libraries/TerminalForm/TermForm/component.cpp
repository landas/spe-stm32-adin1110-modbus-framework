#include "component.h"
#include "container.h"

namespace termform {
	
	void component::invalid(bool invalid) {
		_invalid = invalid;
		
		if (invalid && _parent != nullptr) {
			_parent->invalid(true);
		}
	}
	
}
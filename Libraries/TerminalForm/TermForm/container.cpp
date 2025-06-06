#include "container.h"
#include "form.h"

namespace termform {
	bool container::input(int chr) {
		if (!_cursor->input(chr)) {
			switch (chr) {
			case keycode.arrow_down:
				move_cursor_to_next();
				return true;
			case keycode.arrow_up:
				move_cursor_to_prev();
				return true;
			case keycode.arrow_left:
			case keycode.arrow_right:
			default:
				break;

			}

			return false;
		}
		return true;
	}

	bool container::try_give_focus() {
		if (_cursor != nullptr)
			_cursor->release_focus();

		for (auto& e : _components) {
			if (e->try_give_focus())
			{
				_cursor = e;
				return true;
			}
		}
		return false;
	}	
	
	bool container::try_give_focus_back() {
		if (_cursor != nullptr)
			_cursor->release_focus();

		for (auto it = _components.rbegin(); it != _components.rend(); ++it) {
			if ((*it)->try_give_focus_back()) {
				_cursor = *it;
				return true;
			}
		}

		return false;
	}


	bool container::move_cursor_to_next() {
		if(_cursor != nullptr) 
			_cursor->release_focus();

		auto it = std::find(_components.begin(), _components.end(), _cursor);
		if (it != _components.end())
		{
			++it;
			while (it != _components.end())
			{
				if ((*it)->try_give_focus()) {
					_cursor = *it;
					return true;
				}
				++it;
			}
		}

		if (_parent != nullptr) {
			if (_parent->move_cursor_to_next()) {
				return true;
			}
		}

		return try_give_focus();
	}

	bool container::move_cursor_to_prev() {
		if (_cursor != nullptr)
			_cursor->release_focus();

		{
			auto it = std::find(_components.rbegin(), _components.rend(), _cursor);
			if (it != _components.rend())
			{
				++it;
				while (it != _components.rend())
				{
					if ((*it)->try_give_focus_back()) {
						_cursor = *it;
						return true;
					}
					++it;
				}
			}
		}

		if (_parent != nullptr) {
			if (_parent->move_cursor_to_prev()) {
				return true;
			}
		}

		return try_give_focus_back();
	}

	form* container::get_form() const {

		if (_form != nullptr)
			return _form;

		auto p = parent();
		if (p != nullptr) {
			return p->get_form();
		}
		return nullptr;
	}

	void container::release_focus() {
		component::release_focus();

		if (_cursor != nullptr) {
			_cursor->release_focus();
		}
	}
}

#pragma once

#include "memory.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>
#include "component.h"
#include "tools.h"


namespace termform {

	class container : public component {
	
	public:
		container() {
			_is_container = true;
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<component, T>>>
		void add(std::shared_ptr<T> ptr_object)
		{
			ptr_object->x(0);
			ptr_object->parent(this);
			_components.push_back(std::static_pointer_cast<component>(ptr_object));
		}

		bool input(int chr) override;
		bool try_give_focus() override;
		bool try_give_focus_back() override;
		bool move_cursor_to_next();
		bool move_cursor_to_prev();

		form* get_form() const override;

		void release_focus() override;

	protected:
		inline void set_form(form* pform) {
			_form = pform;
		}

	protected:
		std::vector<component_ptr> _components{};
		form* _form{ nullptr };
		component_ptr _cursor{ nullptr };

	friend class form;

	};
}

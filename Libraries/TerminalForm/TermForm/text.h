#pragma once

#include "memory.hpp"
#include <string>
#include <iostream>
#include "component.h"
#include "control.h"


namespace termform {

	class text : public control {
	protected:
		std::string _value = "";

	public:
		std::string value() {
			return _value;
		}

		void value(const std::string& value) {
			_value = value;
		}

		void value(std::string&& value) {
			_value = std::move(value);
		}
	
		void print() const override {
			std::cout << _value << std::endl;
		}
		
	};
}

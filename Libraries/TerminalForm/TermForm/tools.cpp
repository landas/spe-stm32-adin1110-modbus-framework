#include <vector>
#include <iostream>
#include "tools.h"
#include "ansi_escape_codes.h"


namespace termform {
	boxsize string_boxsize(const std::string& s) {
		
		boxsize _string_size{ 0,1 };
		std::vector<std::string> v(2);
		std::string stripped_string{ ansi_escape_code::strip(s) };
		uint16_t cwidth{ 0 };
		
		for (const auto& c : stripped_string) {
			if (c == '\n') {
				if (cwidth > _string_size.width) {
					_string_size.width = cwidth;
				}
				
				++_string_size.height;
				cwidth = 0;
			}
			else {
				++cwidth;
			}
		}

		if (cwidth > _string_size.width) {
			_string_size.width = cwidth;
		}

		return _string_size;
	}

	uint16_t string_hash_16(const std::string& s) {
		std::hash<std::string> hasher;
		return static_cast<uint16_t>(hasher(s) & 0xFFFF);
	}

}
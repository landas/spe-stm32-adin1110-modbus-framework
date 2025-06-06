#include <cctype>
#include "ansi_escape_codes.h"

namespace termform {
	const std::array<std::string, 7> ansi_escape_code::_format = { "\033[0m","\033[1m","\033[2m","\033[3m","\033[4m","\033[5m","\033[7m" };
	const std::array<std::string, 10> ansi_escape_code::_color = { "\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m", "\033[39m", ""};
	const std::array<std::string, 10> ansi_escape_code::_background = { "\033[30m", "\033[41m", "\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[47m", "\033[49m", ""};
	const std::array<std::string, 3> ansi_escape_code::_manipulator = { "\033[2J\033[H", "\033[?25l", "\033[?25h" };

	int ansi_escape_code::find_first_pos(const std::string& string, int position) {
		if (position < string.length()) {
			for (auto it = string.cbegin() + position; it != string.cend(); ++it, ++position) {
				if (*it == '\033') {
					return position;
				}
			}
		}
		return -1;
	}

	std::string ansi_escape_code::find_first(const std::string& string, int position) {
		std::string s{};
		if (position < string.length()) {
			for (auto it = string.cbegin() + position; it != string.cend(); ++it, ++position) {
				if (*it == '\033') {
					for (++it; it != string.cend(); ++it) {
						s += *it;
						if(isalpha((*it)))
							break;
					}
					break;
				}
			}
		}
		return s;
	}

	std::vector<std::string> ansi_escape_code::find_all(const std::string& string, int position) {
		std::vector<std::string> v{};
		if (position < string.length()) {
			for (auto it = string.cbegin() + position; it != string.cend(); ++it, ++position) {
				if (*it == '\033') {
					std::string s{};
					for (++it; it != string.cend(); ++it) {
						s += *it;
						if (isalpha((*it))) {
							v.push_back(s);
							break;
						}
					}
					--it;
				}
			}
		}
		return v;
	}

	size_t ansi_escape_code::metadata_lenght(const std::string& string) {
		size_t count = 0;
		auto v = ansi_escape_code::find_all(string);
		for (const auto& s : v) {
			count += s.length() + 1;
		}
		return count;
	}

	size_t ansi_escape_code::count_newlines(const std::string& string) {
		size_t count = 0;
		for (const auto& c : string) {
			if (c == '\n')
				++count;
		}
		return count;
	}

	std::string ansi_escape_code::strip(const std::string& string) {
		std::string stripped_string{};
		bool add = true;
		for (const auto& c : string) {
			if(add) {
				if (c == '\033') {
					add = false;
				}
				else {
					stripped_string += c;
				}
			}
			else {
				if (isalpha(c)) {
					add = true;
				}
			}
		}
		return stripped_string;
	}
	
}
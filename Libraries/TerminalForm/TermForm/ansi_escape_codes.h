#pragma once

#include "memory.hpp"
#include <string>
#include <array>
#include <vector>

namespace termform {

	class ansi_escape_code {

	public:
		enum class format : char {
			reset, bold, dim, italic, underline, blink, reverse
		};

		enum class color : char {
			black, red, green, yellow, blue,
			magenta, cyan, white, standard, inherited
		};

		enum class background : char {
			black, red, green, yellow, blue,
			magenta, cyan, white, standard, inherited
		};

		enum class manipulator : char {
			clear, hide_cursor, show_cursor
		};

		inline static std::string get(format f)
		{
			return _format[static_cast<int>(f)];
		}

		inline static std::string get(color c)
		{
			return _color[static_cast<int>(c)];
		}

		inline static std::string get(background b)
		{
			return _background[static_cast<int>(b)];
		}

		inline static std::string get(manipulator m)
		{
			return _manipulator[static_cast<int>(m)];
		}

		inline static std::string get(int x, int y, color c, background b, std::string s = "") {
			return  get_move(x, y) + get(c) + get(b) + s;
		}

		inline static std::string get_clear()
		{
			return get(manipulator::clear);
		}

		inline static std::string get_clear_all()
		{
			return get(color::standard) + get(background::standard) + get(manipulator::clear);
		}

		inline static std::string get_hide_cursor()
		{
			return get(manipulator::hide_cursor);
		}

		inline static std::string get_show_cursor()
		{
			return get(manipulator::show_cursor);
		}

		inline static std::string get_move(int x, int y)
		{
			return std::string("\033[") + std::to_string(y) + ";" + std::to_string(x) + "H";
		}

		static std::string find_first(const std::string& string, int position = 0);
		static int find_first_pos(const std::string& string, int position = 0);
		static std::vector<std::string> find_all(const std::string& string, int position = 0);
		static size_t metadata_lenght(const std::string& string);
		static size_t count_newlines(const std::string& string);
		static std::string strip(const std::string& string);

	private:
		static const std::array<std::string, 7> _format;
		static const std::array<std::string, 10> _color;
		static const std::array<std::string, 10> _background;		
		static const std::array<std::string, 3> _manipulator;

	};
}

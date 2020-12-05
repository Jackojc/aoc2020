#pragma once

#ifndef UTIL_HPP
#define UTIL_HPP

#include <filesystem>
#include <string>
#include <vector>
#include <string>
#include <string_view>
#include <utility>
#include <fstream>

namespace util {
	#define NEW_EXCEPTION_TYPE(name, default_msg) \
		struct name: public std::runtime_error { \
			template <typename... Ts> name(Ts&&... args) \
				: std::runtime_error(((std::string{args}) + ...)) {} \
			name() \
				: std::runtime_error(default_msg) {} \
		};

	NEW_EXCEPTION_TYPE(Error, "an error has occurred.")

	#undef NEW_EXCEPTION_TYPE
}

namespace util {
	inline std::string read_file(const std::string& fname) {
		auto filesize = std::filesystem::file_size(fname);
		std::ifstream is(fname, std::ios::binary);

		auto str = std::string(filesize + 1, '\0');
		is.read(str.data(), static_cast<std::streamsize>(filesize));

		return str;
	}

	constexpr bool is_whitespace(char c) {
		return c == ' ' or c == '\n' or c == '\t' or c == '\v' or c == '\r';
	}

	constexpr bool is_alpha(char c) {
		return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z');
	}

	constexpr bool is_digit(char c) {
		return c >= '0' and c <= '9';
	}

	constexpr bool is_symbol(char c) {
		return
			c == '`' or
			c == '!' or
			c == '"' or
			c == '$' or
			c == '%' or
			c == '^' or
			c == '&' or
			c == '*' or
			c == '(' or
			c == ')' or
			c == '{' or
			c == '}' or
			c == '[' or
			c == ']' or
			c == ':' or
			c == ';' or
			c == '@' or
			c == '\'' or
			c == '~' or
			c == '#' or
			c == '|' or
			c == '\\' or
			c == '<' or
			c == ',' or
			c == '>' or
			c == '.' or
			c == '?' or
			c == '/'
		;
	}

	constexpr bool is_identifier(char c) {
		return is_alpha(c) or is_digit(c) or is_symbol(c);
	}

	auto strtovec(const std::string& str) {
		std::vector<int> numbers;
		numbers.reserve((str.length() >> 1) + (str.length() & 1));

		int num = 0;

		for (auto ptr = str.data(); ptr != str.data() + str.size(); ++ptr) {
			if (is_digit(*ptr)) {
				num = (num * 10) + (*ptr - '0');
				continue;
			}

			numbers.emplace_back(num);
			num = 0;
		}

		numbers.emplace_back(num);

		return numbers;
	}

	struct View {
		const char *begin, *end;

		constexpr size_t size() const {
			return end - begin;
		}
	};

	auto calculate_position(const char* begin, const char* offset) {
		int line = 0;
		int column = 0;

		while (begin != offset) {
			if (*begin == '\n') {
				line++;
				column = 0;
			}

			else {
				column++;
			}

			begin++;
		}

		return std::pair{ line, column };
	}

	constexpr int parse_int(const char*& ptr) {
		int num = 0;

		if (util::is_digit(*ptr)) {
			num = 0;

			do {
				num = (num * 10) + (*ptr - '0');
				++ptr;
			} while (util::is_digit(*ptr));
		}

		else
			return parse_int(++ptr);

		return num;
	}

	constexpr std::string_view parse_identifier(const char*& ptr) {
		const char *begin = nullptr, *end = nullptr;

		if (util::is_identifier(*ptr)) {
			begin = ptr;

			do {
				++ptr;
			} while (util::is_identifier(*ptr));

			end = ptr;
		}

		else
			return parse_identifier(++ptr);

		return { begin, static_cast<std::string_view::size_type>(end - begin) };
	}

	constexpr void skip_whitespace(const char*& ptr) {
		if (util::is_whitespace(*ptr)) {
			do {
				++ptr;
			} while (util::is_whitespace(*ptr));
		}

		else
			skip_whitespace(++ptr);
	}

	constexpr void parse_char(const char*& ptr, char c) {
		if (*ptr != c) {
			throw Error{"expected '", c, "' got '", *ptr, "'"};
		}

		ptr++;
	}

	constexpr char parse_char_any(const char*& ptr) {
		if (not is_identifier(*ptr)) {
			throw Error{"expected char"};
		}

		return *ptr++;
	}
}

#endif

#include <charconv>
#include <tuple>
#include <chrono>

#include <util.hpp>
#include <tinge.hpp>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto parseln(const char*& str) {
	int start = util::parse_int(str);

	util::parse_char(str, '-');

	int end = util::parse_int(str);
	util::skip_whitespace(str);

	auto c = util::parse_char_any(str);

	util::parse_char(str, ':');
	util::skip_whitespace(str);

	auto password = util::parse_identifier(str);

	// tinge::println(start, "-", end, " ", c, ": ", password);

	util::skip_whitespace(str);

	return std::tuple{ start, end, c, password };
}

int part1(const char*& str) {
	int valid = 0;
	while (*str != '\0') {
		auto [start, end, find, password] = parseln(str);

		int count = 0;
		for (const auto& c: password) {
			if (c == find)
				count++;
		}

		if (count >= start and count <= end) {
			valid++;
		}
	}

	return valid;
}

int part2(const char*& str) {
	int valid = 0;
	while (*str != '\0') {
		auto [a, b, find, password] = parseln(str);

		if ((password[a - 1] == find) ^ (password[b - 1] == find))
			valid++;
	}

	return valid;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);
	const char* ptr = nullptr;

	try {
		// using namespace std::chrono_literals;

		// ankerl::nanobench::Bench().timeUnit(1us, "us").run("part1", [&] {
		// 	const char* ptr = str.c_str();
		// 	auto d = part1(ptr);
		// 	ankerl::nanobench::doNotOptimizeAway(d);
		// });

		const char* ptr = str.c_str();
		tinge::successln(part1(ptr));

	} catch (const util::Error& e) {
		auto [line, column] = util::calculate_position(str.c_str(), ptr);
		tinge::errorln("error @ [", std::to_string(line), ": ", std::to_string(column), "]: ", e.what());
		return -1;
	}

	try {
		// using namespace std::chrono_literals;

		// ankerl::nanobench::Bench().timeUnit(1us, "us").run("part2", [&] {
		// 	const char* ptr = str.c_str();
		// 	auto d = part2(ptr);
		// 	ankerl::nanobench::doNotOptimizeAway(d);
		// });

		const char* ptr = str.c_str();
		tinge::successln(part2(ptr));

	} catch (const util::Error& e) {
		auto [line, column] = util::calculate_position(str.c_str(), ptr);
		tinge::errorln("error @ [", std::to_string(line), ": ", std::to_string(column), "]: ", e.what());
		return -1;
	}

	return 0;
}

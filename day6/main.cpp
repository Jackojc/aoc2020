#include <iostream>
#include <fstream>
#include <cstdint>

#include <util.hpp>
#include <tinge.hpp>

#define BENCH

#ifdef BENCH
	#define ANKERL_NANOBENCH_IMPLEMENT
	#include <nanobench.h>
#endif

auto calc(const char* ptr) {
	int answer_pt1 = 0, answer_pt2 = 0;

	uint32_t answer_bits = 0;
	uint32_t common_answer_bits = (1 << 27) - 1;

	while (*ptr != '\0') {

		auto person = util::parse_identifier(ptr);
		auto whitespace = util::consume_whitespace(ptr);

		uint32_t this_person_answer_bits = 0;
		for (const char c: person) {
			this_person_answer_bits |= (1 << (c - 'a'));
		}

		common_answer_bits &= this_person_answer_bits;
		answer_bits |= this_person_answer_bits;

		if (whitespace.size() > 1) {
			answer_pt1 += __builtin_popcount(answer_bits);
			answer_pt2 += __builtin_popcount(common_answer_bits);

			answer_bits = 0;
			common_answer_bits = (1 << 27) - 1;
		}
	}

	return std::pair { answer_pt1, answer_pt2 };
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);

	#ifdef BENCH
		using namespace std::chrono_literals;
		auto bench = ankerl::nanobench::Bench().warmup(200).minEpochIterations(5000).timeUnit(1us, "μs");

		bench.run("day6", [&] {
			ankerl::nanobench::doNotOptimizeAway(calc(str.c_str()));
		});
	#endif

	auto [p1, p2] = calc(str.c_str());

	tinge::successln(p1);
	tinge::successln(p2);

	return 0;
}

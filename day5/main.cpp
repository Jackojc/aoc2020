#include <string_view>
#include <type_traits>
#include <execution>
#include <algorithm>
#include <chrono>
#include <vector>

#include <util.hpp>
#include <tinge.hpp>

#define BENCH

#ifdef BENCH
	#define ANKERL_NANOBENCH_IMPLEMENT
	#include <nanobench.h>
#endif

// Calculate seat IDs.
template <typename F>
inline void calc(const std::string& str, const F& func) {

	const auto find_rc = [] (const char* const ptr) {
		int num = 0;

		for (int i = 0; i < 10; i++) {
			num *= 2;

			switch (*(ptr + i)) {
				case 'B':
				case 'R': num += 1; break;
			}
		}

		return num;
	};

	for (int i = 0; i <= (int)str.size() - 11; i += 11) {
		func(find_rc(str.c_str() + i));
	}
}

inline int part1(const std::string& str) {
	int highest = 0;

	// Find largest ID.
	calc(str, [&highest] (int id) {
		highest = highest > id ? highest: id;
	});

	return highest;
}

inline int part2(const std::string& str) {
	// Gather all IDs.
	int min = std::numeric_limits<int>::max();
	int max = 0;

	int total = 0;

	calc(str, [&] (int id) {
		min = id < min ? id: min;
		max = id > max ? id: max;

		total += id;
	});

	int sum = (max - min + 1) * (min + max) / 2;

	return sum - total;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);

	#ifdef BENCH
		using namespace std::chrono_literals;
		auto bench = ankerl::nanobench::Bench().warmup(50).minEpochIterations(1000).timeUnit(1us, "μs");

		bench.run("part1", [&] {
			ankerl::nanobench::doNotOptimizeAway(part1(str));
		});

		bench.run("part2", [&] {
			ankerl::nanobench::doNotOptimizeAway(part2(str));
		});
	#endif

	tinge::successln("part1: ", part1(str));
	tinge::successln("part2: ", part2(str));

	return 0;
}

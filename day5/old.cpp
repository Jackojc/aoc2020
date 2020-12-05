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
				case 'B': num += 1; break;
				case 'R': num += 1; break;
			}
		}

		return num;
	};

	for (int i = 0; i < (int)str.size() - 11; i += 11)
		func(find_rc(str.data() + i));
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
	std::vector<int> ids;
	ids.reserve(str.size() / 11);

	calc(str, [&ids] (int id) {
		ids.emplace_back(id);
	});

	std::sort(std::execution::unseq, ids.begin(), ids.end());

	// Find two adjadent values that differ by 2.
	return *std::adjacent_find(std::execution::unseq, ids.begin(), ids.end(), [] (const int left, const int right) {
		return left + 1 < right;
	}) + 1;
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

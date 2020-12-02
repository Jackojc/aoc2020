#include <utility>
#include <unordered_map>

#include <util.hpp>
#include <tinge.hpp>

const auto TARGET = 2020;

template <typename V> void part1(const V& vec) {
	std::unordered_map<int, int> map;

	for (typename V::size_type i = 0; i < vec.size(); ++i)
		map[vec[i]] = i;

	for (typename V::size_type i = 0; i < vec.size(); ++i) {
		const auto it = map.find(2020 - vec[i]);

		if (it == map.end())
			continue;

		const auto [key, value] = *it;

		if (value != static_cast<int>(i)) {
			tinge::successln(key * vec[i]);
			return;
		}
	}
}

template <typename V> void part2(const V& vec) {
	for (const auto& a: vec) {
		for (const auto& b: vec) {
			for (const auto& c: vec) {
				if (a + b + c == 2020) {
					tinge::successln(a * b * c);
					return;
				}
			}
		}
	}
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);
	auto nums = util::strtovec(str);

	part1(nums);
	part2(nums);

	return 0;
}

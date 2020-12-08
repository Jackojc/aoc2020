#include <util.hpp>
#include <tinge.hpp>

#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
	int answer_pt1 = 0, answer_pt2 = 0;
	std::ifstream input{"day6.input"};

	std::string line;
	while (!input.eof()) {
		uint32_t answer_bits = 0;
		uint32_t common_answer_bits = (1 << 27) - 1;

		while (std::getline(input, line) && line.size()) {
			uint32_t this_person_answer_bits = 0;
			for (auto c : line) {
				this_person_answer_bits |= (1 << (c - 'a'));
			}
			common_answer_bits &= this_person_answer_bits;
			answer_bits |= this_person_answer_bits;
		}

		answer_pt1 += __builtin_popcount(answer_bits);
		answer_pt2 += __builtin_popcount(common_answer_bits);
	}

	std::cout << "Part 1: " << answer_pt1 << std::endl;
	std::cout << "Part 2: " << answer_pt2 << std::endl;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);

	return 0;
}

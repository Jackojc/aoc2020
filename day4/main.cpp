#include <util.hpp>
#include <tinge.hpp>

int part1(const char*& str) {
	int valid = 0;
	while (*str != '\0') {

	}

	return valid;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);

	tinge::successln(part1(str));

	return 0;
}

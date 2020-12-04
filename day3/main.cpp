#include <vector>
#include <iterator>
#include <algorithm>

#include <util.hpp>
#include <tinge.hpp>

long long calc(const std::string& str, int slide_x, int slide_y, int width, int height) {
	long long count = 0;

	for (int x = 0, y = 0; y < height; y += slide_y, x += slide_x) {
		if (str[(y * width + y) + (x % width)] == '#')
			count++;
	}

	return count;
}

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);

	int width = str.find('\n');
	int height = std::count(str.begin(), str.end(), '\n');

	tinge::successln(calc(str, 3, 1, width, height));

	tinge::successln(
		calc(str, 1, 1, width, height) *
		calc(str, 3, 1, width, height) *
		calc(str, 5, 1, width, height) *
		calc(str, 7, 1, width, height) *
		calc(str, 1, 2, width, height)
	);

	return 0;
}

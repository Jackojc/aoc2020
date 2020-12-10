#include <vector>
#include <unordered_map>
#include <algorithm>

namespace Day9 {
	bool FindPair(const std::vector<int>& preambel, int target) {
		std::unordered_map<int, int> map;

		for (int i = 0; i < preambel.size(); i++) {
			if (map.find(target - preambel[i]) != map.end()) {
				return true;

			} else {
				map[preambel[i]] = i;
			}
		}

		return false;
	}

	int PartA(const std::vector<int>& data) {
		int preambel_index = 0, preambel_length = 25;

		for (int i = preambel_length; i < data.size(); i++) {
			std::vector preambel(data.begin() + preambel_index, data.begin() + preambel_index + preambel_length);

			if (!FindPair(preambel, data[i])) {
				return data[i];
			}

			preambel_index += 1;
		}

		return 0;
	}

	int PartB(const std::vector<int>& data, int target) {
		std::vector<int> t;

		for (int i = 0; i < data.size(); i++) {
			int sum = data[i];
			t.push_back(data[i]);

			for (int k = i + 1; k < data.size(); k++) {
				if (sum < target) {
					sum += data[k];
					t.push_back(data[k]);
				}

				if (sum > target) break;

				if (sum == target) {
					return (*std::min_element(t.begin(), t.end())) + (*std::max_element(t.begin(), t.end()));
				}
			}

			t.clear();
		}

		return 0;
	}
}

int main() {

	return 0;
}

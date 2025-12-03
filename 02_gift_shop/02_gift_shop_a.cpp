#include <iostream>
#include <cstdint>

#include <fileutils.hpp>
#include <stringutils.hpp>

bool isNumberInvalid(uint64_t number) {
	std::string num = std::to_string(number);
	if (num.length() & 1) return false;

	std::string_view part1(num.begin(), num.begin() + num.length() / 2);
	std::string_view part2(num.begin() + num.length() / 2, num.end());
	return part1.compare(part2) == 0;
}

int main() {
	std::string input = loadFileToString("./02_gift_shop.txt");
	uint64_t result = 0;

	for (StringTokenizer segment(input, ","); segment; ++segment) {
		StringTokenizer it(*segment, "-");
		uint64_t begin = std::stoull(std::string(*it));
		uint64_t end = std::stoull(std::string(*(++it)));
		for (uint64_t i = begin; i <= end; ++i)
			if (isNumberInvalid(i))
				result += i;
	}

	std::cout << result << std::endl;
}
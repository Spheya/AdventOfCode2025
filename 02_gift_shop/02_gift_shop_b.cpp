#include <iostream>
#include <cstdint>

#include <fileutils.hpp>
#include <stringutils.hpp>

bool isNumberMadeUpOf(const std::string& num, std::string_view part) {
	if (num.size() % part.size() != 0) return false;
	unsigned parts = num.size() / part.size();
	for (unsigned i = 1; i < parts; ++i) {
		std::string_view part2(num.data() + part.size() * i, part.size());
		if (part.compare(part2) != 0) return false;
	}
	return true;
}

bool isNumberInvalid(uint64_t number) {
	std::string num = std::to_string(number);

	std::string_view part1(num.begin(), num.begin());
	for (size_t i = 0; i < num.length() / 2; ++i) {
		if (isNumberMadeUpOf(num, std::string_view(num.begin(), num.begin() + i + 1)))
			return true;
	}

	return false;
}

int main() {
	std::string input = loadFileToString("./02_gift_shop.txt");
	uint64_t result = 0;

	for (SubStringIterator segment(input, ","); segment; ++segment) {
		SubStringIterator it(*segment, "-");
		uint64_t begin = std::stoull(std::string(*it));
		uint64_t end = std::stoull(std::string(*(++it)));
		for (uint64_t i = begin; i <= end; ++i)
			if (isNumberInvalid(i))
				result += i;
	}

	std::cout << result << std::endl;
}
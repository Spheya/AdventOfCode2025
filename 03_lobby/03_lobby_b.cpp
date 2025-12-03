#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

int main() {
	std::string input = loadFileToString("./03_lobby.txt");
	uint64_t result = 0;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		uint64_t multiplier = 100000000000;

		auto start = it->begin();
		for (int i = 11; i >= 0; --i, multiplier /= 10) {
			auto battery = std::max_element(start, it->end() - i);
			start = battery + 1;
			result += (*battery - '0') * multiplier;
		}
	}

	std::cout << result << std::endl;
}
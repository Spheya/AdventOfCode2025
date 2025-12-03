#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

int main() {
	std::string input = loadFileToString("./03_lobby.txt");
	uint64_t result = 0;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		auto firstBattery = std::max_element(it->begin(), it->end() - 1);
		auto secondBattery = std::max_element(firstBattery + 1, it->end());
		result += (*firstBattery - '0') * 10 + (*secondBattery - '0');
	}

	std::cout << result << std::endl;
}
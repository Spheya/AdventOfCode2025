#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

int main() {
	uint64_t result = 0;

	std::string input = loadFileToString("./05_cafeteria.txt");
	StringTokenizer it = StringTokenizer(input, "\r\n");
	std::vector<std::pair<uint64_t, uint64_t>> ranges;

	for (; it && it->size(); ++it) {
		StringTokenizer range(*it, "-");
		uint64_t start = std::stoull(std::string(*range));
		++range;
		uint64_t end = std::stoull(std::string(*range));
		ranges.emplace_back(start, end);
	}

	++it;
	for (; it && it->size(); ++it) {
		uint64_t num = std::stoull(std::string(*it));
		for (const auto& range : ranges) {
			if (num >= range.first && num <= range.second) {
				++result;
				break;
			}
		}
	}

	std::cout << result << std::endl;
}
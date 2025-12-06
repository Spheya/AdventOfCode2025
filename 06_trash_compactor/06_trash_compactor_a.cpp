#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

#include <vector>

int main() {
	uint64_t result = 0;
	std::string input = loadFileToString("./06_trash_compactor.txt");
	std::vector<std::vector<uint64_t>> numberGrid;

	StringTokenizer it(input, "\r\n");
	for (; it; ++it) {
		if (((*it)[0] < '0' || (*it)[0] > '9') && ((*it)[0] != ' ')) break;

		std::vector<uint64_t> row;

		for (StringTokenizer token(*it, " "); token; ++token) {
			if (token->empty()) continue;
			row.push_back(std::stoull(std::string(*token)));
		}

		numberGrid.emplace_back(row);
	}

	size_t idx = 0;
	for (StringTokenizer token(*it, " "); token; ++token) {
		if (token->empty()) continue;

		switch ((*token)[0]) {
		case '+': for (auto row : numberGrid) result += row[idx];
			break;
		case '*': {
			uint64_t tmp = 1;
			for (auto row : numberGrid)
				tmp *= row[idx];
			result += tmp;
		}
		}

		++idx;
	}

	std::cout << result << std::endl;
}
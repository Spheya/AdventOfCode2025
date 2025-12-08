#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

int main() {
	uint64_t result = 0;
	std::string input = loadFileToString("./07_laboratories.txt");
	std::vector<std::vector<char>> grid;

	StringTokenizer it(input, "\r\n");
	grid.emplace_back(it->size());
	memcpy(grid.front().data(), it->data(), grid.front().size());
	grid.front().push_back('\0');

	for (++it; it; ++it) {
		auto line = *it;
		std::vector<char> outputLine;

		for (size_t i = 0; i < line.size(); ++i) {
			char above = grid.back()[i];
			char c = line[i];

			if (c == '^' && above == '|') {
				++result;
				outputLine.pop_back();
				outputLine.insert(outputLine.end(), { '|', '^', '|' });
				++i;
			} else if (c == '.' && above == '|' || above == 'S') {
				outputLine.push_back('|');
			} else {
				outputLine.push_back(c);
			}
		}

		outputLine.push_back('\0');
		grid.emplace_back(std::move(outputLine));
	}

	for (auto ln : grid) {
		std::cout << ln.data() << std::endl;
	}

	std::cout << result << std::endl;
}


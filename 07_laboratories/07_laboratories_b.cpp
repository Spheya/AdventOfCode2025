#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

#include <numeric>

int main() {
	std::string input = loadFileToString("./07_laboratories.txt");
	std::vector<std::vector<uint64_t>> grid;

	constexpr uint64_t split = uint64_t(-1);

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		std::vector<uint64_t> ln;

		for (char c : *it) {
			if (c == '^') ln.push_back(split);
			else if (c == 'S') ln.push_back(1);
			else ln.push_back(0);
		}

		grid.push_back(std::move(ln));
	}

	for (auto ln = grid.begin() + 1; ln != grid.end(); ++ln) {
		auto prev = ln - 1;

		for (int i = 0; i < ln->size(); ++i) {
			if ((*ln)[i] == split) {
				(*ln)[i - 1] += (*prev)[i];
				(*ln)[i + 1] += (*prev)[i];
			} else {
				(*ln)[i] += (*prev)[i] == split ? 0 : (*prev)[i];
			}
		}
	}

	for (auto ln : grid) {
		for (auto c : ln) {
			std::cout << (c == split ? '^' : (c == 0 ? ' ' : '|'));
		}
		std::cout << std::endl;
	}

	std::cout << std::accumulate(grid.back().begin(), grid.back().end(), 0ull) << std::endl;
}
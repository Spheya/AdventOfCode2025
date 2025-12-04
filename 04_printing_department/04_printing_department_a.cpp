#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

int main() {
	uint64_t result = 0;
	std::vector<std::string> input(StringTokenizer(loadFileToString("./04_printing_department.txt"), "\r\n"), StringTokenizer::end());

	for (int y = 0; y < input.size(); ++y) {
		for (int x = 0; x < input[y].size(); ++x) {
			if (input[y][x] != '@') continue;

			int neighbours = 0;

			for (int yOff = -1; yOff <= 1; ++yOff) {
				for (int xOff = -1; xOff <= 1; ++xOff) {
					int finalX = x + xOff;
					int finalY = y + yOff;

					if (finalY < 0 || finalY >= input.size()) continue;
					if (finalX < 0 || finalX >= input[finalY].size()) continue;

					neighbours += int(input[finalY][finalX] != '.');
				}
			}

			if (neighbours < 5)
				++result;
		}
	}

	std::cout << result << std::endl;
}
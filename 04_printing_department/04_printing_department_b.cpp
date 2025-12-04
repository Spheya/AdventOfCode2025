#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

uint64_t pass(std::vector<std::string>& map, bool& collectedSomething) {
	uint64_t result = 0;
	collectedSomething = false;

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			if (map[y][x] != '@') continue;

			int neighbours = 0;

			for (int yOff = -1; yOff <= 1; ++yOff) {
				for (int xOff = -1; xOff <= 1; ++xOff) {
					int finalX = x + xOff;
					int finalY = y + yOff;

					if (finalY < 0 || finalY >= map.size()) continue;
					if (finalX < 0 || finalX >= map[finalY].size()) continue;

					neighbours += int(map[finalY][finalX] != '.');
				}
			}

			if (neighbours < 5) {
				++result;
				collectedSomething = true;
				map[y][x] = '.';
			}
		}
	}

	return result;
}

int main() {
	uint64_t result = 0;
	std::vector<std::string> input(StringTokenizer(loadFileToString("./04_printing_department.txt"), "\r\n"), StringTokenizer::end());
	bool collectedSomething;
	do result += pass(input, collectedSomething); while (collectedSomething);
	std::cout << result << std::endl;
}
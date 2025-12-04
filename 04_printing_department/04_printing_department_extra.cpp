#include <iostream>
#include <thread>
#include <chrono>

#include <stringutils.hpp>
#include <fileutils.hpp>

#include <Windows.h>

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
	using namespace std::chrono_literals;

	HANDLE output = NULL;
	CONSOLE_CURSOR_INFO cursor;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(output, &cursor);
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(output, &cursor);

	uint64_t result = 0;
	std::vector<std::string> input(StringTokenizer(loadFileToString("./04_printing_department.txt"), "\r\n"), StringTokenizer::end());

	bool collectedSomething;
	do {
		result += pass(input, collectedSomething);

		SetConsoleCursorPosition(output, {});

		for (int y = 0; y < input.size(); ++y) {
			for (int x = 0; x < input[y].size(); ++x) {
				std::cout << input[y][x];
			}
			std::cout << std::endl;
		}

	} while (collectedSomething);

}
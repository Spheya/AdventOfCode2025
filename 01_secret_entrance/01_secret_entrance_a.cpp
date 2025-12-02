#include <iostream>

#include <fileutils.hpp>
#include <stringutils.hpp>

int main() {
	std::string file = loadFileToString("./01_secret_entrance.txt");
	int dial = 50;
	int result = 0;

	for (SubStringIterator it(file, "\n"); it; ++it) {
		dial = ((dial + std::stoi(std::string(it->substr(1))) * ((*it)[0] == 'L' ? -1 : +1)) + 100) % 100;
		if (dial == 0)
			++result;
	}

	std::cout << result << std::endl;
}

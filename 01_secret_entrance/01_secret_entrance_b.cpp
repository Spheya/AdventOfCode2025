#include <iostream>

#include <fileutils.hpp>
#include <stringutils.hpp>

int main() {
	std::string file = loadFileToString("./01_secret_entrance.txt");
	int dial = 50;
	int result = 0;

	for (StringTokenizer it(file, "\n"); it; ++it) {
		if(dial == 0 && (*it)[0] == 'L') --result;
		dial = (dial + std::stoi(std::string(it->substr(1))) * ((*it)[0] == 'L' ? -1 : +1));
		result += abs(dial / 100) + int(dial <= 0);
		dial = (100 + (dial % 100)) % 100;
	}

	std::cout << result << std::endl;
}

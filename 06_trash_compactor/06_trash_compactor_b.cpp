#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

#include <vector>
#include <numeric>

struct Section {
	std::vector<std::vector<char>> data;
	char operation;
};

void transposeSection(Section& section) {
	std::vector<std::vector<char>> newSection;
	newSection.resize(section.data.front().size());
	for (auto& row : newSection)
		row.resize(section.data.size());
	
	for (size_t x = 0; x < section.data.size(); ++x)
		for (size_t y = 0; y < section.data[x].size(); ++y)
			newSection[y][x] = section.data[x][y];

	for (auto it = newSection.begin(); it != newSection.end();) {
		bool empty = true;
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			if (*it2 != ' ') {
				empty = false;
				break;
			}
		}

		if(empty) it = newSection.erase(it); else ++it;
	}

	section.data = std::move(newSection);
}

uint64_t calculateSection(const Section& section) {
	if (section.operation == '*') {
		uint64_t result = 1;
		for (const auto& s : section.data)
			result *= std::stoull(std::string(s.data(), s.size()));
		return result;
	} else {
		uint64_t result = 0;
		for (const auto& s : section.data)
			result += std::stoull(std::string(s.data(), s.size()));

		return result;
	}
}

int main() {
	std::string input = loadFileToString("./06_trash_compactor.txt");
	std::vector<std::string> inputGrid(StringTokenizer(input, "\r\n"), StringTokenizer::end());
	size_t gridWidth = inputGrid.front().size();
	size_t gridHeight = inputGrid.size() - 1;
	std::vector<Section> sections;

	for (size_t column = 0; column < gridWidth;) {
		size_t max = inputGrid.back().find_first_not_of(' ', column + 1);
		if (max == std::string::npos) max = gridWidth;
		size_t w = max - column;

		Section section = { {}, inputGrid.back()[column]};
		for (size_t y = 0; y < gridHeight; ++y) {
			section.data.emplace_back(w);
			memcpy(section.data.back().data(), inputGrid[y].data() + column, w);
		}
		transposeSection(section);
		sections.emplace_back(std::move(section));
		column = max;
	}

	uint64_t result = 0;
	for (auto& section : sections) result += calculateSection(section);
	std::cout << result;
}
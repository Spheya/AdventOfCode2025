#include <iostream>
#include <stringutils.hpp>
#include <fileutils.hpp>

struct PresentLayout {
	uint8_t r1;
	uint8_t r2;
	uint8_t r3;
	auto operator<=>(const PresentLayout& other) const noexcept = default;
};

struct Present {
	std::vector<PresentLayout> layouts;
};

PresentLayout rotatePresent(PresentLayout layout) {
	return PresentLayout{
		uint8_t(((layout.r1 & 4u) >> 2) | ((layout.r2 & 4u) >> 1) | ((layout.r3 & 4u) >> 0)),
		uint8_t(((layout.r1 & 2u) >> 1) | ((layout.r2 & 2u) >> 0) | ((layout.r3 & 2u) << 1)),
		uint8_t(((layout.r1 & 1u) >> 0) | ((layout.r2 & 1u) << 1) | ((layout.r3 & 1u) << 2))
	};
}

PresentLayout flipPresent(PresentLayout layout) {
	return PresentLayout{ layout.r3, layout.r2, layout.r1 };
}

void addUnique(std::vector<PresentLayout>& layouts, PresentLayout layout) {
	if (std::find(layouts.begin(), layouts.end(), layout) == layouts.end())
		layouts.push_back(layout);
}

Present generatePresent(PresentLayout layout) {
	Present present;
	auto flipped = flipPresent(layout);
	for (int i = 0; i < 4; ++i) {
		addUnique(present.layouts, layout);
		addUnique(present.layouts, flipped);
		layout = rotatePresent(layout);
		flipped = rotatePresent(flipped);
	}
	return present;
}

int main() {
	std::string input = loadFileToString("./12_christmas_tree_farm.txt");
	std::vector<std::string> lines(StringTokenizer(input, "\r\n"), StringTokenizer::end());
	std::vector<Present> presents;
	std::vector<std::string>::iterator lastEmptyLine = lines.begin();

	for (auto it = lines.begin(); it != lines.end(); ++it) {
		if (!it->empty()) {
			if ((*it)[1] == ':') {
				PresentLayout layout = {};
				for (char c : *++it) { if (c == '#') layout.r1 = (layout.r1 << 1) | 1; else layout.r1 <<= 1; }
				for (char c : *++it) { if (c == '#') layout.r2 = (layout.r2 << 1) | 1; else layout.r2 <<= 1; }
				for (char c : *++it) { if (c == '#') layout.r3 = (layout.r3 << 1) | 1; else layout.r3 <<= 1; }
				presents.push_back(generatePresent(layout));
			}
		} else {
			lastEmptyLine = it;
		}
	}

	for (auto& present : presents) {
		std::cout << "present:" << std::endl;
		for (auto& layout : present.layouts) {
			std::cout << ((layout.r1 & 1) ? "#" : " ") << ((layout.r1 & 2) ? "#" : " ") << ((layout.r1 & 4) ? "#" : " ") << std::endl;
			std::cout << ((layout.r2 & 1) ? "#" : " ") << ((layout.r2 & 2) ? "#" : " ") << ((layout.r2 & 4) ? "#" : " ") << std::endl;
			std::cout << ((layout.r3 & 1) ? "#" : " ") << ((layout.r3 & 2) ? "#" : " ") << ((layout.r3 & 4) ? "#" : " ") << std::endl;
			std::cout << std::endl;
		}
	}

	int i = 0;
	for (auto ln = lastEmptyLine + 1; ln != lines.end(); ++ln) {
		StringTokenizer tokenizer(*ln, "x");
		int w = std::stoi(std::string(*tokenizer++));
		StringTokenizer tokenizer2(*tokenizer, ": ");
		int h = std::stoi(std::string(*tokenizer2++));
		int area = (w - 3) * (h - 3);

		std::vector<int> presentRequests;
		for (auto it = StringTokenizer(*tokenizer2, " "); it; ++it)
			presentRequests.push_back(std::stoi(std::string(*it)));

		int presentsArea = 0;
		for (int i = 0; i < presentRequests.size(); ++i) {
			presentsArea += std::popcount(presents[i].layouts[0].r1) * presentRequests[i];
			presentsArea += std::popcount(presents[i].layouts[0].r2) * presentRequests[i];
			presentsArea += std::popcount(presents[i].layouts[0].r3) * presentRequests[i];
		}

		std::cout << "required trees: " << float(presentsArea) / float(area) << std::endl;
		i += std::ceil(float(presentsArea) / float(area));
	}

	std::cout << i << std::endl;

}
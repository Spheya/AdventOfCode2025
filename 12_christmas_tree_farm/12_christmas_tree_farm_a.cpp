#include <iostream>
#include <numeric>
#include <stringutils.hpp>
#include <fileutils.hpp>


int main() {
	std::string input = loadFileToString("./12_christmas_tree_farm.txt");
	std::vector<std::string> lines(StringTokenizer(input, "\r\n"), StringTokenizer::end());
	std::vector<int> presentSizes;
	std::vector<std::string>::iterator lastEmptyLine = lines.begin();

	for (auto it = lines.begin(); it != lines.end(); ++it) {
		if (!it->empty()) {
			if ((*it)[1] == ':') {
				presentSizes.push_back(0);
				for (int i = 0; i < 3; ++i) for (char c : *++it) if (c == '#') ++presentSizes.back();
			}
		} else {
			lastEmptyLine = it;
		}
	}

	int result = 0;
	for (auto ln = lastEmptyLine + 1; ln != lines.end(); ++ln) {
		StringTokenizer tokenizer(*ln, "x");
		int w = std::stoi(std::string(*tokenizer++));
		StringTokenizer tokenizer2(*tokenizer, ": ");
		int h = std::stoi(std::string(*tokenizer2++));
		int area = w * h;

		std::vector<int> presentRequests;
		for (auto it = StringTokenizer(*tokenizer2, " "); it; ++it)
			presentRequests.push_back(std::stoi(std::string(*it)));

		int chunks = (w / 3) * (h / 3);
		int totalPresents = std::accumulate(presentRequests.begin(), presentRequests.end(), 0);
		int totalPresentArea = 0;
		for (int i = 0; i < presentRequests.size(); ++i)
			totalPresentArea += presentRequests[i] * presentSizes[i];
		
		if (totalPresents <= chunks) {
			result += 1;
		} else if(totalPresentArea <= area) {
			std::cout << "nontrivial!!" << std::endl;
		}
	}

	std::cout << result << std::endl;

}
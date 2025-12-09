#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Point {
	int64_t x, y;
};

int main() {
	std::string input = loadFileToString("./09_movie_theater.txt");
	std::vector<Point> points;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		StringTokenizer ln(*it,",");
		Point p;
		p.x = std::stoll(std::string(*ln++));
		p.y = std::stoll(std::string(*ln++));
		points.push_back(p);
	}

	int64_t best = 0;
	for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 != points.end(); ++it2) {
			uint64_t area = uint64_t(std::abs(it2->x - it1->x) + 1) * uint64_t(std::abs(it2->y - it1->y) + 1);
			if(area > best)
				best = area;
		}
	}

	std::cout << best << std::endl;
}


#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Point {
	int64_t x, y;
};

struct Rect {
	int64_t minX, minY;
	int64_t maxX, maxY;
};

bool isInside(std::vector<Point>& points, Rect r) {
	bool inside = true;

	for (auto border = points.begin(); border != points.end(); ++border) {
		auto p1 = *border;
		auto p2 = (border + 1) == points.end() ? points.front() : *(border + 1);

		int64_t minX = std::min(p1.x, p2.x);
		int64_t maxX = std::max(p1.x, p2.x);
		int64_t minY = std::min(p1.y, p2.y);
		int64_t maxY = std::max(p1.y, p2.y);

		if (minX == maxX && maxX > r.maxX && maxY > r.maxY && minY < r.minY) inside = !inside;
		if (minX == maxX && maxY > r.minY && minY < r.maxY && minX > r.minX && minX < r.maxX) return false;
		if (minY == maxY && maxX > r.minX && minX < r.maxX && minY > r.minY && minY < r.maxY) return false;
	}

	return inside;
}

int main() {
	std::string input = loadFileToString("./09_movie_theater.txt");
	std::vector<Point> points;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		StringTokenizer ln(*it, ",");
		Point p;
		p.x = std::stoll(std::string(*ln++));
		p.y = std::stoll(std::string(*ln++));
		points.push_back(p);
	}

	int64_t best = 0;
	for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 != points.end(); ++it2) {
			int64_t minX = std::min(it1->x, it2->x);
			int64_t maxX = std::max(it1->x, it2->x);
			int64_t minY = std::min(it1->y, it2->y);
			int64_t maxY = std::max(it1->y, it2->y);

			uint64_t area = uint64_t((maxX - minX + 1) * (maxY - minY + 1));
			if (area > best)
				if (isInside(points, { minX, minY, maxX, maxY }))
					best = area;
		}
	}

	std::cout << best << std::endl;
}


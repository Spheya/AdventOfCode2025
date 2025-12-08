#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Point {
	unsigned circuitId;
	int64_t x, y, z;
};

struct Connection {
	Point* a;
	Point* b;
	uint64_t dstSq;
};

int main() {
	std::string input = loadFileToString("./08_playground.txt");

	std::vector<Point> points;
	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		StringTokenizer coord(*it, ",");
		int64_t x = std::stoll(std::string(*coord++));
		int64_t y = std::stoll(std::string(*coord++));
		int64_t z = std::stoll(std::string(*coord++));
		points.push_back({0, x, y, z});
	}

	std::vector<Connection> connections;
	for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 != points.end(); ++it2) {
			connections.push_back(Connection{&*it1, &*it2, uint64_t((it1->x - it2->x) * (it1->x - it2->x) + (it1->y - it2->y) * (it1->y - it2->y) + (it1->z - it2->z) * (it1->z - it2->z))});
		}
	}

	std::sort(connections.begin(), connections.end(), [](const Connection& a, const Connection& b){ return a.dstSq < b.dstSq; });

	unsigned nextCircuitId = 1;
	for (int i = 0; true; ++i) {
		const Connection& connection = connections[i];
		Point* a = connection.a;
		Point* b = connection.b;
		if(a->circuitId > b->circuitId) std::swap(a, b);

		if (b->circuitId == 0) {
			a->circuitId = nextCircuitId;
			b->circuitId = nextCircuitId;
			++nextCircuitId;
		} else if (a->circuitId == 0) {
			a->circuitId = b->circuitId;
		} else if (a->circuitId != b->circuitId) {
			unsigned swapId = b->circuitId;
			for(auto& p : points)
				if(p.circuitId == swapId)
					p.circuitId = a->circuitId;
		}

		bool connected = true;
		for(const auto& p : points) {
			if(p.circuitId != 1) {
				connected = false;
				break;
			}
		}

		if (connected) {
			std::cout << (a->x * b->x) << std::endl;
			break;
		}
	}
}


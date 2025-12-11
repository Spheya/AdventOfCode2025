#include <iostream>
#include <bit>
#include <algorithm>
#include <numeric>
#include <queue>
#include <unordered_set>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Machine {
	std::vector<unsigned> buttons;
	std::vector<unsigned> requiredJoltage;
	unsigned sizeMult;
};

struct State {
	int heuristic;
	int cost;
	int buttonIdx;
	std::vector<unsigned> joltage;

	bool operator>(const State& other) const noexcept { return heuristic + cost > other.heuristic + other.cost; }
};

// yoinked from https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
class uint_vector_hasher {
public:
	std::size_t operator()(const std::vector<unsigned>& vec) const {
		std::size_t seed = vec.size();
		for (unsigned i : vec)
			seed ^= size_t(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};

unsigned findCombination(const Machine& machine) {
	std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
	queue.emplace(0, 0, 0, std::vector<unsigned>(machine.requiredJoltage.size()));
	std::unordered_set<std::vector<unsigned>, uint_vector_hasher> visited;

	float avgCoverage = 0;
	std::vector<std::vector<bool>> possibleAxes;
	for (int i = 0; i < machine.buttons.size(); ++i) {
		possibleAxes.emplace_back(std::vector<bool>(machine.requiredJoltage.size()));
		for (unsigned j = machine.buttons[i]; j; j &= j - 1)
			for (auto& arr : possibleAxes)
				arr[std::countr_zero(j)] = true;

		avgCoverage += std::popcount(machine.buttons[i]);
	}
	avgCoverage /= float(machine.buttons.size());

	while (!queue.empty()) {
		State state = queue.top();
		queue.pop();

		for (int i = state.buttonIdx; i < machine.buttons.size(); ++i) {
			unsigned btn = machine.buttons[i];
			std::vector<unsigned> joltage = state.joltage;
			for (unsigned j = machine.buttons[i]; j; j &= j - 1)
				++joltage[std::countr_zero(j)];

			if (visited.contains(joltage)) continue;

			bool prune = false;
			bool equalsTarget = true;
			int heuristic = 0;

			for (int j = 0; j < machine.requiredJoltage.size(); ++j) {
				int value = machine.requiredJoltage[j] - joltage[j];
				if (possibleAxes[i][j]) {
					heuristic += std::max(value, heuristic) / avgCoverage;
				} else {
					if (value != 0) { prune = true; break; }
				}

				if (value < 0) { prune = true; break; }
				if (value != 0) equalsTarget = false;
			}

			if (prune) continue;
			if (equalsTarget) return (state.cost + 1) * machine.sizeMult;

			visited.emplace(joltage);
			queue.emplace(heuristic, state.cost + 1, i, std::move(joltage));
		}
	}

	return 0;
}

int main() {
	std::string input = loadFileToString("./10_factory.txt");
	std::vector<Machine> machines;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		Machine machine = {};

		for (StringTokenizer segment(*it, " "); segment; ++segment) {
			if ((*segment)[0] == '{') {
				for (StringTokenizer num(std::string_view(segment->data() + 1, segment->size() - 2), ","); num; ++num)
					machine.requiredJoltage.push_back(unsigned(std::stoi(std::string(*num))));
			} else if ((*segment)[0] == '(') {
				unsigned button = 0;
				for (StringTokenizer num(std::string_view(segment->data() + 1, segment->size() - 2), ","); num; ++num)
					button |= 1 << unsigned(std::stoi(std::string(*num)));
				machine.buttons.push_back(button);
			}
		}

		unsigned gcd = std::accumulate(machine.requiredJoltage.begin() + 1, machine.requiredJoltage.end(), machine.requiredJoltage.front(),
			[](int a, int b) {
				return std::gcd(a, b);
			}
		);
		machine.sizeMult = gcd;

		for (auto& joltage : machine.requiredJoltage) joltage /= gcd;

		std::sort(machine.buttons.begin(), machine.buttons.end(), [](unsigned a, unsigned b) { return std::popcount(b) < std::popcount(a); });
		machines.push_back(machine);
	}

	unsigned result = 0;
	for (auto& machine : machines) {
		unsigned r = findCombination(machine);
		result += r;
		std::cout << r << std::endl;
	}

	std::cout << result << std::endl;
}


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
	unsigned scale;
};

std::vector<unsigned> getButtonsForParity(const Machine& machine, const std::vector<unsigned>& requiredJoltage) {
	unsigned max = 1u << machine.buttons.size();
	std::vector<unsigned> combinations;

	unsigned indicators = 0;
	for (int i = 0; i < requiredJoltage.size(); ++i)
		indicators |= (requiredJoltage[i] & 1) << i;

	for (unsigned i = 0; i < max; ++i) {
		unsigned value = indicators;
		for (unsigned tmp = i; tmp; tmp &= tmp - 1)
			value ^= machine.buttons[std::countr_zero(tmp)];

		if (!value)
			combinations.push_back(i);
	}

	return combinations;
}

unsigned findCombination(const Machine& machine, std::vector<unsigned> requiredJoltage) {
	if (std::accumulate(requiredJoltage.begin(), requiredJoltage.end(), 0) == 0) return 0;

	auto combinations = getButtonsForParity(machine, requiredJoltage);
	unsigned solution = UINT_MAX;

	for (unsigned combi : combinations) {
		std::vector<unsigned> reqJolt = requiredJoltage;

		for (unsigned btn = combi; btn; btn &= btn - 1)
			for (unsigned jlt = machine.buttons[std::countr_zero(btn)]; jlt; jlt &= jlt - 1)
				--reqJolt[std::countr_zero(jlt)];

		bool prune = false;
		for (int i = 0; i < reqJolt.size(); ++i)
			if (reqJolt[i] > requiredJoltage[i]) prune = true;

		for (int i = 0; i < reqJolt.size(); ++i)
			reqJolt[i] >>= 1;

		if (!prune) {
			unsigned partialSolution = findCombination(machine, reqJolt);
			if (partialSolution != UINT_MAX)
				solution = std::min((partialSolution << 1) + std::popcount(combi), solution);
		}
	}

	return solution;
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

		machine.scale = std::accumulate(machine.requiredJoltage.begin() + 1, machine.requiredJoltage.end(), machine.requiredJoltage.front(),
			[](int a, int b) { return std::gcd(a, b); }
		);

		for (auto& joltage : machine.requiredJoltage) joltage /= machine.scale;

		std::sort(machine.buttons.begin(), machine.buttons.end(), [](unsigned a, unsigned b) { return std::popcount(b) < std::popcount(a); });
		machines.push_back(machine);
	}

	unsigned result = 0;
	int i = 0;
	for (auto& machine : machines) {
		unsigned r = findCombination(machine, machine.requiredJoltage) * machine.scale;
		result += r;
		std::cout << "shortest path: " << r << std::endl;
	}

	std::cout << result << std::endl;
}


#include <iostream>
#include <bit>
#include <algorithm>
#include <numeric>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Machine {
	unsigned totalJoltage;
	std::vector<unsigned> buttons;
	std::vector<unsigned> requiredJoltage;
	std::vector<unsigned> maxPresses;
};

bool isValidCombination(const Machine& machine, const std::vector<unsigned>& buffer) {
	static std::vector<unsigned> joltage;
	joltage.clear();
	joltage.resize(machine.requiredJoltage.size());

	for (int i = 0; i < buffer.size(); ++i) {
		unsigned btn = machine.buttons[i];
		while (btn) {
			int idx = std::countr_zero(btn);
			joltage[idx] += buffer[i];
			btn ^= 1 << idx;
		}
	}

	return joltage == machine.requiredJoltage;
}

unsigned findCombination(const Machine& machine, std::vector<unsigned>& buffer, int totalJoltage) {
	for (int i = 0; i < machine.buttons.size(); ++i) {
		if(buffer[i] >= machine.maxPresses[i] - 1) continue;

		int popcount = std::popcount(machine.buttons[i]);
		totalJoltage += popcount;
		++buffer[i];
		if (totalJoltage < machine.totalJoltage) {
			findCombination(machine, buffer, totalJoltage);
		}else if(totalJoltage == machine.totalJoltage) {
			if(isValidCombination(machine, buffer)) {
				unsigned total = 0;
				for(auto u : buffer) total += u;
				std::cout << "valid combination found: " << total << std::endl;
				return total;
			}
		}
		--buffer[i];
		totalJoltage -= popcount;
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

		machine.totalJoltage = std::accumulate(machine.requiredJoltage.begin(), machine.requiredJoltage.end(), 0);

		for (int i = 0; i < machine.buttons.size(); ++i) {
			unsigned maxPresses = UINT_MAX;
			unsigned btn = machine.buttons[i];
			while (btn) {
				int idx = std::countr_zero(btn);
				maxPresses = std::min(maxPresses, machine.requiredJoltage[idx]);
				btn ^= 1 << idx;
			}
			machine.maxPresses.push_back(maxPresses);
		}

		machines.push_back(machine);
	}

	unsigned result = 0;
	for (auto& machine : machines) {
		std::vector<unsigned> buffer;
		buffer.resize(machine.buttons.size());
		result += findCombination(machine, buffer, 0);
	}

	std::cout << result << std::endl;
}


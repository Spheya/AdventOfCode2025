#include <iostream>
#include <bit>
#include <algorithm>
#include <numeric>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Machine {
	uint64_t permCount;
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

unsigned findCombination(const Machine& machine) {
	std::vector<unsigned> buttons;
	buttons.resize(machine.maxPresses.size());

	for (uint64_t i = 0; i < machine.permCount; ++i) {
		uint64_t tmp = i;
		for (int j = 0; j < buttons.size(); ++j) {
			buttons[j] = tmp % machine.maxPresses[j];
			tmp /= machine.maxPresses[j];
		}

		if(isValidCombination(machine, buttons)) {
			std::cout << "found valid combination!!!" << std::endl;
			return i;
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

		machine.totalJoltage = std::accumulate(machine.requiredJoltage.begin(), machine.requiredJoltage.end(), 0);
		machine.permCount = 1;
		for(auto btn : machine.maxPresses)
			machine.permCount *= btn;

		machines.push_back(machine);
	}

	unsigned result = 0;
	for (auto& machine : machines) {
		result += findCombination(machine);
	}

	std::cout << result << std::endl;
}


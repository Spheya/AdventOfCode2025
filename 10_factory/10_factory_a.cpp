#include <iostream>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Machine {
	unsigned indicators;
	std::vector<unsigned> buttons;
};

unsigned findCombination(const Machine& machine) {
	unsigned max = 1ull << machine.buttons.size();
	unsigned shortest = UINT64_MAX;

	for (unsigned i = 0; i < max; ++i) {
		unsigned tmp = i;
		unsigned value = 0;
		while (tmp) {
			unsigned idx = std::countr_zero(tmp);
			value ^= machine.buttons[idx];
			tmp ^= 1 << idx;
		}

		if (value == machine.indicators)
			shortest = std::min(shortest, unsigned(std::popcount(i)));
	}

	return shortest;
}

int main() {
	std::string input = loadFileToString("./10_factory.txt");
	std::vector<Machine> machines;

	for (StringTokenizer it(input, "\r\n"); it; ++it) {
		Machine machine = {};

		for (StringTokenizer segment(*it, " "); segment; ++segment) {
			if ((*segment)[0] == '[') {
				for (int i = 1; (*segment)[i] != ']'; ++i) {
					if((*segment)[i] == '#') machine.indicators |= 1 << (i - 1);
				}
			} else if ((*segment)[0] == '(') {
				unsigned button = 0;
				for (StringTokenizer num(std::string_view(segment->data() + 1, segment->size() - 2), ","); num; ++num)
					button |= 1 << unsigned(std::stoi(std::string(*num)));
				machine.buttons.push_back(button);
			}
		}

		machines.push_back(machine);
	}

	unsigned result = 0;
	for(auto& machine : machines)
		result += findCombination(machine);

	std::cout << result << std::endl;
}


#include <iostream>
#include <algorithm>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Token {
	enum class Type { Open, Close };
	uint64_t value;
	Type type;
	auto operator<=>(const Token& other) const = default;
};

int main() {
	uint64_t result = 0;

	std::string input = loadFileToString("./05_cafeteria.txt");
	std::vector<Token> tokens;

	for (StringTokenizer it(input, "\r\n"); it && it->size(); ++it) {
		StringTokenizer range(*it, "-");
		tokens.emplace_back(std::stoull(std::string(*range++)), Token::Type::Open);
		tokens.emplace_back(std::stoull(std::string(*range++)), Token::Type::Close);
	}

	std::sort(tokens.begin(), tokens.end());

	unsigned depth = 0;
	size_t start = 0;
	for (const auto& token : tokens) {
		if (token.type == Token::Type::Open) {
			if (depth == 0)
				start = token.value;
			++depth;
		} else {
			--depth;
			if (depth == 0)
				result += token.value - start + 1;
		}
	}
	std::cout << result << std::endl;
}
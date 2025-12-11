#include <iostream>
#include <vector>
#include <set>

#include <stringutils.hpp>
#include <fileutils.hpp>

struct Server {
	std::string name;
	std::vector<size_t> outConnections;
	std::vector<size_t> inConnections;

	bool visited;
	size_t pathCount;
};

size_t traverse(std::vector<Server>& servers, size_t server) {
	Server& s = servers[server];

	if (s.visited)
		return s.pathCount;
	s.visited = true;
	
	for (size_t out : s.outConnections)
		s.pathCount += traverse(servers, out);

	return s.pathCount;
}

int main() {
	std::string input = loadFileToString("./11_reactor.txt");
	std::vector<Server> servers;

	for (StringTokenizer it(input, "\r\n"); it; ++it)
		servers.emplace_back(std::string(*(StringTokenizer(*it, ":"))));
	servers.emplace_back("out");
	servers.back().visited = true;
	servers.back().pathCount = 1;

	size_t lnNum = 0;
	for (StringTokenizer ln(input, "\r\n"); ln; ++ln, ++lnNum) {
		StringTokenizer it(*ln, " ");
		++it;
		for (; it; ++it) {
			auto serverIt = std::find_if(servers.begin(), servers.end(), [&](const Server& server) { return server.name == *it; });
			size_t serverId = serverIt - servers.begin();
			servers[lnNum].outConnections.push_back(serverId);
			servers[serverId].inConnections.push_back(lnNum);
		}
	}

	auto you = std::find_if(servers.begin(), servers.end(), [](const Server& server) { return server.name == "you"; });
	size_t result = traverse(servers, you - servers.begin());
	std::cout << result << std::endl;
}


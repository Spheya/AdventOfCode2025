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

void initForSearch(std::vector<Server>& servers, const std::string& name) {
	for (auto& server : servers) {
		if (server.name == name) {
			server.visited = true;
			server.pathCount = 1;
		} else {
			server.visited = false;
			server.pathCount = 0;
		}
	}
}

int main() {
	std::string input = loadFileToString("./11_reactor.txt");
	std::vector<Server> servers;

	for (StringTokenizer it(input, "\r\n"); it; ++it)
		servers.emplace_back(std::string(*(StringTokenizer(*it, ":"))));
	servers.emplace_back("out");

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

	auto svr = std::find_if(servers.begin(), servers.end(), [](const Server& server) { return server.name == "svr"; });
	auto dac = std::find_if(servers.begin(), servers.end(), [](const Server& server) { return server.name == "dac"; });
	auto fft = std::find_if(servers.begin(), servers.end(), [](const Server& server) { return server.name == "fft"; });
	initForSearch(servers, "dac");
	size_t toDac = traverse(servers, svr - servers.begin());

	initForSearch(servers, "fft");
	size_t toFft = traverse(servers, svr - servers.begin());

	initForSearch(servers, "fft");
	size_t dacToFft = traverse(servers, dac - servers.begin());

	initForSearch(servers, "dac");
	size_t fftToDac = traverse(servers, fft - servers.begin());

	initForSearch(servers, "out");
	size_t fftToOut = traverse(servers, fft - servers.begin());

	initForSearch(servers, "out");
	size_t dacToOut = traverse(servers, dac - servers.begin());

	size_t result = toDac * dacToFft * fftToOut + toFft * fftToDac * dacToOut;
	std::cout << result << std::endl;
}


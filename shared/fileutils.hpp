#pragma once

#include <fstream>
#include <string>
#include <filesystem>

std::string loadFileToString(const char* path) {
	std::ifstream file(path, std::iostream::binary);
	if (!file) return "";

	std::string data;
	data.resize(std::filesystem::file_size(path));
	file.read(data.data(), data.size());
	return data;
}

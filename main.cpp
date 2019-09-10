#include "main.h"

#include <iostream>
#include <fstream>
#include <random>
#include <string>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Expected exactly two arguments: filename and number of bytes to write" << std::endl;
		return 1;
	}

	const std::string filename(argv[1]);
	const std::string numBytesString(argv[2]);
	uint64_t numBytes;
	try 
	{
		numBytes = std::stoi(numBytesString);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error parsing cmdline arguments: " << e.what() << std::endl;
		return 1;
	}

	std::ofstream fp(filename, std::ofstream::out | std::ofstream::binary);
	if (fp.fail())
	{
		std::cerr << "Failed to open file for writing" << std::endl;
		return 1;
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint32_t> dist;

	for (int i = 0; i < numBytes / 4; i++) {
		uint32_t fourBytes = dist(mt);
		fp.write((const char *)&fourBytes, 4);
	}

	const auto remainder = numBytes % 4;
	if (remainder != 0)
	{
		uint32_t fourBytes = dist(mt);
		fp.write((const char*)& fourBytes, remainder);
	}

	if (fp.fail())
	{
		std::cerr << "Failed writing somewhere" << std::endl;
		return 1;
	}

	return 0;
}
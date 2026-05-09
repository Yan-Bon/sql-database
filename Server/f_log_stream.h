#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
//#define LOG_ENABLE

class f_log_stream
{
public:
	unsigned int pageId;
	std::fstream iof;
	void open(std::string s, std::ios_base::openmode om) {
		iof.open(s, om);
	};

	void write(const char* c, size_t count) {

		iof.write(c, count);
		iof.flush();
#ifdef LOG_ENABLE
		std::cout << std::endl << "write\n";
		for (int i = 0; i < count; i += 1) {
			char cur = *(c + i);
			std::cout << std::bitset<8>(cur) << " ";
		}
#endif // LOG_ENABLE
	}
	void read(char* c, size_t count) {
		iof.read(c, count);
		iof.flush();
#ifdef LOG_ENABLE
		std::cout << std::endl << "read\n";
		for (int i = 0; i < count; i += 1)
		{
			std::cout << std::bitset<8>(*(c + i)) << " ";
		}
#endif // LOG_ENABLE
	}
	bool is_open() {
		return iof.is_open();
	}

	void seekp(std::streamoff offset, std::ios_base::seekdir dir) {
		iof.seekp(offset, dir);
	}
	void seekg(std::streamoff offset, std::ios_base::seekdir dir) {
		iof.seekg(offset, dir);
	}
	void seekp(std::streamoff offset) {
		iof.seekp(offset);
	}
	void seekg(std::streamoff offset) {
		iof.seekg(offset);
	}
	std::streampos tellg() {
		iof.clear();
		if (iof.eof())
			exit(5000);
		return iof.tellg();
	}
	std::streampos tellp() {
		return iof.tellp();
	}
	void flush() {
		iof.flush();
	}

public:

	f_log_stream()
	{
	}
};


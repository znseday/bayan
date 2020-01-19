#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

// __FUNCSIG__ is for VS, but Qt (mingw) works with __PRETTY_FUNCTION__
#if ((defined WIN32) || (defined WIN64)) && (defined _MSC_VER)
#define MY_P_FUNC __FUNCSIG__
#else
#define MY_P_FUNC __PRETTY_FUNCTION__
#endif

#if ((defined NDEBUG) || (defined _NDEBUG))
#define MY_DEBUG_ONLY(x)
#else
#define MY_DEBUG_ONLY(x) {x}
#endif

enum class HashEnum
{
	CRC32,
	SHA1
};
HashEnum ConvertStringToHashEnum(const std::string& s);

struct Options 
{
	std::vector<std::string> Files;
	HashEnum HashType;
	size_t BlockSize;
};


bool GetOptions(Options &options, int argc, char* argv[]);

std::string GetCRC32(const char* buf, size_t blockSize);
std::string GetSHA1(const char* buf, size_t blockSize);

bool IsIdenticFiles(const Options& options);

#include <iostream>
#include <sstream>

#if ((defined WIN32) || (defined WIN64))
#include <boost/uuid/detail/sha1.hpp>
#else
#include <boost/uuid/sha1.hpp>
#endif


#include <boost/functional/hash.hpp>
#include <boost/crc.hpp>
#include <boost/filesystem.hpp>

#include "bayan.h"

using namespace std;

namespace opt = boost::program_options;

HashEnum ConvertStringToHashEnum(const std::string& s)
{
	HashEnum res = HashEnum::CRC32;
	if (s == "crc32" || s == "CRC32")
		res = HashEnum::CRC32;
	else if (s == "sha1" || s == "SHA1")
		res = HashEnum::SHA1;
	else
	{/*maybe in future*/}
	return res;
}
//--------------------------------------------------------------------

bool GetOptions(Options& options, int argc, char* argv[])
{
	opt::options_description desc("Usage: bayan [OPTIONS]... [FILES]...\nAll options:"); 
	desc.add_options()
		("help", "Help")
		("blocksize,b", opt::value<int>()->default_value(64), "Block size")
		("hash,h", opt::value<std::string>(), "Hash type (boost, crc32)")
		("files,f", opt::value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing(), "files to check");

	opt::positional_options_description posDescription;
	posDescription.add("files", -1);

	opt::command_line_parser parser{ argc, argv };
	parser.options(desc).positional(posDescription).allow_unregistered();
	opt::parsed_options parsed_options = parser.run();

	opt::variables_map vm;
	opt::store(parsed_options, vm);
	opt::notify(vm);

	options.BlockSize = 64;
	options.HashType = HashEnum::CRC32;

	if (vm.count("help"))
	{
		cout << desc << endl;
		return false;
	}

	if (vm.count("blocksize"))
	{
		options.BlockSize = vm["blocksize"].as<int>();
	}

	if (vm.count("hash")) 
	{
		options.HashType = ConvertStringToHashEnum(vm["hash"].as<std::string>());
	}

	if (vm.count("files")) 
	{
		options.Files = vm["files"].as<std::vector<std::string>>();
	}

	return true;
}
//--------------------------------------------------------------------

std::string GetCRC32(const char* buf, size_t blockSize)
{
	boost::crc_32_type crc_hash;
	crc_hash.process_bytes(buf, blockSize);
	return to_string(crc_hash.checksum());
}
//--------------------------------------------------------------------

string GetSHA1(const char* buf, size_t blockSize)
{
	unsigned resHash[5];

	boost::uuids::detail::sha1 Sha1;
	Sha1.process_bytes(buf, blockSize);

	string res;
	//string res(Sha1);

	Sha1.get_digest( resHash );
	
	for (auto d : resHash)
		res += to_string(d);

	return res;
}
//--------------------------------------------------------------------

bool IsIdenticFiles(const Options& options)
{
	size_t firstSize = boost::filesystem::file_size(options.Files.front());

	for (const auto& f : options.Files)
	{
		if ( firstSize != boost::filesystem::file_size(f) )
			return false;
	}

	//vector<ifstream> fileStreams(options.Files.size());
	vector<ifstream*> fileStreams;
	for (int i = 0; i < options.Files.size(); i++)
		fileStreams.push_back(new ifstream);

	vector<char> buf(options.BlockSize);

	size_t blockCount = firstSize / options.BlockSize + 1;
	size_t lastSize = firstSize % options.BlockSize;

	for (size_t i = 0; i < blockCount; i++)
	{
		string fisrtHash, curHash;

		for (size_t j = 0; j < options.Files.size(); j++)
		{
			if (i == 0)
			{
				fileStreams[j]->rdbuf()->pubsetbuf(nullptr, 0); // Disable buffering
				fileStreams[j]->open(options.Files[j], ios::in || ios::binary);
				if (!fileStreams[j]->is_open())
				{
					cout << "Error: file couldn't open" << endl;
					return false;
				}
			}
		
			if (i == blockCount - 1)
			{
				fileStreams[j]->read(buf.data(), lastSize);
				memset(buf.data() + lastSize, 0, buf.size() - lastSize);
			}
			else
				fileStreams[j]->read(buf.data(), buf.size());
	
			switch (options.HashType)
			{
			case HashEnum::CRC32:
				curHash = GetCRC32(buf.data(), buf.size());
				break;
			case HashEnum::SHA1:
				curHash = GetSHA1(buf.data(), buf.size());
				break;
			}

			if (j == 0)
				fisrtHash = curHash;
			else
			{
				if (fisrtHash != curHash)
					return false;
			}

		}
	}

	return true;
}
//--------------------------------------------------------------------

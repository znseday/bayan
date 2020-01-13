#include <iostream>
#include <vector>
//#include <iterator>
//#include <algorithm>
//#include <cassert>
#include <fstream>
#include <boost/program_options.hpp>

#include "bayan.h"

namespace opt = boost::program_options;

using namespace std;

void TestBasic();
//void MainTask();
void PrintOptions(const Options& options);

int main(int argc, char *argv[])
{

#if (defined WIN32) || (defined WIN64)
    cout << MY_P_FUNC << endl;              // for debugging

    //MY_DEBUG_ONLY(TestBasic();)           // for debugging
#else
    //istream &i_stream = cin;
#endif

	MY_DEBUG_ONLY(cout << "Homework bayan (DEBUG detected)" << endl;)

	try 
	{
		Options options;
		if (!GetOptions(options, argc, argv)) 
		{
			cout << "Error: something's wrongs with options" << endl;
			return -1;
		}

		MY_DEBUG_ONLY(PrintOptions(options); )

		if (IsIdenticFiles(options))
			cout << "Files are identical" << endl;
		else
			cout << "Files are NOT identical" << endl;
		
	}
	catch (const opt::error& e) 
	{
		cerr << e.what() << endl;
		return -1;
	}
	catch (const exception& e) 
	{
		cerr << e.what() << endl;
		return -1;
	}

    return 0;
}
//--------------------------------------------------------------------

void TestBasic()
{
    cout << endl << "TestBasic" << endl;
    cout << "//-------------------" << endl;
}
//--------------------------------------------------------------------

void PrintOptions(const Options &options)
{
	cout << endl << "PrintOptions" << endl;
	cout << "options.BlockSize = " << options.BlockSize << endl;

	for (const auto& f : options.Files)
		cout << "options.File = " << f << endl;

	switch (options.HashType)
	{
	case HashEnum::CRC32:
		cout << "HashType = HashEnum::CRC32" << endl;
		break;
	case HashEnum::SHA1:
		cout << "HashType = HashEnum::SHA1" << endl;
		break;
	default:
		cout << "Something's wrong with HashEnum" << endl;
	}

	cout << "//-------------------" << endl;
}
//--------------------------------------------------------------------




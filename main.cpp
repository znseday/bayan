#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <fstream>

#include "bayan.h"

using namespace std;

void TestBasic();
void MainTask();

int main(int argc, char *argv[])
{
    //for(int i = 1; i < argc; i++)
    //    if (strcmp(argv[1], "-ext") == 0)
    //        IsExOutput = true;

#if (defined WIN32) || (defined WIN64)
    cout << MY_P_FUNC << endl;              // for debugging

    //MY_DEBUG_ONLY(TestBasic();)           // for debugging

    //ifstream i_stream = ifstream("my_own_test.txt");
    //if (!i_stream)
    //{
    //    cout << "My error: the input file not found" << endl;
    //    exit(0);
    //}
#else
    istream &i_stream = cin;
#endif

    MY_DEBUG_ONLY(cout << "Homework bayan (DEBUG detected)" << endl;)

	TestBasic();

    //vector<string> srcData;

    //string line;
    //while (getline(i_stream, line))
    //{
    //    #if (defined WIN32) || (defined WIN64)
    //        cout << line << endl; // just echo
    //    #else
    //        // nothing
    //    #endif

    //    rt.Insert(line);
    //    srcData.emplace_back(line);
    //}

    MainTask();

    return 0;
}

void TestBasic()
{
    cout << endl << "TestBasic" << endl;

    cout << "//-------------------" << endl;
}

void MainTask()
{
    cout << endl << "TestMainTask" << endl;

    cout << "//-------------------" << endl;
}


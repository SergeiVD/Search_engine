#include <iostream>
#include <fstream>
#include <exception>
#include <cerrno>
#include <string>
#include <system_error>
#include <vector>

// #include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../google_tests/inverted_index_tests.h"
#include "../google_tests/relative_index_tests.h"

#include "../include/converter_json.h"
#include "../include/inverted_index.h"
#include "../include/search_server.h"

#include "../include/search_engine.h"


int main(int argc, char *argv[])
{
	std::cout<<"Menu:"<<std::endl;
	std::cout<<"If you whant run to project input [run]"<<std::endl;
	std::cout<<"If you whant run to tests input [tests]"<<std::endl;
	std::cout<<"If you whant to exit input [exit]"<<std::endl;

	while (true)
	{
		std::string command;
		std::cout<<"Input command: ";
		std::cin>>command;

		if(command == "run")
		{
			SearchEngine search_engine;
			try
			{
				search_engine.run();	
			}
			catch (std::runtime_error& e)
			{
				std::cout<<"Error code: "<<errno<<" "<<e.what()<<std::endl;
				return errno;
			}

			std::cout<<"Search Engine is COMPLETED!!!"<<std::endl;
			std::cout<<"Result locate in file ../json/answers.json"<<std::endl;
			break;
		}
		else if(command == "tests")
		{
			testing::InitGoogleTest();
			return RUN_ALL_TESTS();
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			std::cout<<"no correct command try again!"<<std::endl;
		}
	}
	
	return 0;
}

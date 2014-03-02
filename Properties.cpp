#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <exception>
#include <fstream>

#include <iomanip>
#include <algorithm>
#include <cctype>

#include "Properties.hpp"

namespace utilities
{
	
Properties::Properties(std::string filename) : filename_(filename)
{
	initialize();
}

Properties::~Properties()
{
}

void Properties::initialize()
{	
	std::ifstream config( filename_.c_str() );
	if(!config)
	{
		// TODO: proper error handling
		std::cerr<<"error"<<std::endl;
		return;
	}

	//parameters
	std::set<std::string> options;
	options.insert("*");
	
	try
	{	  
		for (pod::config_file_iterator i(config, options), e ; i != e; ++i)
		{
			std::cout << i->string_key <<" "<<i->value[0] << std::endl;
			parameters_[i->string_key] = i->value[0];
		}
		std::cout << parameters_["StatLogServer.Path"] << std::endl;
	}
	catch(std::exception& e)	
	{
		std::cerr<<"Exception: "<<e.what()<<std::endl;
	}
}

bool Properties::toBool(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

std::string Properties::getStringValue(std::string name)
{
	return parameters_[name];
}

int Properties::getIntValue(std::string name)
{
	return std::stoi( parameters_[name] );
}

long Properties::getLongValue(std::string name)
{
	return std::stol( parameters_[name] );
}

float Properties::getFloatValue(std::string name)
{
	return std::stof( parameters_[name] );
}

double Properties::getDoubleValue(std::string name)
{
	return std::stod( parameters_[name] );
}

bool Properties::getBoolValue(std::string name)
{
	return toBool( parameters_[name] );
}

}

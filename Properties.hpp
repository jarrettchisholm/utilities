#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string.h>
#include <map>

#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>

namespace pod = boost::program_options::detail;

namespace utilities
{
	
class Properties
{
public:
	Properties(std::string filename);
	virtual ~Properties();
	
	std::string getStringValue(std::string name);
	int getIntValue(std::string name);
	long getLongValue(std::string name);
	float getFloatValue(std::string name);
	double getDoubleValue(std::string name);
	bool getBoolValue(std::string name);

private:
	std::string filename_;
	std::map<std::string, std::string> parameters_;
	
	void initialize();
	
	bool toBool(std::string str);
};

}

#endif /* PROPERTIES_H_ */

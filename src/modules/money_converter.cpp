#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "money_converter.hpp"
#include <sstream>


std::string exec(const char* cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe)
	{
		throw std::runtime_error("_popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}
	return result;
}


//function saving currencies requested by user
std::string currency_comparison(const std::string& currency1, const std::string& currency2, bool chart)
{
	std::string money, code;
	std::string command = "MoneyExchange.exe " + currency1 + " " + currency2;
	std::string result = exec(command.c_str());
	std::stringstream ss(result);
	ss >> money >> code;
	if (chart)
	{
		return code;
	}
	return money;
}

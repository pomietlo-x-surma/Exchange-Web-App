#include "password_checker.hpp"
#include <regex>


std::string pass_check(const std::string& password)
{
	std::regex pattern_nalfa("[^a-zA-Z0-9\\s]");
	std::regex pattern_liczba("[0-9]");
	std::regex pattern_AZ("[A-Z]");
	std::regex pattern_az("[a-z]");
	std::regex pattern_rozmiar(".{8,50}");


	std::string nap = "";

	if (password.find('\\0') != std::string::npos)
	{
		return "Haslo nie moze zawierac znaku '\\0'!";
	}

	if (std::regex_search(password, pattern_nalfa) &&
		std::regex_search(password, pattern_liczba) &&
		std::regex_search(password, pattern_AZ) &&
		std::regex_search(password, pattern_az) &&
		std::regex_search(password, pattern_rozmiar))
	{
		return nap;
	}
	nap = "Haslo musi zawierac: ";
	if (!std::regex_search(password, pattern_nalfa))
	{
		nap += "przynajmniej jeden znak specjalny (np. !,@,#,$,%,^)! \n";
	}
	if (!std::regex_search(password, pattern_liczba))
	{
		nap += "przynajmniej jedna liczbe! \n";
	}
	if (!std::regex_search(password, pattern_AZ))
	{
		nap += "przynajmniej\njedna wielka litere! \n";
	}
	if (!std::regex_search(password, pattern_az))
	{
		nap += +"przynajmniej\njedna mala litere! \n";
	}
	if (!std::regex_search(password, pattern_rozmiar))
	{
		if (password.length() < 8)
		{
			nap += "Miec dlugosc przynajmniej 8 znakow! ";
		}
		else
		{
			nap += "Zbyt dlugie haslo! \n";
		}
	}
	return nap;
}

bool email_check(const std::string& email)
{
	std::regex email_regex("[0-9a-zA-Z]+@[0-9a-z]+\\.[a-z]{2,3}");
	if (std::regex_match(email, email_regex))
	{
		return true;
	}
	if (email.find('\\0') != std::string::npos)
	{
		return false;
	}
	return false;
}

bool login_check(const std::string& user)
{
	std::regex user_regex("^[0-9a-zA-Z]{4,30}$");
	if (std::regex_match(user, user_regex))
	{
		return true;
	}
	if (user.find('\\0') != std::string::npos)
	{
		return false;
	}
	return false;
}

#include "password_checker.hpp"
#include <regex>


std::string pass_check(const std::string& password)
{
	std::regex pattern_alpha("[^a-zA-Z0-9\\s]");
	std::regex pattern_number("[0-9]");
	std::regex pattern_AZ("[A-Z]");
	std::regex pattern_az("[a-z]");
	std::regex pattern_size(".{8,50}");


	std::string text = "";

	if (password.find('\\0') != std::string::npos)
	{
		return "Your password can't contain '\\0'!";
	}

	if (std::regex_search(password, pattern_alpha) &&
		std::regex_search(password, pattern_number) &&
		std::regex_search(password, pattern_AZ) &&
		std::regex_search(password, pattern_az) &&
		std::regex_search(password, pattern_size))
	{
		return text;
	}
	text = "Password must consist of: \n";
	if (!std::regex_search(password, pattern_alpha))
	{
		text += "at least one special character (np. !,@,#,$,%,^)! \n";
	}
	if (!std::regex_search(password, pattern_number))
	{
		text += "at least one number! \n";
	}
	if (!std::regex_search(password, pattern_AZ))
	{
		text += "at least\none uppercase letter! \n";
	}
	if (!std::regex_search(password, pattern_az))
	{
		text += +"at least\none lowercase letter! \n";
	}
	if (!std::regex_search(password, pattern_size))
	{
		if (password.length() < 8)
		{
			text += "It must have at least 8! \n";
		}
		else
		{
			text += "Too long password! \n";
		}
	}
	return text;
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

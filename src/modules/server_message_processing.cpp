#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "handling_CSV_file.hpp"
#include "password_checker.hpp"
#include "server_message_processing.hpp"


std::array<std::string,3> currencies = {"USD","EUR", "PLN"};

std::string to_string_with_precision(const long double& value, const char& precision)
{
	std::ostringstream out;
	out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

//sending to client
std::string process_message(const std::string& received_message)
{
	return received_message;
}

std::string check_register(const std::string& email, const std::string& login, const std::string& pass,
                           const std::string& pass_rep)
{
	if (!(email_check(email) && login_check(login)))
	{
		return process_message("Incorrect E-mail or Password!");
	}
	if (check_login_email_existence(email, login))
	{
		return process_message("The specified email or login already exists!");
	}
	if (!pass_check(pass).empty())
	{
		return process_message(pass_check(pass));
	}
	if (pass != pass_rep)
	{
		return process_message("Passwords don't match!");
	}
	WriteLogsToFile_Passes(email, login, pass, path_to_user_auth_csv);
	WriteLogsToFile_Currencies(login, "100", "0.0", "0.0", path_to_user_balance_csv, true);
	return "0" + login;
}

std::string check_logging(const std::string& email, const std::string& pass)
{
	if (!correct_password_check(email, pass).empty())
	{
		return process_message(correct_password_check(email, pass));
	}
	return process_message("5");
}


//0
std::string login_user(const std::string& message)
{
	std::stringstream sa(message);
	std::string email, pass;
	sa >> email >> pass;
	return check_logging(email, pass);
}

//1
std::string register_user(const std::string& message)
{
	std::cout << message << "\n";
	std::stringstream sa(message);
	std::string email, login, pass, pass_rep;
	sa >> email >> login >> pass >> pass_rep;
	return check_register(email, login, pass, pass_rep);
}

//3
std::string exchange_rate(const std::string& message)
{
	std::stringstream sa(message);
	std::string currency1, currency2, value, value_result;
	sa >> currency1 >> currency2 >> value;
	if (value.empty())
	{
		if (currency1 == currency2)
		{
			return "Z1.0";
		}
		return "Z" + ReadLogs(currency1 + " " + currency2, path_to_currencies_csv);
	}
	if (currency1 == currency2)
	{
		return "ZZ" + to_string_with_precision(stold(value) / 10);
	}
	std::stringstream os(ReadLogs(currency1 + " " + currency2, path_to_currencies_csv));
	std::getline(os, value_result, ' ');
	return "ZZ" + to_string_with_precision(stold(value_result) * stold(value) / 10);
}


//4
std::string account_balance(const std::string& message)
{
	std::string log, usd, pln, eur;
	std::string result = ReadLogs(message, path_to_user_balance_csv);
	std::istringstream(result) >> usd >> eur >> pln;
	return "W  USD: " + usd + "  EUR: " + eur + "  PLN: " + pln + '\n';
}

//6
std::string exchange(const std::string& message)
{
	std::stringstream sa(message);
	std::string login, currency1, currency2, value;
	sa >> login >> currency1 >> currency2 >> value;
	if (currency1 != currency2)
	{
		std::string usd, pln, eur;
		std::map<std::string, long double> balance = {{"USD", 0.0}, {"EUR", 0.0}, {"PLN", 0.0}};
		std::istringstream(ReadLogs(login, path_to_user_balance_csv)) >> usd >> eur >> pln;
		long double usd_value = stold(usd), eur_value = stold(eur), pln_value = stold(pln), wart = stold(value);
		balance["USD"] = usd_value;
		balance["EUR"] = eur_value;
		balance["PLN"] = pln_value;
		if (balance[currency1] >= wart)
		{
			balance[currency1] -= wart;
			balance[currency2] += wart * stold(ReadLogs(currency1 + " " + currency2, path_to_currencies_csv));
		}
		else
		{
			return "EYou do not have enough funds in your account!\n";
		}
		WriteLogsToFile_Currencies(login, to_string_with_precision(balance["USD"]),
		                           to_string_with_precision(balance["EUR"]), to_string_with_precision(balance["PLN"]),
									path_to_user_balance_csv, false
		);
		return "W  USD: " + to_string_with_precision(balance["USD"]) + "  EUR: " + to_string_with_precision(balance["EUR"])
			+ "  PLN: " + to_string_with_precision(balance["PLN"]);
	}
	if (currency1 == currency2)
	{
		return "Y" + value;
	}
	return "Eerror!\n";
}


std::string receive_text(const char& id, const std::string& message)
{
	std::cout << id << "," << message << '\n';
	switch (id)
	{
	case '0': return login_user(message);
	case '1': return register_user(message);
	case '3': return exchange_rate(message);
	case '4': return account_balance(message);
	case '6': return exchange(message);
	default : return "Index don't match!\n";
	}
}

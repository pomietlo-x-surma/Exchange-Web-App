#include <boost/test/unit_test.hpp>
#include "../src/modules/server_message_processing.hpp"
#include "../src/modules/password_checker.hpp"

struct ExistingUser {
	std::string email = "bart11@o2.pl";
	std::string login = "bart";
	std::string password = "qWERTY1!!!";
}existing_user;

struct NewUser {
	std::string email = "11bart11@o2.pl";
	std::string login = "11bart";
	std::string password = "qWERTY1!!!";
}new_user;

const std::string incorrect_password = "123566Aa";
const std::string correct_password = "qWERTY1!!!";
BOOST_AUTO_TEST_CASE(TestPositiveNumber) {
    BOOST_REQUIRE_EQUAL(to_string_with_precision(2.312, 1), "2.3");
}




BOOST_AUTO_TEST_CASE(TestPasswordEquality){
	BOOST_REQUIRE_EQUAL(check_register(existing_user.email, existing_user.login, correct_password, correct_password), "The specified email or login already exists!");
	BOOST_REQUIRE_EQUAL(check_register(new_user.email, new_user.login, correct_password, incorrect_password), "Passwords don't match!");
	BOOST_REQUIRE_EQUAL(check_register(existing_user.email, new_user.login, correct_password, correct_password), "The specified email or login already exists!");
}

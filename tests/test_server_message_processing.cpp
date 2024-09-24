#include <boost/test/unit_test.hpp>
#include "../src/modules/server_message_processing.hpp"
#include "../src/modules/password_checker.hpp"

struct TestUser {
	std::string email = "bart11@o2.pl";
	std::string login = "bart";
	std::string password = "qWERTY1!!!";
}user;



BOOST_AUTO_TEST_CASE(TestPositiveNumber) {
    BOOST_REQUIRE_EQUAL(to_string_with_precision(2.312, 1), "2.3");
}




BOOST_AUTO_TEST_CASE(TestPasswordEquality){
	BOOST_REQUIRE_EQUAL(check_register("1"+user.email, user.login+"1", user.password, user.password), "The specified email or login already exists!");
	BOOST_REQUIRE_EQUAL(check_register("1aa"+user.email, user.login+"111", user.password, user.password+'1'), "Passwords don't match!");
}

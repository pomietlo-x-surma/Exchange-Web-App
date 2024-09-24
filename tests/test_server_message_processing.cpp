#include <boost/test/unit_test.hpp>
#include "../src/modules/server_message_processing.hpp"

BOOST_AUTO_TEST_CASE(TestPositiveNumber) {
    BOOST_REQUIRE_EQUAL(to_string_with_precision(2.312, 1), "2.3");
}
BOOST_AUTO_TEST_CASE(TestPasswordEquality){
	BOOST_REQUIRE_EQUAL(check_register("adam123@o2.pl", "adam", "Admin12345!", "Admin12345!"), "0adam");
}

#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "../src/modules/money_converter.cpp"

std::string mock_exec(const char* cmd) {
	return "4.56 USD";
}

BOOST_AUTO_TEST_CASE(TestCurrencyComparisonWithMockExec) {
    exec_func = mock_exec;
    
    std::string currency1 = "PLN";
    std::string currency2 = "USD";

    std::string result = currency_comparison(currency1, currency2, false);
	BOOST_CHECK_EQUAL(result, "4.56");

    std::code_result(currency1, currency2, true);
    BOOST_CHECK_EQUAL(code_result, "USD");

    exec_func = exec;

}


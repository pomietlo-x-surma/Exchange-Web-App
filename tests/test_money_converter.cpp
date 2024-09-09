#pragma once

#define BOOST_TEST_MODULE AppTest
#include <boost/test/included/unit_test.hpp>
#include "../src/modules/money_converter.hpp"  

inline std::string mock_exec(const char* cmd) {
    return "4.56 chart";
}

BOOST_AUTO_TEST_CASE(TestCurrencyComparisonWithMockExec) {
    exec_func = mock_exec;

    std::string currency1 = "PLN";
    std::string currency2 = "USD";

    std::string result = currency_comparison(currency1, currency2, false);
    BOOST_CHECK_EQUAL(result, "4.56");

    std::string code_result = currency_comparison(currency1, currency2, true);
    BOOST_CHECK_EQUAL(code_result, "chart");

    exec_func = exec;
}



BOOST_AUTO_TEST_CASE(test_currency_comparison_integration)
{
    std::string currency1 = "PLN";
    std::string currency2 = "USD";

    std::string result = currency_comparison(currency1, currency2, false);
    BOOST_CHECK(!result.empty());
    
    std::string code_result = currency_comparison(currency1, currency2, true);
    BOOST_CHECK(!code_result.empty()); 

}

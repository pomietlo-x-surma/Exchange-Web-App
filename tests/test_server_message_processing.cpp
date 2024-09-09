#pragma once

#include <boost/test/included/unit_test.hpp>
#include "../src/modules/server_message_processing.hpp"

BOOST_AUTO_TEST_CASE(TestPositiveNumber) {
    BOOST_CHECK_EQUAL(to_string_with_precision(2.312, 1), "2.3");
}

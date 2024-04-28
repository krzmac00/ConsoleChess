#include <boost/test/unit_test.hpp>
#include "typedefs.h"

struct TestSuiteEnumFixture {
    Color color;

    TestSuiteEnumFixture() {
        color = WHITE;
    }

    ~TestSuiteEnumFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteEnum, TestSuiteEnumFixture)

BOOST_AUTO_TEST_CASE(OperatorPlusPlusTest) {
    BOOST_REQUIRE_EQUAL(color, WHITE);
    BOOST_REQUIRE_EQUAL(color++, BLACK);
}

BOOST_AUTO_TEST_CASE(OperatorOstreamTest) {
    std::ostringstream buf;
    buf << color;
    BOOST_REQUIRE_EQUAL(buf.str(), "WHITE");
        color = BLACK;
    buf.str("");
    buf << color;
    BOOST_REQUIRE_EQUAL(buf.str(), "BLACK");
}

BOOST_AUTO_TEST_SUITE_END()
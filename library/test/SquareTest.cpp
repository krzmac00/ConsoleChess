#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Players/HumanPlayer.h"
#include "Pieces/Pawn.h"


struct TestSuiteSquareFixture {
    SquarePtr square;
    PlayerPtr player;
    int row = 1;
    int column = 1;

    TestSuiteSquareFixture() {
        square = std::make_shared<Square>(row, column);
        player = std::make_shared<HumanPlayer>("Player_1", WHITE);
    }

    ~TestSuiteSquareFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteSquare, TestSuiteSquareFixture)

    BOOST_AUTO_TEST_CASE(constructorTest) {
        BOOST_REQUIRE_EQUAL(square->getRow(), row);
        BOOST_REQUIRE_EQUAL(square->getColumn(), column);
    }

    BOOST_AUTO_TEST_CASE(setPieceTest) {
        PiecePtr piece = std::make_shared<Pawn>(player, nullptr);
        square->setPiece(piece);
        BOOST_REQUIRE_EQUAL(square->getPiece(), piece);
    }

    BOOST_AUTO_TEST_CASE(toStringTest) {
        std::string abbr = square->toString();
        BOOST_TEST(abbr == "B7");
    }

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Check.h"
#include "Pieces/Queen.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteCheckFixture {
    CheckPtr check;
    PlayerPtr player;
    SquarePtr square;
    PiecePtr piece;

    TestSuiteCheckFixture() {
        check = std::make_shared<Check>();
        player = std::make_shared<HumanPlayer>("Player_1", WHITE);
        square = std::make_shared<Square>(1, 1);
        piece = std::make_shared<Queen>(player, square);
    }

    ~TestSuiteCheckFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCheck, TestSuiteCheckFixture)

    BOOST_AUTO_TEST_CASE(constructorTest) {
        BOOST_REQUIRE_EQUAL(check->isCheck(), false);
        BOOST_REQUIRE_EQUAL(check->getCheckingPiece(), nullptr);
    }

    BOOST_AUTO_TEST_CASE(settersTest) {
        check->setCheck(true);
        BOOST_REQUIRE_EQUAL(check->isCheck(), true);

        check->setCheckingPiece(piece);
        BOOST_REQUIRE_EQUAL(check->getCheckingPiece(), piece);
    }
BOOST_AUTO_TEST_SUITE_END()
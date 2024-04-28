#include <boost/test/unit_test.hpp>
#include "Players/HumanPlayer.h"
#include "typedefs.h"
#include "Pieces/King.h"
#include "Square.h"

struct TestSuiteHumanPlayerFixture {
    PlayerPtr blackPlayer;
    PlayerPtr whitePlayer;

    TestSuiteHumanPlayerFixture() {
        blackPlayer = std::make_shared<HumanPlayer>("blackPlayer", BLACK);
        whitePlayer = std::make_shared<HumanPlayer>("player", WHITE);
    }

    ~TestSuiteHumanPlayerFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteHumanPlayer, TestSuiteHumanPlayerFixture)

    BOOST_AUTO_TEST_CASE(getColorTest) {
        BOOST_REQUIRE_EQUAL(blackPlayer->getColor(), BLACK);
        BOOST_REQUIRE_EQUAL(whitePlayer->getColor(), WHITE);
    }

    BOOST_AUTO_TEST_CASE(getNameTest) {
        BOOST_REQUIRE_EQUAL(blackPlayer->getName(), "blackPlayer");
        BOOST_REQUIRE_EQUAL(whitePlayer->getName(), "player");
    }

    BOOST_AUTO_TEST_CASE(addMoveTest) {
        whitePlayer->addMove("A7-B3");
        whitePlayer->addMove("G2-E1");
        std::vector<std::string> moves = whitePlayer->getMoves();
        BOOST_REQUIRE_EQUAL(moves[0], "A7-B3");
        BOOST_REQUIRE_EQUAL(moves[1], "G2-E1");
    }

    BOOST_AUTO_TEST_CASE(addCapturedPieceTest) {
        whitePlayer->addCapturedPiece("Pawn");
        whitePlayer->addCapturedPiece("Queen");
        std::vector<std::string> pieces = whitePlayer->getCapturedPieces();
        BOOST_REQUIRE_EQUAL(pieces[0], "Pawn");
        BOOST_REQUIRE_EQUAL(pieces[1], "Queen");
    }

    BOOST_AUTO_TEST_CASE(getLastMoveTest) {
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
        whitePlayer->addMove("A7-B3");
        whitePlayer->addMove("G2-E1");
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "G2-E1");
    }

    BOOST_AUTO_TEST_CASE(getKingTest) {
        SquarePtr square = std::make_shared<Square>(0, 0);
        PiecePtr king = std::make_shared<King>(whitePlayer, square);
        whitePlayer->setKing(king);
        BOOST_REQUIRE_EQUAL(whitePlayer->getKing(), king);
    }

BOOST_AUTO_TEST_SUITE_END()

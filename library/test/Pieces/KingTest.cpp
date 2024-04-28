#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Pieces/King.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteKingFixture {
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuiteKingFixture() {
        board = std::make_shared<Board>();
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuiteKingFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteKing, TestSuiteKingFixture)

    BOOST_AUTO_TEST_CASE(setSquareTest) {
        PiecePtr king = std::make_shared<King>(whitePlayer, square0);
        king->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(king->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveInAllDirectionsPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::King, whitePlayer, 4, 3);
        bool moveRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(4, 4), board);
        bool moveLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(4, 2), board);
        bool moveUpwards = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 3), board);
        bool moveDownwards = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(5, 3), board);
        bool moveUpwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 4), board);
        bool moveUpwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 2), board);
        bool moveDownwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(5, 2), board);
        bool moveDownwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(5, 4), board);
        BOOST_REQUIRE_EQUAL(moveRight, true);
        BOOST_REQUIRE_EQUAL(moveLeft, true);
        BOOST_REQUIRE_EQUAL(moveUpwards, true);
        BOOST_REQUIRE_EQUAL(moveDownwards, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsRight, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveDownwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveDownwardsRight, true);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::King, whitePlayer, 2, 1);
        bool move1 = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(4, 1), board);
        bool move2 = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 3), board);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::King, whitePlayer, 5, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 5, 1);
        PiecePtr pawn = board->getSquare(5, 1)->getPiece();
        PiecePtr king = board->getSquare(5, 0)->getPiece();
        bool capture = board->getSquare(5, 0)->getPiece()->canBeMovedToSquare(board->getSquare(5, 1), board);
        BOOST_REQUIRE_EQUAL(capture, true);
    }

BOOST_AUTO_TEST_SUITE_END()

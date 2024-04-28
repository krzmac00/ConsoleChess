#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Pieces/Queen.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteQueenFixture {
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuiteQueenFixture() {
        board = std::make_shared<Board>();
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuiteQueenFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteHetman, TestSuiteQueenFixture)

    BOOST_AUTO_TEST_CASE(setsquareTest) {
        PiecePtr queen = std::make_shared<Queen>(whitePlayer, square0);
        queen->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveUpwardsLeftPositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(1, 0), board);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveUpwardsRightPositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 4), board);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveDoDoluRightPositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(6, 5), board);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveDoDoluLeftPositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(7, 0), board);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveWhenPieceOnWayNegativeTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 2, 5);
        board->addPiece(PieceType::Pawn, whitePlayer, 1, 3);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 3);
        bool move1 = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(1, 6), board);
        bool move2 = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(0, 3), board);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(moveRankPositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 4, 0);
        board->addPiece(PieceType::Queen, whitePlayer, 3, 7);
        bool moveRight = board->getSquare(4, 0)->getPiece()->canBeMovedToSquare(board->getSquare(4, 7), board);
        bool moveLeft = board->getSquare(3, 7)->getPiece()->canBeMovedToSquare(board->getSquare(3, 0), board);
        BOOST_REQUIRE_EQUAL(moveRight, true);
        BOOST_REQUIRE_EQUAL(moveLeft, true);
    }

    BOOST_AUTO_TEST_CASE(moveFilePositiveTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 2, 1);
        board->addPiece(PieceType::Queen, whitePlayer, 7, 0);
        bool moveDownwards = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(7, 1), board);
        bool moveUpwards = board->getSquare(7, 0)->getPiece()->canBeMovedToSquare(board->getSquare(0, 0), board);
        BOOST_REQUIRE_EQUAL(moveDownwards, true);
        BOOST_REQUIRE_EQUAL(moveUpwards, true);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 0, 2);
        bool move1 = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(4, 3), board);
        bool move2 = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(1, 4), board);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(moveRankNegativeTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 2, 1);
        board->addPiece(PieceType::Queen, blackPlayer, 2, 3);
        bool isCorrect = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 5), board);
        BOOST_REQUIRE_EQUAL(isCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(moveFileNegativeTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 0, 2);
        board->addPiece(PieceType::Queen, blackPlayer, 2, 2);
        bool isCorrect = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(6, 2), board);
        BOOST_REQUIRE_EQUAL(isCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Queen, whitePlayer, 3, 3);
        board->addPiece(PieceType::Queen, whitePlayer, 3, 6);
        board->addPiece(PieceType::Queen, blackPlayer, 1, 1);
        PiecePtr queen33 = board->getSquare(3, 3)->getPiece();
        PiecePtr queen36 = board->getSquare(3, 6)->getPiece();
        PiecePtr capturingQueen = board->getSquare(1, 1)->getPiece();
        bool capture33 = board->getSquare(1, 1)->getPiece()->canBeMovedToSquare(board->getSquare(3, 3), board);
        bool capture36 = board->getSquare(3, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 6), board);
        BOOST_REQUIRE_EQUAL(capture33, true);
        BOOST_REQUIRE_EQUAL(capture36, true);
    }

BOOST_AUTO_TEST_SUITE_END()
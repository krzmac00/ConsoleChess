#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "GameData.h"
#include "Pieces/Knight.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteKnightFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuiteKnightFixture() {
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(std::make_shared<Board>(), whitePlayer, blackPlayer, whitePlayer);
        board = gameData->getBoard();
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuiteKnightFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteKnight, TestSuiteKnightFixture)

    BOOST_AUTO_TEST_CASE(setSquareTest) {
        PiecePtr knight = std::make_shared<Knight>(whitePlayer, square0);
        knight->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(knight->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveThatChangesColumnBy2PositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Knight, whitePlayer, 4, 3);
        bool moveDownwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(5, 1), gameData);
        bool moveUpwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 5), gameData);
        bool moveUpwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 1), gameData);
        bool moveDownwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(5, 5), gameData);
        BOOST_REQUIRE_EQUAL(moveDownwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsRight, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveDownwardsRight, true);
    }

    BOOST_AUTO_TEST_CASE(moveThatChangesRowBy2PositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Knight, whitePlayer, 4, 3);
        bool moveDownwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(6, 2), gameData);
        bool moveUpwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(2, 4), gameData);
        bool moveUpwardsLeft = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(2, 2), gameData);
        bool moveDownwardsRight = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(6, 4), gameData);
        BOOST_REQUIRE_EQUAL(moveDownwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsRight, true);
        BOOST_REQUIRE_EQUAL(moveUpwardsLeft, true);
        BOOST_REQUIRE_EQUAL(moveDownwardsRight, true);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Knight, whitePlayer, 0, 1);
        bool move1 = board->getSquare(0, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 1), gameData);
        bool move2 = board->getSquare(0, 1)->getPiece()->canBeMovedToSquare(board->getSquare(3, 2), gameData);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Knight, whitePlayer, 4, 3);
        board->addPiece(PieceType::Knight, blackPlayer, 6, 2);
        PiecePtr capturedPiece = board->getSquare(6, 2)->getPiece();
        PiecePtr capturingPiece = board->getSquare(4, 3)->getPiece();
        bool capture = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(6, 2), gameData);
        BOOST_REQUIRE_EQUAL(capture, true);
    }

BOOST_AUTO_TEST_SUITE_END()

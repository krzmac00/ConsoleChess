#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "GameData.h"
#include "Pieces/Rook.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteRookFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuiteRookFixture() {
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(std::make_shared<Board>(), whitePlayer, blackPlayer, whitePlayer);
        board = gameData->getBoard();
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuiteRookFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRook, TestSuiteRookFixture)

    BOOST_AUTO_TEST_CASE(setSquareTest) {
        PiecePtr rook = std::make_shared<Rook>(whitePlayer, square0);
        rook->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(rook->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveRankPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 0);
        board->addPiece(PieceType::Rook, whitePlayer, 3, 7);
        bool moveRight= board->getSquare(4, 0)->getPiece()->canBeMovedToSquare(board->getSquare(4, 7), gameData);
        bool moveLeft= board->getSquare(3, 7)->getPiece()->canBeMovedToSquare(board->getSquare(3, 2), gameData);
        BOOST_REQUIRE_EQUAL(moveRight, true);
        BOOST_REQUIRE_EQUAL(moveLeft, true);
    }

    BOOST_AUTO_TEST_CASE(moveFilePositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 1);
        board->addPiece(PieceType::Rook, whitePlayer, 7, 6);
        bool moveUpwards = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 6), gameData);
        bool moveDownwards = board->getSquare(7, 6)->getPiece()->canBeMovedToSquare(board->getSquare(1, 6), gameData);
        BOOST_REQUIRE_EQUAL(moveUpwards, true);
        BOOST_REQUIRE_EQUAL(moveDownwards, true);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 2);
        bool move1 = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(4, 3), gameData);
        bool move2 = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(1, 3), gameData);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(moveRankNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 1);
        board->addPiece(PieceType::Rook, blackPlayer, 2, 3);
        bool isCorrect = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 5), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(moveFileNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 2);
        board->addPiece(PieceType::Rook, blackPlayer, 2, 2);
        bool isCorrect = board->getSquare(0, 2)->getPiece()->canBeMovedToSquare(board->getSquare(6, 2), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Rook, whitePlayer, 5, 0);
        board->addPiece(PieceType::Rook, blackPlayer, 5, 3);
        PiecePtr capturedPiece = board->getSquare(5, 3)->getPiece();
        PiecePtr capturingPiece = board->getSquare(5, 0)->getPiece();
        bool capture = board->getSquare(5, 0)->getPiece()->canBeMovedToSquare(board->getSquare(5, 3), gameData);
        BOOST_REQUIRE_EQUAL(capture, true);
    }

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "GameData.h"
#include "Pieces/Bishop.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"

struct TestSuiteBishopFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuiteBishopFixture() {
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(std::make_shared<Board>(), whitePlayer, blackPlayer, whitePlayer);
        board = gameData->getBoard();
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuiteBishopFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteBishop, TestSuiteBishopFixture)

    BOOST_AUTO_TEST_CASE(setQuareTest) {
        PiecePtr bishop = std::make_shared<Bishop>(whitePlayer, square0);
        bishop->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(bishop->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveUpwardsLeftPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Bishop, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(1, 0), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveUpwardsRightPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Bishop, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(3, 4), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveDownwardsRightPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Bishop, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(6, 5), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveDownwardsLeftPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Bishop, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(7, 0), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Bishop, whitePlayer, 1, 1);
        bool move1 = board->getSquare(1, 1)->getPiece()->canBeMovedToSquare(board->getSquare(3, 2), gameData);
        bool move2 = board->getSquare(1, 1)->getPiece()->canBeMovedToSquare(board->getSquare(1, 3), gameData);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(ruchGdyFiguraNaDrodzeNegatywnyTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 2, 5);
        board->addPiece(PieceType::Bishop, whitePlayer, 4, 3);
        bool isCorrect = board->getSquare(4, 3)->getPiece()->canBeMovedToSquare(board->getSquare(1, 6), gameData);
        BOOST_REQUIRE_EQUAL(isCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 5, 2);
        board->addPiece(PieceType::Bishop, blackPlayer, 3, 0);
        PiecePtr pawn = board->getSquare(5, 2)->getPiece();
        PiecePtr bishop = board->getSquare(3, 0)->getPiece();
        bool capture = board->getSquare(3, 0)->getPiece()->canBeMovedToSquare(board->getSquare(5, 2), gameData);
        BOOST_REQUIRE_EQUAL(capture, true);
    }

BOOST_AUTO_TEST_SUITE_END()
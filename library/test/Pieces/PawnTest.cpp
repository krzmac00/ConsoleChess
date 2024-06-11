#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Pieces/Pawn.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Square.h"
#include "GameData.h"

struct TestSuitePawnFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    SquarePtr square0;
    SquarePtr square1;

    TestSuitePawnFixture() {
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(std::make_shared<Board>(), whitePlayer, blackPlayer, whitePlayer);
        board = gameData->getBoard();
        square0 = std::make_shared<Square>(5, 0);
        square1 = std::make_shared<Square>(2, 0);
    }

    ~TestSuitePawnFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePawn, TestSuitePawnFixture)

    BOOST_AUTO_TEST_CASE(setSquareTest) {
        PiecePtr pawn = std::make_shared<Pawn>(whitePlayer, square0);
        pawn->setSquare(square1);
        BOOST_REQUIRE_EQUAL(square0->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), square1);
    }

    BOOST_AUTO_TEST_CASE(moveForwards1PositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 1, 4);
        bool moveWhiteCorrect = board->getSquare(6, 0)->getPiece()->canBeMovedToSquare(board->getSquare(5, 0), gameData);
        bool moveBlackCorrect = board->getSquare(1, 4)->getPiece()->canBeMovedToSquare(board->getSquare(2, 4), gameData);
        BOOST_REQUIRE_EQUAL(moveWhiteCorrect, true);
        BOOST_REQUIRE_EQUAL(moveBlackCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveForwards1NegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 5, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 1, 4);
        board->addPiece(PieceType::Pawn, whitePlayer, 2, 4);
        bool moveWhiteCorrect = board->getSquare(6, 0)->getPiece()->canBeMovedToSquare(board->getSquare(5, 0), gameData);
        bool moveBlackCorrect = board->getSquare(1, 4)->getPiece()->canBeMovedToSquare(board->getSquare(2, 4), gameData);
        BOOST_REQUIRE_EQUAL(moveWhiteCorrect, false);
        BOOST_REQUIRE_EQUAL(moveBlackCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(moveDoTyluTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 5, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 2, 4);
        bool moveWhiteCorrect = board->getSquare(5, 0)->getPiece()->canBeMovedToSquare(board->getSquare(6, 0), gameData);
        bool moveBlackCorrect = board->getSquare(2, 4)->getPiece()->canBeMovedToSquare(board->getSquare(1, 4), gameData);
        BOOST_REQUIRE_EQUAL(moveWhiteCorrect, false);
        BOOST_REQUIRE_EQUAL(moveBlackCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(moveForwards2PositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 1, 0);
        bool moveWhiteCorrect = board->getSquare(6, 0)->getPiece()->canBeMovedToSquare(board->getSquare(4, 0), gameData);
        bool moveBlackCorrect = board->getSquare(1, 0)->getPiece()->canBeMovedToSquare(board->getSquare(3, 0), gameData);
        BOOST_REQUIRE_EQUAL(moveWhiteCorrect, true);
        BOOST_REQUIRE_EQUAL(moveBlackCorrect, true);
    }

    BOOST_AUTO_TEST_CASE(moveForwards2NegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 1);
        board->addPiece(PieceType::Pawn, blackPlayer, 1, 0);
        bool moveWhiteCorrect = board->getSquare(6, 1)->getPiece()->canBeMovedToSquare(board->getSquare(3, 1), gameData);
        bool moveBlackCorrect = board->getSquare(1, 0)->getPiece()->canBeMovedToSquare(board->getSquare(4, 0), gameData);
        BOOST_REQUIRE_EQUAL(moveWhiteCorrect, false);
        BOOST_REQUIRE_EQUAL(moveBlackCorrect, false);
    }

    BOOST_AUTO_TEST_CASE(moveNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 1);
        bool move1 = board->getSquare(6, 1)->getPiece()->canBeMovedToSquare(board->getSquare(6, 2), gameData);
        bool move2 = board->getSquare(6, 1)->getPiece()->canBeMovedToSquare(board->getSquare(4, 3), gameData);
        BOOST_REQUIRE_EQUAL(move1, false);
        BOOST_REQUIRE_EQUAL(move2, false);
    }

    BOOST_AUTO_TEST_CASE(capturePieceTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, whitePlayer, 2, 1);
        board->addPiece(PieceType::Pawn, blackPlayer, 1, 0);
        PiecePtr capturedPiece = board->getSquare(1, 0)->getPiece();
        PiecePtr capturingPiece = board->getSquare(2, 1)->getPiece();
        bool capture = board->getSquare(2, 1)->getPiece()->canBeMovedToSquare(board->getSquare(1, 0), gameData);
        BOOST_REQUIRE_EQUAL(capture, true);
    }

    BOOST_AUTO_TEST_CASE(enPassanPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        //white pawn captures black pawn
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 1);
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 0);
        MovePtr moveBlack = std::make_shared<Move>("A7-A5", board, blackPlayer);
        gameData->addMove(moveBlack);
        PiecePtr capturedBlack = board->getSquare(3, 0)->getPiece();
        PiecePtr capturingWhite = board->getSquare(3, 1)->getPiece();
        bool captureBlack = board->getSquare(3, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 0), gameData);
        BOOST_REQUIRE_EQUAL(captureBlack, true);
        //black pawn captures white pawn
        board->addPiece(PieceType::Pawn, whitePlayer, 4, 7);
        board->addPiece(PieceType::Pawn, blackPlayer, 4, 6);
        MovePtr moveWhite = std::make_shared<Move>("H2-H4", board, whitePlayer);
        gameData->addMove(moveWhite);
        PiecePtr capturedWhite = board->getSquare(4, 7)->getPiece();
        PiecePtr capturingBlack = board->getSquare(4, 6)->getPiece();
        bool captureWhite = board->getSquare(4, 6)->getPiece()->canBeMovedToSquare(board->getSquare(5, 7), gameData);
        BOOST_REQUIRE_EQUAL(captureWhite, true);

    }
    BOOST_AUTO_TEST_CASE(enPassantNegativeTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        //piece different from pawn
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 1);
        board->addPiece(PieceType::Queen, blackPlayer, 3, 0);
        MovePtr moveBlack = std::make_shared<Move>("A7-A5", board, blackPlayer);
        gameData->addMove(moveBlack);
        PiecePtr queen = board->getSquare(3, 0)->getPiece();
        PiecePtr pawn = board->getSquare(3, 1)->getPiece();
        bool capture = board->getSquare(3, 1)->getPiece()->canBeMovedToSquare(board->getSquare(2, 0), gameData);
        BOOST_REQUIRE_EQUAL(capture, false);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(3, 0));
        BOOST_REQUIRE_EQUAL(queen->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), board->getSquare(3, 1));
        //one move after en passant was possible
        board->addPiece(PieceType::Pawn, whitePlayer, 4, 7);
        board->addPiece(PieceType::Pawn, blackPlayer, 4, 6);
        MovePtr moveWhite = std::make_shared<Move>("A2-H4", board, whitePlayer);
        gameData->addMove(moveWhite);
        PiecePtr white = board->getSquare(4, 7)->getPiece();
        PiecePtr capturingBlack = board->getSquare(4, 6)->getPiece();
        bool captureWhite = board->getSquare(4, 6)->getPiece()->canBeMovedToSquare(board->getSquare(5, 7), gameData);
        BOOST_REQUIRE_EQUAL(captureWhite, false);
        BOOST_REQUIRE_EQUAL(white->getSquare(), board->getSquare(4, 7));
        BOOST_REQUIRE_EQUAL(white->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(capturingBlack->getSquare(), board->getSquare(4, 6));

    }



BOOST_AUTO_TEST_SUITE_END()
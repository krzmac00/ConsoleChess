#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Move.h"
#include "Board.h"
#include "GameData.h"
#include "Square.h"
#include "Players/HumanPlayer.h"

struct TestSuiteMoveFixture {
    GameDataPtr gameData;
    BoardPtr board;
    SquarePtr fromSquare;
    SquarePtr toSquare;
    MovePtr move;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;

    TestSuiteMoveFixture() {
        fromSquare = std::make_shared<Square>(0, 0);
        toSquare = std::make_shared<Square>(3, 3);
        whitePlayer = std::make_shared<HumanPlayer>("Player_1", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player_2", BLACK);
        gameData = std::make_shared<GameData>(std::make_shared<Board>(), whitePlayer, blackPlayer, whitePlayer);
        board = gameData->getBoard();
        move = std::make_shared<Move>(fromSquare, toSquare, whitePlayer);

        for(int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                board->addSquare(x, y);
    }

    ~TestSuiteMoveFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteMove, TestSuiteMoveFixture)

    BOOST_AUTO_TEST_CASE(squaresConstructorTest) {
        BOOST_REQUIRE_EQUAL(move->getFrom(), fromSquare);
        BOOST_REQUIRE_EQUAL(move->getTo(), toSquare);
        BOOST_REQUIRE_EQUAL(move->getPlayer(), whitePlayer);
    }

    BOOST_AUTO_TEST_CASE(stringBoardConstructorTest) {
        MovePtr moveString = std::make_shared<Move>("A5-B3", board, whitePlayer);
        BOOST_REQUIRE_EQUAL(moveString->getFrom(), board->getSquare(3, 0));
        BOOST_REQUIRE_EQUAL(moveString->getTo(), board->getSquare(5, 1));
    }

    BOOST_AUTO_TEST_CASE(stringConstructorTest) {
        std::string test = "O-O-O";
        MovePtr moveString = std::make_shared<Move>(test, whitePlayer);
        BOOST_REQUIRE_EQUAL(moveString->getAbbr(), test);
    }

    BOOST_AUTO_TEST_CASE(getAbbrTest) {
        BOOST_REQUIRE_EQUAL(move->getAbbr(), "A8-D5");
    }

    BOOST_AUTO_TEST_CASE(executeShortCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        PiecePtr rook = board->getSquare(7, 7)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O", whitePlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 6)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 5)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 6));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), castling->getAbbr());
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        rook = board->getSquare(0, 7)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O", blackPlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 6)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 6));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 7)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), castling->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeLongCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        PiecePtr rook = board->getSquare(7, 0)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O-O", whitePlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 2)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 3)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 2));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 3));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), castling->getAbbr());
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        rook = board->getSquare(0, 0)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O-O", blackPlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 2)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 3)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 2));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 3));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), castling->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeMoveWithoutCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 0, 0);
        PiecePtr queen = board->getSquare(0, 0)->getPiece();
        MovePtr moveWithoutCapture = std::make_shared<Move>(board->getSquare(0, 0), board->getSquare(0, 5), whitePlayer);
        moveWithoutCapture->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(0, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), moveWithoutCapture->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeEnPassantTest) {
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 3);
        PiecePtr whitePawn = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr blackPawn = board->getSquare(3, 2)->getPiece();
        MovePtr enPassant  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(2, 2), whitePlayer);
        enPassant->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(2, 2)->getPiece(), whitePawn);
        BOOST_REQUIRE_EQUAL(whitePawn->getSquare(), board->getSquare(2, 2));
        BOOST_REQUIRE_EQUAL(blackPawn->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPawn->isCaptured(), true);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), enPassant->getAbbr());
        std::string abbr;
        for(auto &fig : board->getPiecesCapturedByPlayer(whitePlayer)) abbr = fig->getAbbr();
        BOOST_REQUIRE_EQUAL(abbr, "BP");
    }

    BOOST_AUTO_TEST_CASE(executeCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 3, 3);
        PiecePtr queen = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr pawn = board->getSquare(3, 2)->getPiece();
        MovePtr capture  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(3, 2), whitePlayer);
        capture->execute(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(pawn->isCaptured(), true);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove()->getAbbr(), capture->getAbbr());
        std::string abbr;
        for(auto &fig : board->getPiecesCapturedByPlayer(whitePlayer)) abbr = fig->getAbbr();
        BOOST_REQUIRE_EQUAL(abbr, "BP");
    }

    BOOST_AUTO_TEST_CASE(undoShortCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        PiecePtr rook = board->getSquare(7, 7)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O", whitePlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 7));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 6)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        rook = board->getSquare(0, 7)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O", blackPlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 7)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 7));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 6)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
    }

    BOOST_AUTO_TEST_CASE(undoLongCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        PiecePtr rook = board->getSquare(7, 0)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O-O", whitePlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 0)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        rook = board->getSquare(0, 0)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O-O", blackPlayer);
        castling->execute(gameData);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
    }

    BOOST_AUTO_TEST_CASE(undoMoveWithoutCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 0, 0);
        PiecePtr queen = board->getSquare(0, 0)->getPiece();
        MovePtr moveWithoutCapture = std::make_shared<Move>(board->getSquare(0, 0), board->getSquare(0, 5), whitePlayer);
        moveWithoutCapture->execute(gameData);
        moveWithoutCapture->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(0, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
    }

    BOOST_AUTO_TEST_CASE(undoMoveenPassantTest) {
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 3);
        PiecePtr whitePawn = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr blackPawn = board->getSquare(3, 2)->getPiece();
        MovePtr enPassant  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(2, 2), whitePlayer);
        enPassant->execute(gameData);
        enPassant->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), whitePawn);
        BOOST_REQUIRE_EQUAL(whitePawn->getSquare(), board->getSquare(3, 3));
        BOOST_REQUIRE_EQUAL(blackPawn->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(blackPawn->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), blackPawn);
        BOOST_REQUIRE_EQUAL(board->getSquare(2, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getPiecesCapturedByPlayer(whitePlayer).size(), 0);
    }

    BOOST_AUTO_TEST_CASE(undoMoveCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 3, 3);
        PiecePtr queen = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr pawn = board->getSquare(3, 2)->getPiece();
        MovePtr capture  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(3, 2), whitePlayer);
        capture->execute(gameData);
        capture->undo(gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(3, 3));
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), pawn);
        BOOST_REQUIRE_EQUAL(pawn->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(queen->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getPiecesCapturedByPlayer(whitePlayer).size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()
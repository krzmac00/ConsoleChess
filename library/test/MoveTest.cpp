#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Move.h"
#include "Board.h"
#include "Square.h"
#include "Players/HumanPlayer.h"

struct TestSuiteMoveFixture {
    BoardPtr board;
    SquarePtr fromSquare;
    SquarePtr toSquare;
    MovePtr move;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;

    TestSuiteMoveFixture() {
        board = std::make_shared<Board>();
        fromSquare = std::make_shared<Square>(0, 0);
        toSquare = std::make_shared<Square>(3, 3);
        move = std::make_shared<Move>(fromSquare, toSquare);
        whitePlayer = std::make_shared<HumanPlayer>("Player_1", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player_2", BLACK);

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
    }

    BOOST_AUTO_TEST_CASE(stringBoardConstructorTest) {
        MovePtr moveString = std::make_shared<Move>("A5-B3", board);
        BOOST_REQUIRE_EQUAL(moveString->getFrom(), board->getSquare(3, 0));
        BOOST_REQUIRE_EQUAL(moveString->getTo(), board->getSquare(5, 1));
    }

    BOOST_AUTO_TEST_CASE(stringConstructorTest) {
        std::string test = "O-O-O";
        MovePtr moveString = std::make_shared<Move>(test);
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
        MovePtr castling = std::make_shared<Move>("O-O");
        castling->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 6)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 5)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 6));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), castling->getAbbr());
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        rook = board->getSquare(0, 7)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O");
        castling->execute(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 6)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 6));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 7)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPlayer->getLastMove(), castling->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeLongCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        PiecePtr rook = board->getSquare(7, 0)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O-O");
        castling->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 2)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 3)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 2));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 3));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), castling->getAbbr());
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        rook = board->getSquare(0, 0)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling = std::make_shared<Move>("O-O-O");
        castling->execute(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 2)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 3)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 2));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 3));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPlayer->getLastMove(), castling->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeMoveWithoutCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 0, 0);
        PiecePtr queen = board->getSquare(0, 0)->getPiece();
        MovePtr moveWithoutCapture = std::make_shared<Move>(board->getSquare(0, 0), board->getSquare(0, 5));
        moveWithoutCapture->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(0, 5));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), moveWithoutCapture->getAbbr());
    }

    BOOST_AUTO_TEST_CASE(executeEnPassantTest) {
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 3);
        PiecePtr whitePawn = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr blackPawn = board->getSquare(3, 2)->getPiece();
        MovePtr enPassant  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(2, 2));
        enPassant->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(2, 2)->getPiece(), whitePawn);
        BOOST_REQUIRE_EQUAL(whitePawn->getSquare(), board->getSquare(2, 2));
        BOOST_REQUIRE_EQUAL(blackPawn->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPawn->isCaptured(), true);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), enPassant->getAbbr());
        std::string abbr;
        for(auto &fig : whitePlayer->getCapturedPieces()) abbr = fig;
        BOOST_REQUIRE_EQUAL(abbr, "BP");
    }

    BOOST_AUTO_TEST_CASE(executeCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 3, 3);
        PiecePtr queen = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr pawn = board->getSquare(3, 2)->getPiece();
        MovePtr capture  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(3, 2));
        capture->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(pawn->isCaptured(), true);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), capture->getAbbr());
        std::string abbr;
        for(auto &fig : whitePlayer->getCapturedPieces()) abbr = fig;
        BOOST_REQUIRE_EQUAL(abbr, "BP");
    }

    BOOST_AUTO_TEST_CASE(undoShortCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        PiecePtr rook = board->getSquare(7, 7)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O");
        castling->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 7));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 6)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        rook = board->getSquare(0, 7)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling->execute(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 7)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 7));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 6)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
    }

    BOOST_AUTO_TEST_CASE(undoLongCastlingTest) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        PiecePtr rook = board->getSquare(7, 0)->getPiece();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        PiecePtr king = board->getSquare(7, 4)->getPiece();
        MovePtr castling = std::make_shared<Move>("O-O-O");
        castling->execute(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 0)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(7, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(7, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        rook = board->getSquare(0, 0)->getPiece();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        king = board->getSquare(0, 4)->getPiece();
        castling->execute(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), false);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), false);
        castling->undo(blackPlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 4)->getPiece(), king);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), rook);
        BOOST_REQUIRE_EQUAL(king->getSquare(), board->getSquare(0, 4));
        BOOST_REQUIRE_EQUAL(rook->getSquare(), board->getSquare(0, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 3)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(blackPlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(king->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(rook->isFirstMove(), true);
    }

    BOOST_AUTO_TEST_CASE(cofnijmoveWithoutCaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 0, 0);
        PiecePtr queen = board->getSquare(0, 0)->getPiece();
        MovePtr moveWithoutCapture = std::make_shared<Move>(board->getSquare(0, 0), board->getSquare(0, 5));
        moveWithoutCapture->execute(whitePlayer, board);
        moveWithoutCapture->undo(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 5)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(0, 0));
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
    }

    BOOST_AUTO_TEST_CASE(cofnijmoveenPassantTest) {
        board->addPiece(PieceType::Pawn, whitePlayer, 3, 3);
        PiecePtr whitePawn = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr blackPawn = board->getSquare(3, 2)->getPiece();
        MovePtr enPassant  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(2, 2));
        enPassant->execute(whitePlayer, board);
        enPassant->undo(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), whitePawn);
        BOOST_REQUIRE_EQUAL(whitePawn->getSquare(), board->getSquare(3, 3));
        BOOST_REQUIRE_EQUAL(blackPawn->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(blackPawn->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), blackPawn);
        BOOST_REQUIRE_EQUAL(board->getSquare(2, 2)->getPiece(), nullptr);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(whitePlayer->getCapturedPieces().size(), 0);
    }

    BOOST_AUTO_TEST_CASE(cofnijmovecaptureTest) {
        board->addPiece(PieceType::Queen, whitePlayer, 3, 3);
        PiecePtr queen = board->getSquare(3, 3)->getPiece();
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 2);
        PiecePtr pawn = board->getSquare(3, 2)->getPiece();
        MovePtr capture  = std::make_shared<Move>(board->getSquare(3, 3), board->getSquare(3, 2));
        capture->execute(whitePlayer, board);
        capture->undo(whitePlayer, board);
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 3)->getPiece(), queen);
        BOOST_REQUIRE_EQUAL(queen->getSquare(), board->getSquare(3, 3));
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), board->getSquare(3, 2));
        BOOST_REQUIRE_EQUAL(board->getSquare(3, 2)->getPiece(), pawn);
        BOOST_REQUIRE_EQUAL(pawn->isCaptured(), false);
        BOOST_REQUIRE_EQUAL(queen->isFirstMove(), true);
        BOOST_REQUIRE_EQUAL(whitePlayer->getLastMove(), "");
        BOOST_REQUIRE_EQUAL(whitePlayer->getCapturedPieces().size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()
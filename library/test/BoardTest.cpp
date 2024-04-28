#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"
#include "Pieces/Pawn.h"


struct TestSuiteBoardFixture {
    Board* board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;


    TestSuiteBoardFixture() {
        board = new Board();
        whitePlayer = std::make_shared<HumanPlayer>("Player1", WHITE);
        blackPlayer = std::make_shared<ComputerPlayer>("ComputerPlayer", BLACK);
    }

    ~TestSuiteBoardFixture() {
        delete board;
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteBoard, TestSuiteBoardFixture)

    BOOST_AUTO_TEST_CASE(addSquareTest) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) {
                BOOST_REQUIRE_EQUAL(board->getSquare(i, j)->getRow(), i);
                BOOST_REQUIRE_EQUAL(board->getSquare(i, j)->getColumn(), j);
            }
    }

    BOOST_AUTO_TEST_CASE(addPieceTest) {
        board->addSquare(0, 0);
        board->addSquare(7, 7);
        board->addPiece(PieceType::Pawn, whitePlayer, 0, 0);
        board->addPiece(PieceType::Queen, blackPlayer, 7, 7);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getType(), PieceType::Pawn);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getPlayer(), whitePlayer);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece()->getType(), PieceType::Queen);
        BOOST_REQUIRE_EQUAL(board->getSquare(7, 7)->getPiece()->getPlayer(), blackPlayer);
    }

    BOOST_AUTO_TEST_CASE(getPiecesOfPlayerTest) {
        board->addSquare(0, 0);
        board->addSquare(0, 1);
        board->addSquare(0, 2);
        std::vector<PiecePtr> pieces;
        std::vector<PiecePtr> piecesTest;

        //piece1 type=Pawn player=player square=(0,0)
        PiecePtr piece1 = std::make_shared<Pawn>(whitePlayer, std::make_shared<Square>(0, 0));
        pieces.push_back(piece1);
        board->addPiece(piece1->getType(), piece1->getPlayer(),
                           piece1->getSquare()->getRow(),
                           piece1->getSquare()->getColumn());

        //piece2 type=Pawn player=blackPlayer square=(0,1)
        PiecePtr piece2 = std::make_shared<Pawn>(blackPlayer, std::make_shared<Square>(0, 1));
        pieces.push_back(piece2);
        board->addPiece(piece2->getType(), piece2->getPlayer(),
                           piece2->getSquare()->getRow(),
                           piece2->getSquare()->getColumn());

        //piece3 type=Pawn player=player square=(0,2)
        PiecePtr piece3 = std::make_shared<Pawn>(whitePlayer, std::make_shared<Square>(0, 2));
        pieces.push_back(piece3);
        board->addPiece(piece3->getType(), piece3->getPlayer(),
                           piece3->getSquare()->getRow(),
                           piece3->getSquare()->getColumn());

        piecesTest = board->getPiecesOfPlayer(whitePlayer);
        BOOST_REQUIRE_EQUAL(piecesTest.size(), 2);

        //piece1(pieces[0]==piecesTest[0]) type=Pawn player=player square=(0,0)
        BOOST_REQUIRE_EQUAL(pieces[0]->getType(), piecesTest[0]->getType());
        BOOST_REQUIRE_EQUAL(pieces[0]->getPlayer(), piecesTest[0]->getPlayer());
        BOOST_REQUIRE_EQUAL(pieces[0]->getSquare()->getRow(), piecesTest[0]->getSquare()->getRow());
        BOOST_REQUIRE_EQUAL(pieces[0]->getSquare()->getColumn(), piecesTest[0]->getSquare()->getColumn());

        //piece3(pieces[2]==piecesTest[1]) type=Pawn player=player square=(0,2)
        BOOST_REQUIRE_EQUAL(pieces[2]->getType(), piecesTest[1]->getType());
        BOOST_REQUIRE_EQUAL(pieces[2]->getPlayer(), piecesTest[1]->getPlayer());
        BOOST_REQUIRE_EQUAL(pieces[2]->getSquare()->getRow(), piecesTest[1]->getSquare()->getRow());
        BOOST_REQUIRE_EQUAL(pieces[2]->getSquare()->getColumn(), piecesTest[1]->getSquare()->getColumn());
    }

    BOOST_AUTO_TEST_CASE(deletePieceTest) {
        board->addSquare(0, 0);
        board->addSquare(0, 1);
        board->addSquare(0, 2);
        board->addPiece(PieceType::Pawn, whitePlayer, 0, 0);
        board->addPiece(PieceType::Pawn, blackPlayer, 0, 1);
        board->addPiece(PieceType::Pawn, whitePlayer, 0, 2);
        PiecePtr piece1 = board->getSquare(0, 0)->getPiece();
        BOOST_REQUIRE_EQUAL(board->getPieces().size(), 3);

        board->deletePiece(piece1);
        std::vector<PiecePtr> pieces = board->getPieces();
        BOOST_REQUIRE_EQUAL(pieces.size(), 2);
        for (auto& piece : pieces) {
            BOOST_TEST(piece != piece1);
        }
    }

    BOOST_AUTO_TEST_CASE(toStringTest) {
        //creating fields
        for(int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board->addSquare(i, j);
        //adding pawns
        for (int i = 0; i < 8; i++) {
            board->addPiece(PieceType::Pawn, whitePlayer, 6, i);
            board->addPiece(PieceType::Pawn, blackPlayer, 1, i);
        }
        //adding rooks
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        //adding knights
        board->addPiece(PieceType::Knight, whitePlayer, 7, 1);
        board->addPiece(PieceType::Knight, whitePlayer, 7, 6);
        board->addPiece(PieceType::Knight, blackPlayer, 0, 1);
        board->addPiece(PieceType::Knight, blackPlayer, 0, 6);
        //adding bishops
        board->addPiece(PieceType::Bishop, whitePlayer, 7, 2);
        board->addPiece(PieceType::Bishop, whitePlayer, 7, 5);
        board->addPiece(PieceType::Bishop, blackPlayer, 0, 2);
        board->addPiece(PieceType::Bishop, blackPlayer, 0, 5);
        //adding queens
        board->addPiece(PieceType::Queen, whitePlayer, 7, 3);
        board->addPiece(PieceType::Queen, blackPlayer, 0, 3);
        //adding kings
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        std::string expectedPiecesPositions = "BR BN BB BQ BK BB BN BR \n"
                                              "BP BP BP BP BP BP BP BP \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "WP WP WP WP WP WP WP WP \n"
                                              "WR WN WB WQ WK WB WN WR \n";
        BOOST_TEST(expectedPiecesPositions == board->toString());
    }

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Move.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Game/GameForTesting.h"
#include "View/TestView.h"
#include "Check.h"

struct TestSuiteBugFixture {
    GameForTesting* game;
    ViewPtr view;
    std::shared_ptr<TestView> viewTest;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;

    TestSuiteBugFixture() {
        view = std::make_shared<TestView>();
        viewTest = std::dynamic_pointer_cast<TestView>(view);
        board = std::make_shared<Board>();
        whitePlayer = std::make_shared<HumanPlayer>("Player_1", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player_2", BLACK);
        game = new GameForTesting(view);

        game->setBoard(board);
        for(int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                board->addSquare(x, y);
    }

    ~TestSuiteBugFixture() {
        delete game;
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteBug, TestSuiteBugFixture)

    BOOST_AUTO_TEST_CASE(segmentationFaultTest) {
        std::string moves = "G1-G2";
        viewTest->setMoves(moves);
        viewTest->setNewGame(false);
        viewTest->setFilePath("../../library/test/gameSaveFiles/testSegFault.txt");
        game->play();
        BOOST_TEST(true);
    }


    BOOST_AUTO_TEST_CASE(bishop20Pawn11Test) {
        board->addPiece(PieceType::Knight, blackPlayer, 2, 0);
        PiecePtr knight = board->getSquare(2, 0)->getPiece();

        board->addPiece(PieceType::Bishop, whitePlayer, 7, 5);
        PiecePtr bishop = board->getSquare(7, 5)->getPiece();

        board->addPiece(PieceType::Pawn, blackPlayer, 1, 1);
        PiecePtr pawn = board->getSquare(1, 1)->getPiece();

        auto fromSquare = board->getSquare(7, 5);
        auto toSquare = board->getSquare(2, 0);
        auto move = std::make_shared<Move>(fromSquare, toSquare);
        move->execute(whitePlayer, board);

        fromSquare = board->getSquare(1, 1);
        toSquare = board->getSquare(2, 0);
        move = std::make_shared<Move>(fromSquare, toSquare);
        move->execute(blackPlayer, board);

        BOOST_REQUIRE_EQUAL(pawn, board->getSquare(2, 0)->getPiece());
        BOOST_REQUIRE_EQUAL(bishop->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(knight->getSquare(), nullptr);
        BOOST_REQUIRE_EQUAL(pawn->getSquare(), board->getSquare(2, 0));

        move->undo(blackPlayer, board);

        BOOST_REQUIRE_EQUAL(pawn->getSquare(), board->getSquare(1, 1));
        BOOST_REQUIRE_EQUAL(pawn, board->getSquare(1, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(bishop->getSquare(), board->getSquare(2,0));
        BOOST_REQUIRE_EQUAL(bishop, board->getSquare(2, 0)->getPiece());
    }

BOOST_AUTO_TEST_SUITE_END()
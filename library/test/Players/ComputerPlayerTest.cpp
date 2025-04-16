#include <boost/test/unit_test.hpp>
#include "Players/ComputerPlayer.h"
#include "Board.h"
#include "View/ConsoleView.h"
#include "typedefs.h"

struct TestSuiteComputerPlayerFixture {
    PlayerPtr computerBlack;
    PlayerPtr computerWhite;
    BoardPtr board;
    ViewPtr view;

    TestSuiteComputerPlayerFixture() {
        computerBlack = std::make_shared<ComputerPlayer>("ComputerPlayer", BLACK);
        computerWhite = std::make_shared<ComputerPlayer>("ComputerPlayer", WHITE);
        board = std::make_shared<Board>();
        view = std::make_shared<ConsoleView>();
    }

    ~TestSuiteComputerPlayerFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteKomputer, TestSuiteComputerPlayerFixture)

    BOOST_AUTO_TEST_CASE(executeMoveBlackPositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, computerBlack, 1, 0);
        board->addPiece(PieceType::Pawn, computerBlack, 1, 7);

        MovePtr move = computerBlack->getMove(board, view);

        bool expectedFromSquareCorrect = false;
        if (move->getFrom()->getRow() == 1 &&
            (move->getFrom()->getColumn() == 0 || move->getFrom()->getColumn() == 7)) expectedFromSquareCorrect = true;
        BOOST_REQUIRE_EQUAL(expectedFromSquareCorrect, true);

        BOOST_TEST(move->getTo() != move->getFrom());
        MovePtr move2 = computerBlack->getMove(board, view);
        bool areMovesDifferent = move->getTo() != move2->getTo() || move->getFrom() !=
                                                                    move2->getFrom();
        BOOST_TEST(areMovesDifferent == true);
    }

    BOOST_AUTO_TEST_CASE(executeMoveWhitePositiveTest) {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                board->addSquare(i, j);
        board->addPiece(PieceType::Pawn, computerWhite, 6, 0);
        board->addPiece(PieceType::Pawn, computerWhite, 6, 7);

        MovePtr move = computerWhite->getMove(board, view);

        bool expectedFromSquareCorrect = false;
        if (move->getFrom()->getRow() == 6 &&
            (move->getFrom()->getColumn() == 0 || move->getFrom()->getColumn() == 7)) expectedFromSquareCorrect = true;
        BOOST_REQUIRE_EQUAL(expectedFromSquareCorrect, true);

        BOOST_TEST(move->getTo() != move->getFrom());
        MovePtr move2 = computerWhite->getMove(board, view);
        bool areMovesDifferent = move->getTo() != move2->getTo() || move->getFrom() !=
                                                                move2->getFrom();
        BOOST_TEST(areMovesDifferent == true);
    }

    BOOST_AUTO_TEST_CASE(promotionTest) {
        PieceType type = computerWhite->promotion(view);
        bool isTypeCorrect;
        switch(type){
            case PieceType::Knight:
            case PieceType::Rook:
            case PieceType::Bishop:
            case PieceType::Queen:
                isTypeCorrect = true;
                break;
            default:
                isTypeCorrect = false;
                break;
        }
        BOOST_REQUIRE_EQUAL(isTypeCorrect, true);
    }

BOOST_AUTO_TEST_SUITE_END()

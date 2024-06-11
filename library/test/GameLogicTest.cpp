#include <boost/test/unit_test.hpp>
#include "GameData.h"
#include "GameLogic.h"
#include "Players/HumanPlayer.h"
#include "Move.h"

struct TestSuiteGameLogicFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;

    TestSuiteGameLogicFixture() {
        board = std::make_shared<Board>();
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(board, whitePlayer, blackPlayer, whitePlayer);

        for(int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                board->addSquare(x, y);
    }

    ~TestSuiteGameLogicFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteGameLogic, TestSuiteGameLogicFixture)

    /*************************** initializeGame() ***************************/

    BOOST_AUTO_TEST_CASE(initializeGameTest) {
        GameDataPtr game = GameLogic::initializeGame(WHITE, false);
        std::string expectedPiecesPositions = "BR1   BN1   BB1   BQ1   BK1   BB1   BN1   BR1   \n\n"

                                              "BP1   BP1   BP1   BP1   BP1   BP1   BP1   BP1   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "WP1   WP1   WP1   WP1   WP1   WP1   WP1   WP1   \n\n"

                                              "WR1   WN1   WB1   WQ1   WK1   WB1   WN1   WR1   \n\n";
        BOOST_TEST(expectedPiecesPositions == game->getBoard()->toString());
        BOOST_TEST(game->getPlayer1()->getName() == "Player_1");
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getColor(), WHITE);
        BOOST_TEST(game->getPlayer2()->getName() == "Player_2");
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getColor(), BLACK);
        BOOST_REQUIRE_EQUAL(game->getPlayerTurn(), game->getPlayer1());
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getKing(), game->getBoard()->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getKing(), game->getBoard()->getSquare(0, 4)->getPiece());
    }

    /**************************** promotePawn() ****************************/

    BOOST_AUTO_TEST_CASE(promotePawnTest) {
        board->addPiece(PieceType::Pawn, whitePlayer, 0,0);
        PieceType newPiece = PieceType::Queen;
        GameLogic::promotePawn(newPiece, board->getSquare(0,0), gameData);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getType(), PieceType::Queen);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getPlayer(), whitePlayer);
        BOOST_REQUIRE_EQUAL(board->getPieces().size(), 1);
    }

    /************************** checkIfPromotion() **************************/

    BOOST_AUTO_TEST_CASE(checkIfPromotionPositiveTest) {
        //white
        board->addPiece(PieceType::Pawn, whitePlayer, 0,0);
        MovePtr whiteMove = std::make_shared<Move>(board->getSquare(1,0), board->getSquare(0,0), whitePlayer);
        BOOST_REQUIRE_EQUAL(GameLogic::checkIfPromotion(whiteMove, gameData), board->getSquare(0,0));
        //black
        board->addPiece(PieceType::Pawn, blackPlayer, 7,0);
        MovePtr blackMove = std::make_shared<Move>(board->getSquare(6,0), board->getSquare(7,0), blackPlayer);
        BOOST_REQUIRE_EQUAL(GameLogic::checkIfPromotion(blackMove, gameData), board->getSquare(7,0));
    }


    /************************* getCheckingPiece() *************************/

    BOOST_AUTO_TEST_CASE(getcheckingPieceTest_return_piece) {
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 5, 4);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->getSquare(0, 0)->getPiece()->setCaptured();
        BOOST_REQUIRE_EQUAL(GameLogic::getCheckingPiece(blackPlayer, gameData), board->getSquare(5, 4)->getPiece());
    }

    BOOST_AUTO_TEST_CASE(getcheckingPieceTest_return_nullptr) {
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 4, 1);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->getSquare(0, 0)->getPiece()->setCaptured();
        BOOST_REQUIRE_EQUAL(GameLogic::getCheckingPiece(blackPlayer, gameData), nullptr);
    }


    /****************** isPlayerInCheckAfterMove() ******************/

    BOOST_AUTO_TEST_CASE(isPlayerInCheckAfterMoveTest_return_true) {
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 6, 4);
        board->addPiece(PieceType::Queen, blackPlayer, 1, 4);
        MovePtr move = std::make_shared<Move>(board->getSquare(6, 4), board->getSquare(6, 0), blackPlayer);
        BOOST_REQUIRE_EQUAL(GameLogic::isPlayerInCheckAfterMove(whitePlayer, move, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(isPlayerInCheckAfterMoveTest_return_false) {
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 6, 4);
        board->addPiece(PieceType::Queen, blackPlayer, 1, 4);
        MovePtr move = std::make_shared<Move>(board->getSquare(6, 4), board->getSquare(4, 4), blackPlayer);
        BOOST_REQUIRE_EQUAL(GameLogic::isPlayerInCheckAfterMove(whitePlayer, move, gameData), false);
    }


    /********************* canCheckingPieceBeCaptured() *********************/

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_true) {
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 4);
        PiecePtr checkingPiece  = board->getSquare(3, 4)->getPiece();
        whitePlayer->setCheckingPiece(checkingPiece);
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckingPieceBeCaptured(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_false_caseNoAvailableCapture) {
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 4);
        PiecePtr checkingPiece  = board->getSquare(3, 4)->getPiece();
        whitePlayer->setCheckingPiece(checkingPiece);
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckingPieceBeCaptured(whitePlayer, gameData), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_false_caseInCheckAfterCapture) {
        board->addPiece(PieceType::Knight, whitePlayer, 6, 3);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 4, 4);
        board->addPiece(PieceType::Bishop, blackPlayer, 4, 1);
        PiecePtr checkingPiece = board->getSquare(4, 4)->getPiece();
        whitePlayer->setCheckingPiece(checkingPiece);
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckingPieceBeCaptured(whitePlayer, gameData), false);
    }


    /************************* canKingBeMoved() *************************/

    BOOST_AUTO_TEST_CASE(canKingBeMovedTest_return_true) {
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 1);
        BOOST_REQUIRE_EQUAL(GameLogic::canKingBeMoved(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(canKingBeMovedTest_return_false) {
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 1);
        board->addPiece(PieceType::Rook, blackPlayer, 1, 1);
        BOOST_REQUIRE_EQUAL(GameLogic::canKingBeMoved(whitePlayer, gameData), false);
    }


    /******************** canCheckBeBlocked() *********************/

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseRook_return_true) {
        board->addPiece(PieceType::Rook, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 2);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 4);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseRook_return_false_caseNoPiece) {
        board->addPiece(PieceType::Rook, blackPlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseBishop_return_true) {
        board->addPiece(PieceType::Bishop, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseBishop_return_false_caseNoPiece) {
        board->addPiece(PieceType::Bishop, blackPlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseQueen_return_true) {
        board->addPiece(PieceType::Queen, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 1, 2);
        board->addPiece(PieceType::Rook, whitePlayer, 1, 4);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 1);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 1);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseQueen_return_false_caseNoPiece) {
        board->addPiece(PieceType::Queen, blackPlayer, 3, 3);
        whitePlayer->setCheckingPiece(board->getSquare(3, 3)->getPiece());
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::canCheckBeBlocked(whitePlayer, gameData), false);
    }


    /************************* isCastlingCorrect() *************************/

    BOOST_AUTO_TEST_CASE(isCastlingCorrectPositiveTestCaseShort) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::isCastlingCorrect(whitePlayer, "O-O", gameData), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::isCastlingCorrect(blackPlayer, "O-O", gameData), true);
    }

    BOOST_AUTO_TEST_CASE(isCastlingCorrectPositiveTestCaseLong) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::isCastlingCorrect(whitePlayer, "O-O-O", gameData), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(GameLogic::isCastlingCorrect(blackPlayer, "O-O-O", gameData), true);
    }


    /************************** isSquareAttacked() **************************/

    BOOST_AUTO_TEST_CASE(isSquareAttackedTest_return_true) {
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 0);
        BOOST_REQUIRE_EQUAL(GameLogic::isSquareAttacked(blackPlayer, board->getSquare(3, 0), gameData), true);
        BOOST_REQUIRE_EQUAL(GameLogic::isSquareAttacked(blackPlayer, board->getSquare(0, 3), gameData), true);
        BOOST_REQUIRE_EQUAL(GameLogic::isSquareAttacked(blackPlayer, board->getSquare(3, 7), gameData), true);
        BOOST_REQUIRE_EQUAL(GameLogic::isSquareAttacked(blackPlayer, board->getSquare(7, 3), gameData), true);
    }

    BOOST_AUTO_TEST_CASE(isSquareAttackedTest_return_false) {
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 4);
        BOOST_REQUIRE_EQUAL(GameLogic::isSquareAttacked(blackPlayer, board->getSquare(3, 7), gameData), false);
    }


    /******************************* isStalemate() *******************************/


    BOOST_AUTO_TEST_CASE(isStalemateTest_return_true) {
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 2, 1);
        BOOST_REQUIRE_EQUAL(GameLogic::isStalemate(whitePlayer, gameData), true);
    }

    BOOST_AUTO_TEST_CASE(isStalemateTest_return_false) {
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 0, 1);
        board->addPiece(PieceType::Queen, blackPlayer, 2, 1);
        BOOST_REQUIRE_EQUAL(GameLogic::isStalemate(whitePlayer, gameData), false);
    }

BOOST_AUTO_TEST_SUITE_END()

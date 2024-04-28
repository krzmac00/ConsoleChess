#include <boost/test/unit_test.hpp>
#include "Game/GameForTesting.h"
#include "View/TestView.h"
#include "Players/HumanPlayer.h"
#include "Move.h"
#include "Check.h"


struct TestSuiteGameFixture {
    GameForTesting* game;
    ViewPtr view;
    std::shared_ptr<TestView> viewTest;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;

    void gameDefaultSettings() const {
        game->setPlayer1(whitePlayer);
        game->setPlayer2(blackPlayer);
        game->setPlayerTurn(whitePlayer);
    }

    TestSuiteGameFixture() {
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

    ~TestSuiteGameFixture() {
        delete game;
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteGame, TestSuiteGameFixture)

    /******************************** play() ********************************/

    BOOST_AUTO_TEST_CASE(practicalUseCaseCastlingTest) {
        std::string moves = "E2-E4 A7-A5 E4-E5 D7-D5 E5-D6 A5-A4 B2-B3 C7-C5 B3-B4 A4-B3 C5-B4 C2-C4 B4-C3";
        viewTest->setMoves(moves);
        game->play();
        std::string expectedPiecesPositions = "BR BN BB BQ BK BB BN BR \n"
                                              "() BP () () BP BP BP BP \n"
                                              "() () () WP () () () () \n"
                                              "() () () () () () () () \n"
                                              "BP () () () () () () () \n"
                                              "() () BP () () () () () \n"
                                              "WP () () WP () WP WP WP \n"
                                              "WR WN WB WQ WK WB WN WR \n";
        BOOST_REQUIRE_EQUAL(expectedPiecesPositions, game->getBoard()->toString());
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getCapturedPieces().size(), 1);
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getCapturedPieces().size(), 2);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseSzach) {
        std::string moves = "E2-E3 F7-F6 D1-H5";
        viewTest->setMoves(moves);
        game->play();
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->isCheck(), true);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseCheckmate) {
        std::string moves = "F2-F3 E7-E6 G2-G4 D8-H4";
        viewTest->setMoves(moves);
        game->play();
        BOOST_REQUIRE_EQUAL(game->isCheckmatePublic(game->getPlayer1()), true);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseStalemate) {
        std::string moves = "G1-C1";
        viewTest->setMoves(moves);
        viewTest->setNewGame(false);
        viewTest->setFilePath("../../library/test/gameSaveFiles/testCaseStalemate.txt");
        std::string expectedPiecesPositions = "() () () () () BK () () \n"
                                              "() () () () () () BP () \n"
                                              "() () () () () () () () \n"
                                              "() () BP () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() () () BQ () () () () \n"
                                              "WK () () WP () () () () \n"
                                              "() () BQ () () () () () \n";
        game->play();
        BOOST_REQUIRE_EQUAL(expectedPiecesPositions, game->getBoard()->toString());
        BOOST_REQUIRE_EQUAL(game->isStalematePublic(game->getPlayer1()), true);
    }


    /******************* startGame(), initializeGame() *******************/

    BOOST_AUTO_TEST_CASE(startGame_initializeGameTest) {
        viewTest->setGameWithComputer(false);
        viewTest->setPlayer1Color(WHITE);
        game->startGamePublic();
        std::string expectedPiecesPositions = "BR BN BB BQ BK BB BN BR \n"
                                              "BP BP BP BP BP BP BP BP \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "WP WP WP WP WP WP WP WP \n"
                                              "WR WN WB WQ WK WB WN WR \n";
        BOOST_TEST(expectedPiecesPositions == game->getBoard()->toString());
        BOOST_TEST(game->getPlayer1()->getName() == "Player_1");
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getColor(), WHITE);
        BOOST_TEST(game->getPlayer2()->getName() == "Player_2");
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getColor(), BLACK);
        BOOST_REQUIRE_EQUAL(game->getPlayerTurn(), game->getPlayer1());
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getKing(), game->getBoard()->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getKing(), game->getBoard()->getSquare(0, 4)->getPiece());
    }


    /********************** saveGame(), loadGame() ***********************/

    BOOST_AUTO_TEST_CASE(saveGame_loadGameTest) {
        viewTest->setFilePath("../../library/test/gameSaveFiles/testSave.txt");
        game->setPlayer1(whitePlayer);
        game->setPlayer2(blackPlayer);
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        board->addPiece(PieceType::Knight, blackPlayer, 2, 0);
        board->addPiece(PieceType::Queen, blackPlayer, 4, 4);
        board->addPiece(PieceType::Knight, blackPlayer, 4, 7);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        board->addPiece(PieceType::Bishop, whitePlayer, 1, 4);
        board->addPiece(PieceType::Pawn, whitePlayer, 5, 4);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 5);
        board->addPiece(PieceType::Knight, whitePlayer, 7, 6);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        MovePtr move1 = std::make_shared<Move>(board->getSquare(1, 4), board->getSquare(4, 7));
        move1->execute(whitePlayer, board);
        MovePtr move2 = std::make_shared<Move>(board->getSquare(4, 4), board->getSquare(4, 7));
        move2->execute(blackPlayer, board);
        MovePtr move3 = std::make_shared<Move>(board->getSquare(7, 6), board->getSquare(5, 5));
        move3->execute(whitePlayer, board);
        MovePtr move4 = std::make_shared<Move>(board->getSquare(4, 7), board->getSquare(4, 1));
        move4->execute(blackPlayer, board);
        whitePlayer->setCheck(board->getSquare(4, 1)->getPiece());
        game->setPlayerTurn(blackPlayer);
        std::string expectedPiecesPositions = "BR () () () BK () () () \n"
                                              "() () () () () () () () \n"
                                              "BN () () () () () () () \n"
                                              "() () () () () () () () \n"
                                              "() BQ () () () () () () \n"
                                              "() () () () WP WN () () \n"
                                              "() () () () () WP () () \n"
                                              "WR () () () WK () () () \n";
        BOOST_TEST(expectedPiecesPositions == game->getBoard()->toString());
        std::vector<std::string> piecesCapturedByPlayer1 = whitePlayer->getCapturedPieces();
        std::vector<std::string> piecesCapturedByPlayer2 = blackPlayer->getCapturedPieces();
        std::vector<std::string> movesOfPlayer1 = whitePlayer->getMoves();
        std::vector<std::string> movesOfPlayer2 = blackPlayer->getMoves();

        BOOST_REQUIRE_EQUAL(game->saveGamePublic(), true);
        BOOST_REQUIRE_EQUAL(game->loadGamePublic(), true);
        BOOST_TEST(expectedPiecesPositions == game->getBoard()->toString());
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getColor(), WHITE);
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getName(), "Player_1");
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getKing(), game->getBoard()->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->isCheck(), true);
        BOOST_REQUIRE_EQUAL(game->getPlayer1()->getCheckingPiece()->getCheckingPiece(), game->getBoard()->getSquare(4, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getColor(), BLACK);
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getName(), "Player_2");
        BOOST_REQUIRE_EQUAL(game->getPlayer2()->getKing(), game->getBoard()->getSquare(0, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->getPlayerTurn()->getColor(), BLACK);
        BOOST_REQUIRE_EQUAL(game->getPlayerTurn(), game->getPlayer2());
        int i = 0;
        for(auto &piece : game->getPlayer1()->getCapturedPieces()) {
            BOOST_TEST(piece == piecesCapturedByPlayer1[i]);
            i++;
        }
        i = 0;
        for(auto &piece : game->getPlayer2()->getCapturedPieces()) {
            BOOST_TEST(piece == piecesCapturedByPlayer2[i]);
            i++;
        }
        i = 0;
        for(auto &move : game->getPlayer1()->getMoves()) {
            BOOST_TEST(move == movesOfPlayer1[i]);
            i++;
        }
        i = 0;
        for(auto &move : game->getPlayer2()->getMoves()) {
            BOOST_TEST(move == movesOfPlayer2[i]);
            i++;
        }
    }


    /***************************** handleMove() *****************************/

    //BOOST_AUTO_TEST_CASE(obslugamoveuTest_return_R)


    /**************************** promotion() ****************************/

    BOOST_AUTO_TEST_CASE(promotionTest) {
        viewTest->setPromotion(PieceType::Queen);
        board->addPiece(PieceType::Pawn, whitePlayer, 0, 0);
        game->promotionPublic(board->getSquare(0, 0), whitePlayer);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getType(), PieceType::Queen);
        BOOST_REQUIRE_EQUAL(board->getSquare(0, 0)->getPiece()->getPlayer(), whitePlayer);
        BOOST_REQUIRE_EQUAL(board->getPieces().size(), 1);
    }


    /************************* getCheckingPiece() *************************/

    BOOST_AUTO_TEST_CASE(getcheckingPieceTest_return_piece) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 5, 4);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->getSquare(0, 0)->getPiece()->setCaptured();
        BOOST_REQUIRE_EQUAL(game->getCheckingPiecePublic(blackPlayer), board->getSquare(5, 4)->getPiece());
    }

    BOOST_AUTO_TEST_CASE(getcheckingPieceTest_return_nullptr) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 4, 1);
        board->addPiece(PieceType::Pawn, whitePlayer, 6, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->getSquare(0, 0)->getPiece()->setCaptured();
        BOOST_REQUIRE_EQUAL(game->getCheckingPiecePublic(blackPlayer), nullptr);
    }


    /****************** isPlayerInCheckAfterMove() ******************/

    BOOST_AUTO_TEST_CASE(isPlayerInCheckAfterMoveTest_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 6, 4);
        board->addPiece(PieceType::Queen, blackPlayer, 1, 4);
        MovePtr move = std::make_shared<Move>(board->getSquare(6, 4), board->getSquare(6, 0));
        BOOST_REQUIRE_EQUAL(game->isPlayerInCheckAfterMovePublic(whitePlayer, move), true);
    }

    BOOST_AUTO_TEST_CASE(isPlayerInCheckAfterMoveTest_return_false) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 6, 4);
        board->addPiece(PieceType::Queen, blackPlayer, 1, 4);
        MovePtr move = std::make_shared<Move>(board->getSquare(6, 4), board->getSquare(4, 4));
        BOOST_REQUIRE_EQUAL(game->isPlayerInCheckAfterMovePublic(whitePlayer, move), false);
    }


    /********************* canCheckingPieceBeCaptured() *********************/

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 4);
        PiecePtr checkingPiece  = board->getSquare(3, 4)->getPiece();
        whitePlayer->setCheck(checkingPiece);
        BOOST_REQUIRE_EQUAL(game->canCheckingPieceBeCapturedPublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_false_caseNoAvailableCapture) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, whitePlayer, 0, 0);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 4);
        PiecePtr checkingPiece  = board->getSquare(3, 4)->getPiece();
        whitePlayer->setCheck(checkingPiece);
        BOOST_REQUIRE_EQUAL(game->canCheckingPieceBeCapturedPublic(whitePlayer), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckingPieceBeCapturedTest_return_false_caseInCheckAfterCapture) {
        gameDefaultSettings();
        board->addPiece(PieceType::Knight, whitePlayer, 6, 3);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 4, 4);
        board->addPiece(PieceType::Bishop, blackPlayer, 4, 1);
        PiecePtr checkingPiece = board->getSquare(4, 4)->getPiece();
        whitePlayer->setCheck(checkingPiece);
        BOOST_REQUIRE_EQUAL(game->canCheckingPieceBeCapturedPublic(whitePlayer), false);
    }


    /************************* canKingBeMoved() *************************/

    BOOST_AUTO_TEST_CASE(canKingBeMovedTest_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 1);
        BOOST_REQUIRE_EQUAL(game->canKingBeMovedPublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(canKingBeMovedTest_return_false) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 3, 1);
        board->addPiece(PieceType::Rook, blackPlayer, 1, 1);
        BOOST_REQUIRE_EQUAL(game->canKingBeMovedPublic(whitePlayer), false);
    }


    /******************** canCheckBeBlocked() *********************/

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseRook_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 2);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 4);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseRook_return_false_caseNoPiece) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, blackPlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseBishop_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::Bishop, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseBishop_return_false_caseNoPiece) {
        gameDefaultSettings();
        board->addPiece(PieceType::Bishop, blackPlayer, 3, 3);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseQueen_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::Queen, blackPlayer, 3, 3);
        board->addPiece(PieceType::Rook, whitePlayer, 1, 2);
        board->addPiece(PieceType::Rook, whitePlayer, 1, 4);
        board->addPiece(PieceType::Rook, whitePlayer, 2, 1);
        board->addPiece(PieceType::Rook, whitePlayer, 4, 1);
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(canCheckBeBlockedTestCaseQueen_return_false_caseNoPiece) {
        gameDefaultSettings();
        board->addPiece(PieceType::Queen, blackPlayer, 3, 3);
        whitePlayer->setCheck(board->getSquare(3, 3)->getPiece());
        board->addPiece(PieceType::King, whitePlayer, 1, 1);
        whitePlayer->setKing(board->getSquare(1, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 5);
        whitePlayer->setKing(board->getSquare(1, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 5);
        whitePlayer->setKing(board->getSquare(5, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 1);
        whitePlayer->setKing(board->getSquare(5, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 5, 3);
        whitePlayer->setKing(board->getSquare(5, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 1);
        whitePlayer->setKing(board->getSquare(3, 1)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 1, 3);
        whitePlayer->setKing(board->getSquare(1, 3)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
        board->addPiece(PieceType::King, whitePlayer, 3, 5);
        whitePlayer->setKing(board->getSquare(3, 5)->getPiece());
        BOOST_REQUIRE_EQUAL(game->canCheckBeBlockedPublic(whitePlayer), false);
    }


    /************************* isCastlingCorrect() *************************/

    BOOST_AUTO_TEST_CASE(isCastlingCorrectPositiveTestCaseShort) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 7);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->isCastlingCorrectPublic(whitePlayer, "O-O"), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 7);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->isCastlingCorrectPublic(blackPlayer, "O-O"), true);
    }

    BOOST_AUTO_TEST_CASE(isCastlingCorrectPositiveTestCaseLong) {
        //white
        board->addPiece(PieceType::Rook, whitePlayer, 7, 0);
        board->addPiece(PieceType::King, whitePlayer, 7, 4);
        whitePlayer->setKing(board->getSquare(7, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->isCastlingCorrectPublic(whitePlayer, "O-O-O"), true);
        //black
        board->addPiece(PieceType::Rook, blackPlayer, 0, 0);
        board->addPiece(PieceType::King, blackPlayer, 0, 4);
        blackPlayer->setKing(board->getSquare(0, 4)->getPiece());
        BOOST_REQUIRE_EQUAL(game->isCastlingCorrectPublic(blackPlayer, "O-O-O"), true);
    }


    /************************** isSquareAttacked() **************************/

    BOOST_AUTO_TEST_CASE(isSquareAttackedTest_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 0);
        BOOST_REQUIRE_EQUAL(game->isSquareAttackedPublic(blackPlayer, board->getSquare(3, 0)), true);
        BOOST_REQUIRE_EQUAL(game->isSquareAttackedPublic(blackPlayer, board->getSquare(0, 3)), true);
        BOOST_REQUIRE_EQUAL(game->isSquareAttackedPublic(blackPlayer, board->getSquare(3, 7)), true);
        BOOST_REQUIRE_EQUAL(game->isSquareAttackedPublic(blackPlayer, board->getSquare(7, 3)), true);
    }

    BOOST_AUTO_TEST_CASE(isSquareAttackedTest_return_false) {
        gameDefaultSettings();
        board->addPiece(PieceType::Rook, whitePlayer, 3, 3);
        board->addPiece(PieceType::Pawn, blackPlayer, 3, 4);
        BOOST_REQUIRE_EQUAL(game->isSquareAttackedPublic(blackPlayer, board->getSquare(3, 7)), false);
    }


    /******************************* isStalemate() *******************************/


    BOOST_AUTO_TEST_CASE(isStalemateTest_return_true) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, blackPlayer, 2, 1);
        BOOST_REQUIRE_EQUAL(game->isStalematePublic(whitePlayer), true);
    }

    BOOST_AUTO_TEST_CASE(isStalemateTest_return_false) {
        gameDefaultSettings();
        board->addPiece(PieceType::King, whitePlayer, 0, 0);
        whitePlayer->setKing(board->getSquare(0, 0)->getPiece());
        board->addPiece(PieceType::Queen, whitePlayer, 0, 1);
        board->addPiece(PieceType::Queen, blackPlayer, 2, 1);
        BOOST_REQUIRE_EQUAL(game->isStalematePublic(whitePlayer), false);
    }

BOOST_AUTO_TEST_SUITE_END()


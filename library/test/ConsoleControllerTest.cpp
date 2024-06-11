#include <boost/test/unit_test.hpp>
#include "Controller/TestController.h"
#include "View/TestView.h"
#include "Players/HumanPlayer.h"
#include "Move.h"
#include "GameLogic.h"

struct TestSuiteConsoleControllerFixture {
    ViewPtr view;
    TestController controller;
    std::shared_ptr<TestView> viewTest;
    GameDataPtr gameData;

    TestSuiteConsoleControllerFixture() :
        view(std::make_shared<TestView>()),
        controller(view),
        viewTest(std::dynamic_pointer_cast<TestView>(view)) {
    }

    ~TestSuiteConsoleControllerFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteConsoleController, TestSuiteConsoleControllerFixture)

    /******************************** play() ********************************/

    BOOST_AUTO_TEST_CASE(practicalUseCaseEnPassantTest) {
        std::string moves = "E2-E4 A7-A5 E4-E5 D7-D5 E5-D6 A5-A4 B2-B3 C7-C5 B3-B4 A4-B3 C5-B4 C2-C4 B4-C3";
        viewTest->setMoves(moves);
        controller.play();
        std::string expectedPiecesPositions = "BR1   BN1   BB1   BQ1   BK1   BB1   BN1   BR1   \n\n"

                                              "[.]   BP1   [.]   [.]   BP1   BP1   BP1   BP1   \n\n"

                                              "[.]   [.]   [.]   WP0   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "BP0   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   BP0   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "WP1   [.]   [.]   WP1   [.]   WP1   WP1   WP1   \n\n"

                                              "WR1   WN1   WB1   WQ1   WK1   WB1   WN1   WR1   \n\n";
        gameData = controller.getGameData();
        auto board = gameData->getBoard();
        auto player1 = gameData->getPlayer1();
        auto player2 = gameData->getPlayer2();
        BOOST_REQUIRE_EQUAL(expectedPiecesPositions, board->toString());
        BOOST_REQUIRE_EQUAL(board->getPiecesCapturedByPlayer(player1).size(), 1);
        BOOST_REQUIRE_EQUAL(board->getPiecesCapturedByPlayer(player2).size(), 2);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseCheck) {
        std::string moves = "E2-E3 F7-F6 D1-H5";
        viewTest->setMoves(moves);
        controller.play();
        gameData = controller.getGameData();
        BOOST_REQUIRE_EQUAL(gameData->getPlayer2()->isInCheck(), true);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseCheckmate) {
        std::string moves = "F2-F3 E7-E6 G2-G4 D8-H4";
        viewTest->setMoves(moves);
        controller.play();
        gameData = controller.getGameData();
        BOOST_REQUIRE_EQUAL(GameLogic::isCheckmate(gameData->getPlayer1(), gameData), true);
    }

    BOOST_AUTO_TEST_CASE(practicalUseTestCaseStalemate) {
        std::string moves = "G1-C1";
        viewTest->setMoves(moves);
        viewTest->setNewGame(false);
        viewTest->setFilePath("../../library/test/gameSaveFiles/testCaseStalemate.txt");
        std::string expectedPiecesPositions = "[.]   [.]   [.]   [.]   [.]   BK0   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   BP1   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   BP0   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   [.]   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   [.]   BQ0   [.]   [.]   [.]   [.]   \n\n"

                                              "WK0   [.]   [.]   WP1   [.]   [.]   [.]   [.]   \n\n"

                                              "[.]   [.]   BQ0   [.]   [.]   [.]   [.]   [.]   \n\n";
        controller.play();
        gameData = controller.getGameData();
        BOOST_REQUIRE_EQUAL(expectedPiecesPositions, gameData->getBoard()->toString());
        BOOST_REQUIRE_EQUAL(GameLogic::isStalemate(gameData->getPlayer1(), gameData), true);
    }


BOOST_AUTO_TEST_SUITE_END()
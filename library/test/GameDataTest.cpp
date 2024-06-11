#include <boost/test/unit_test.hpp>
#include "GameData.h"
#include "Players/HumanPlayer.h"
#include "Move.h"


struct TestSuiteGameDataFixture {
    GameDataPtr gameData;
    BoardPtr board;
    PlayerPtr whitePlayer;
    PlayerPtr blackPlayer;
    MovePtr move1;
    MovePtr move2;

    TestSuiteGameDataFixture() {
        board = std::make_shared<Board>();
        whitePlayer = std::make_shared<HumanPlayer>("Player", WHITE);
        blackPlayer = std::make_shared<HumanPlayer>("Player", BLACK);
        gameData = std::make_shared<GameData>(board, whitePlayer, blackPlayer, whitePlayer);
        move1 = std::make_shared<Move>("A2-A4", whitePlayer);
        move2 = std::make_shared<Move>("A2-A4", blackPlayer);
    }

    ~TestSuiteGameDataFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteGameData, TestSuiteGameDataFixture)

    BOOST_AUTO_TEST_CASE(constructorAndGettersTest) {
        BOOST_REQUIRE_EQUAL(gameData->getBoard(), board);
        BOOST_REQUIRE_EQUAL(gameData->getPlayer1(), whitePlayer);
        BOOST_REQUIRE_EQUAL(gameData->getPlayer2(), blackPlayer);
        BOOST_REQUIRE_EQUAL(gameData->getPlayerTurn(), whitePlayer);
    }

    BOOST_AUTO_TEST_CASE(nextTurnTest) {
        gameData->nextTurn();
        BOOST_REQUIRE_EQUAL(gameData->getPlayerTurn(), blackPlayer);
        gameData->nextTurn();
        BOOST_REQUIRE_EQUAL(gameData->getPlayerTurn(), whitePlayer);
    }

    BOOST_AUTO_TEST_CASE(movesCollectionTest) {
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory().size(), 0);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(whitePlayer).size(), 0);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(blackPlayer).size(), 0);
        gameData->addMove(move1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory().size(), 1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory()[0], move1);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), move1);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(whitePlayer), move1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(whitePlayer).size(), 1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(blackPlayer).size(), 0);
        gameData->addMove(move2);
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory().size(), 2);
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory()[0], move1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesHistory()[1], move2);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(), move2);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(whitePlayer), move1);
        BOOST_REQUIRE_EQUAL(gameData->getLastMove(blackPlayer), move2);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(whitePlayer).size(), 1);
        BOOST_REQUIRE_EQUAL(gameData->getMovesOfPlayer(blackPlayer).size(), 1);
    }

BOOST_AUTO_TEST_SUITE_END()

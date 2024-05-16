#include <boost/test/unit_test.hpp>
#include "Exceptions/FileStructureException.h"
#include "GameReader.h"
#include "GameData.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include <vector>


typedef std::vector<std::string> stringVector;

BOOST_TEST_DONT_PRINT_LOG_VALUE(stringVector)

BOOST_AUTO_TEST_SUITE(TestSuiteGameReader)

    BOOST_AUTO_TEST_CASE(loadGameTest) {
        GameDataPtr gameData = GameReader::loadGame("../../library/test/gameSaveFiles/testSave.txt");
        BoardPtr board = gameData->getBoard();
        PlayerPtr player1 = gameData->getPlayer1();
        PlayerPtr player2 = gameData->getPlayer2();
        PlayerPtr playerTurn = gameData->getPlayerTurn();
        BOOST_REQUIRE_EQUAL(playerTurn->getName(), "Player_2");
        BOOST_REQUIRE_EQUAL(playerTurn->getColor(), Color::BLACK);
        //Player Colors
        BOOST_REQUIRE_EQUAL(player1->getColor(), Color::WHITE);
        BOOST_REQUIRE_EQUAL(player2->getColor(), Color::BLACK);
        //Player Kings
        BOOST_REQUIRE_EQUAL(player1->getKing(), board->getSquare(7,4)->getPiece());
        BOOST_REQUIRE_EQUAL(player2->getKing(), board->getSquare(0,4)->getPiece());
        //Black Rook A8
        BOOST_REQUIRE_EQUAL(board->getSquare(0,0)->getPiece()->getType(), PieceType::Rook);
        BOOST_REQUIRE_EQUAL(board->getSquare(0,0)->getPiece()->getPlayer(), player2);
        BOOST_REQUIRE_EQUAL(board->getSquare(0,0)->getPiece()->isFirstMove(), true);
        //Black King E8
        BOOST_REQUIRE_EQUAL(board->getSquare(0,4)->getPiece()->getType(), PieceType::King);
        BOOST_REQUIRE_EQUAL(board->getSquare(0,4)->getPiece()->getPlayer(), player2);
        BOOST_REQUIRE_EQUAL(board->getSquare(0,4)->getPiece()->isFirstMove(), true);
        //Black Knight A6
        BOOST_REQUIRE_EQUAL(board->getSquare(2,0)->getPiece()->getType(), PieceType::Knight);
        BOOST_REQUIRE_EQUAL(board->getSquare(2,0)->getPiece()->getPlayer(), player2);
        BOOST_REQUIRE_EQUAL(board->getSquare(2,0)->getPiece()->isFirstMove(), true);
        //Black Queen B4
        BOOST_REQUIRE_EQUAL(board->getSquare(4,1)->getPiece()->getType(), PieceType::Queen);
        BOOST_REQUIRE_EQUAL(board->getSquare(4,1)->getPiece()->getPlayer(), player2);
        BOOST_REQUIRE_EQUAL(board->getSquare(4,1)->getPiece()->isFirstMove(), false);
        //White Pawn E3
        BOOST_REQUIRE_EQUAL(board->getSquare(5,4)->getPiece()->getType(), PieceType::Pawn);
        BOOST_REQUIRE_EQUAL(board->getSquare(5,4)->getPiece()->getPlayer(), player1);
        BOOST_REQUIRE_EQUAL(board->getSquare(5,4)->getPiece()->isFirstMove(), true);
        //White Knight F3
        BOOST_REQUIRE_EQUAL(board->getSquare(5,5)->getPiece()->getType(), PieceType::Knight);
        BOOST_REQUIRE_EQUAL(board->getSquare(5,5)->getPiece()->getPlayer(), player1);
        BOOST_REQUIRE_EQUAL(board->getSquare(5,5)->getPiece()->isFirstMove(), false);
        //White Pawn F3
        BOOST_REQUIRE_EQUAL(board->getSquare(6,5)->getPiece()->getType(), PieceType::Pawn);
        BOOST_REQUIRE_EQUAL(board->getSquare(6,5)->getPiece()->getPlayer(), player1);
        BOOST_REQUIRE_EQUAL(board->getSquare(6,5)->getPiece()->isFirstMove(), true);
        //White Rook A1
        BOOST_REQUIRE_EQUAL(board->getSquare(7,0)->getPiece()->getType(), PieceType::Rook);
        BOOST_REQUIRE_EQUAL(board->getSquare(7,0)->getPiece()->getPlayer(), player1);
        BOOST_REQUIRE_EQUAL(board->getSquare(7,0)->getPiece()->isFirstMove(), true);
        //White King E1
        BOOST_REQUIRE_EQUAL(board->getSquare(7,4)->getPiece()->getType(), PieceType::King);
        BOOST_REQUIRE_EQUAL(board->getSquare(7,4)->getPiece()->getPlayer(), player1);
        BOOST_REQUIRE_EQUAL(board->getSquare(7,4)->getPiece()->isFirstMove(), true);
        //Player1 moves
        std::vector<std::string> player1Moves;
        player1Moves.emplace_back("E7-H4");
        player1Moves.emplace_back("G1-F3");
        BOOST_REQUIRE_EQUAL(player1->getMoves(), player1Moves);
        //Player2 moves
        std::vector<std::string> player2Moves;
        player2Moves.emplace_back("E4-H4");
        player2Moves.emplace_back("H4-B4");
        BOOST_REQUIRE_EQUAL(player2->getMoves(), player2Moves);
        //Player1 captured pieces
        std::vector<std::string> player1CapturedPieces;
        player1CapturedPieces.emplace_back("BN");
        BOOST_REQUIRE_EQUAL(player1->getCapturedPieces(), player1CapturedPieces);
        //Player2 captured pieces
        std::vector<std::string> player2CapturedPieces;
        player2CapturedPieces.emplace_back("WB");
        BOOST_REQUIRE_EQUAL(player2->getCapturedPieces(), player2CapturedPieces);
    }

BOOST_AUTO_TEST_CASE(loadGameTestCaseEmptyFile) {
        GameDataPtr gameData;
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/empty.txt"), FileStructureException);
}

    BOOST_AUTO_TEST_CASE(loadGameTestCaseInvalidColor) {
        GameDataPtr gameData;
        //Player1
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidPlayer1Color.txt"), FileStructureException);
        //Player2
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidPlayer2Color.txt"), FileStructureException);
    }

    BOOST_AUTO_TEST_CASE(loadGameTestCaseInvalidName) {
        GameDataPtr gameData;
        //Player1
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidPlayer1Name.txt"), FileStructureException);
        //Player2
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidPlayer2Name.txt"), FileStructureException);
    }

    BOOST_AUTO_TEST_CASE(loadGameTestCaseMissingSquare) {
        GameDataPtr gameData;
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/missingSquare.txt"), FileStructureException);
    }

BOOST_AUTO_TEST_SUITE_END()
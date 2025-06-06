#include <boost/test/unit_test.hpp>
#include "Exceptions/FileStructureException.h"
#include "GameReader.h"
#include "GameData.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
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
        //movesHistory: E7-H4 E4-H4 G1-F3 H4-B4
        std::vector<std::string> movesToString;
        movesToString.emplace_back("E7-H4");
        movesToString.emplace_back("E4-H4");
        movesToString.emplace_back("G1-F3");
        movesToString.emplace_back("H4-B4");
        auto movesHistory = gameData->getMovesHistory();
        BOOST_REQUIRE_EQUAL(movesHistory.size(), 4);
        for(int i = 0; i != static_cast<int>(movesHistory.size()); i++) {
            BOOST_REQUIRE_EQUAL(movesHistory[i]->getAbbr(), movesToString[i]);
        }
        //Player1 moves
        std::vector<std::string> player1MovesToString;
        player1MovesToString.emplace_back("E7-H4");
        player1MovesToString.emplace_back("G1-F3");
        auto player1Moves = gameData->getMovesOfPlayer(player1);
        for(int i = 0; i != static_cast<int>(player1Moves.size()); i++) {
            BOOST_REQUIRE_EQUAL(player1Moves[i]->getAbbr(), player1MovesToString[i]);
        }
        //Player2 moves
        std::vector<std::string> player2MovesToString;
        player2MovesToString.emplace_back("E4-H4");
        player2MovesToString.emplace_back("H4-B4");
        auto player2Moves = gameData->getMovesOfPlayer(player2);
        for(int i = 0; i != static_cast<int>(player2Moves.size()); i++) {
            BOOST_REQUIRE_EQUAL(player2Moves[i]->getAbbr(), player2MovesToString[i]);
        }
        //Player1 captured pieces
        std::vector<std::string> player1CapturedPiecesToString;
        player1CapturedPiecesToString.emplace_back("BN");
        auto player1CapturedPieces = gameData->getBoard()->getPiecesCapturedByPlayer(player1);
        for(int i = 0; i != static_cast<int>(player1CapturedPieces.size()); i++) {
            BOOST_REQUIRE_EQUAL(player1CapturedPieces[i]->getAbbr(), player1CapturedPiecesToString[i]);
        }
        //Player2 captured pieces
        std::vector<std::string> player2CapturedPiecesToString;
        player2CapturedPiecesToString.emplace_back("WB");
        auto player2CapturedPieces = gameData->getBoard()->getPiecesCapturedByPlayer(player2);
        for(int i = 0; i != static_cast<int>(player2CapturedPieces.size()); i++) {
            BOOST_REQUIRE_EQUAL(player2CapturedPieces[i]->getAbbr(), player2CapturedPiecesToString[i]);
        }
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

    BOOST_AUTO_TEST_CASE(loadGameTestCaseInvalidPieceName) {
        GameDataPtr gameData;
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidPieceName.txt"), FileStructureException);
    }

    BOOST_AUTO_TEST_CASE(loadGameTestCaseInvalidMoveFormat) {
        GameDataPtr gameData;
        BOOST_REQUIRE_THROW(gameData = GameReader::loadGame("../../library/test/gameSaveFiles/corruptedFiles/invalidMoveFormat.txt"), FileStructureException);
    }

BOOST_AUTO_TEST_SUITE_END()
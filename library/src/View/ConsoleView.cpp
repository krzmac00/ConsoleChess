#include "View/ConsoleView.h"
#include "Board.h"
#include "Exceptions/InputException.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;

//private methods
void ConsoleView::displayColumnNames() const {
    string space = "    ";
    for (char i = 65; i <= 72; i++) {
        cout << space << i;
    }
    cout << endl;
}

void ConsoleView::displayHorizontalEdge() const {
    cout << " ";
    for(int i = 0; i < 8; i++) cout << "+----";
    cout << "+" << endl;
}

void ConsoleView::displayRow(BoardPtr &board, int row, string info) const {
    cout << 8 - row;
    for(int column = 0; column < 8; column++) {
        cout << "| ";
        PiecePtr piece = board->getSquare(row, column)->getPiece();
        piece == nullptr ? cout << "  " : cout << piece->getAbbr();
        cout << " ";
    }
    cout << "|" << 8 - row << "  " << info << endl;
    displayHorizontalEdge();
}

void ConsoleView::displayBoard(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) const {
    PlayerPtr white;
    PlayerPtr black;
    string space = "   ";
    if (player1->getColor() == WHITE) {
        white = player1;
        black = player2;
    }
    else {
        white = player2;
        black = player1;
    }
    string blackPlayer = "BLACK: " + black->getName();
    string blackMove = "Last move: " + black->getLastMove();
    string whitePlayer = "WHITE: " + white->getName();
    string whiteMove = "Last move: " + white->getLastMove();
    displayColumnNames();
    displayHorizontalEdge();
    for (int row = 0; row < 8; row++) {
        if (row == 0) displayRow(board, row, blackPlayer);
        else if (row == 1) displayRow(board, row, blackMove);
        else if (row == 6) displayRow(board, row, whitePlayer);
        else if (row == 7) displayRow(board, row, whiteMove);
        else displayRow(board, row, "");
    }
    displayColumnNames();
    cout << endl;
}

void ConsoleView::displayCapturedPieces(PlayerPtr &player1, PlayerPtr &player2) const {
    vector<string> capturedPlayer1 = player1->getCapturedPieces();
    vector<string> capturedPlayer2 = player2->getCapturedPieces();
    if(player1->getColor() == WHITE) {
        cout << "captured blacks: ";
        for(auto& piece : capturedPlayer1) cout << piece << " ";
        cout << endl;
        cout << "captured whites: ";
        for(auto& piece : capturedPlayer2) cout << piece << " ";
        cout << endl;
    }
    else {
        cout << "captured blacks: ";
        for(auto& piece : capturedPlayer2) cout << piece << " ";
        cout << endl;
        cout << "captured whites: ";
        for(auto& piece : capturedPlayer1) cout << piece << " ";
        cout << endl;
    }
}

void ConsoleView::displayDefView(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) {
    displayBoard(board, player1, player2);
    displayCapturedPieces(player1, player2);
    cout << "(M)enu" << endl;
    if(player1->isInCheck()) displayCheckInfo(player1);
    else if (player2->isInCheck()) displayCheckInfo(player2);
}

bool ConsoleView::readUserChoice() const {
    string choice;
    bool playWithComputer;
    bool error = true;
    do {
        cout << "Do you want to play against computer(Y/n)" << endl << "> ";
        try {
            cin >> choice;
            if (choice == "N" || choice == "n") {
                playWithComputer = false;
                error = false;
            }
            else if (choice == "Y" || choice == "y") {
                playWithComputer = true;
                error = false;
            }
            else throw (InputException("Incorrect choice!!!"));
        }
        catch (InputException &ie) {
            cout << endl << ie.what() << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return playWithComputer;
}

Color ConsoleView::readUserChoiceOfColor() const {
    string choice;
    Color color;
    bool error = true;
    do {
        cout << "Choose Player 1 color: WHITE(W) or BLACK(B)" << endl << "> ";
        try {
            cin >> choice;
            if (choice == "W" || choice == "w") {
                color = WHITE;
                error = false;
            }
            else if (choice == "B" || choice == "b") {
                color = BLACK;
                error = false;
            }
            else throw (InputException("Incorrect choice!!!"));
        }
        catch (InputException &ie) {
            cout << endl << ie.what() << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return color;
}

void ConsoleView::displayWinner(PlayerPtr winner) const {
    cout << "CHECKMATE: game ended" << endl << endl << "The winner is " << winner->getName() << " (" << winner->getColor() << ")"
         << endl << "Congratulations!!!" << endl;
    cin.get();
    this->displayEndGameMenu();
}

void ConsoleView::displayDraw() const {
    cout << "STALEMATE: game ended in a DRAW" << endl;
    cin.get();
    this->displayEndGameMenu();
}

std::string ConsoleView::readMove(Color color) {
    string move;
    string input;
    string strColor;
    if (this->error) cout << "Move incorrect" << endl;
    color == WHITE ? strColor = "WHITE" : strColor = "BLACK";
    bool error = true;
    do {
        cout << "Move of " << strColor << endl << "> ";
        try {
            cin >> input;
            move = input.substr(0, 5);
            if (move[0] >= 'A' && move[0] <= 'H' && move[3] >= 'A' && move[3] <= 'H'
                && move[1] >= '1' && move[1] <= '8' && move[4] >= '1' && move[4] <= '8') {
                move[2] = '-';
                error = false;
            }
            else if (move[0] == 'O' && move[2] == 'O') {
                if (move[4] == 'O') move = "O-O-O";
                else move = "O-O";
                error = false;
            }
            else if (move[0] == 'M') {
                move = "M";
                error = false;
            }
            else throw (InputException("Incorrect move format!!!"));
        }
        catch (InputException &ie) {
            cout << endl << ie.what() << endl;
            cin.get();
            system("clear");
        }
        catch (...) {
            cout << endl << "Incorrect move format!!!" << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return move;
}

PieceType ConsoleView::readPromotionChoice() {
    PieceType piece;
    string input;
    bool error;
    do {
        error = false;
        cout << "Pawn promotion: choose piece: (Q)ueen,(R)ook,(B)ishop,(K)night" << endl << "> ";
        try {
            cin >> input;
            input = input.substr(0, 1);
            if (input[0] == 'Q' || input[0] == 'q') piece = PieceType::Queen;
            else if (input[0] == 'R' || input[0] == 'r') piece = PieceType::Rook;
            else if (input[0] == 'B' || input[0] == 'b') piece = PieceType::Bishop;
            else if (input[0] == 'K' || input[0] == 'k') piece = PieceType::Knight;
            else {
                error = true;
                throw (InputException("Incorrect choice of piece!!!"));
            }
        }
        catch (InputException &ie) {
            cout << endl << ie.what() << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return piece;
}

void ConsoleView::displayCheckInfo(PlayerPtr &player) const {
    cout << player->getName() << "(" << player->getColor() << ") is in CHECK!" << endl;
}

void ConsoleView::displayMenu() const {
    cout << "============== MENU ==============" << endl;
    cout << "Display all player moves (D)" << endl;
    cout << "Save game (S)" << endl;
    cout << "Quit game (Q)" << endl;
    cout << "Close menu (C)" << endl;
}

void ConsoleView::displayEndGameMenu() const {
    cout << "New game (N)" << endl;
    cout << "Quit game (Q)" << endl;
}

std::string ConsoleView::readUserChoiceOfMenuOption() const {
    string input;
    bool error;
    do {
        error = false;
        cout << "> ";
        try {
            cin >> input;
            input = input.substr(0, 1);
            if (input != "D" && input != "S" && input != "Q" && input != "C" && input != "N") {
                error = true;
                throw (InputException("Incorrect option!!!"));
            }
        }
        catch (InputException &ie) {
            cout << ie.what() << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return input;
}

ConsoleView::ConsoleView() : View() {}

bool ConsoleView::readIfNewGame() const {
    string input;
    bool error;
    do {
        cout << "1. New game (N)" << endl << "2. Load game (L)" << endl << "> ";
        error = false;
        try {
            cin >> input;
            input = input.substr(0, 1);
            if (input != "N" && input != "L" ) {
                error = true;
                throw (InputException("Incorrect option!!!"));
            }
            else if(input == "N") return true;
            else return false;
        }
        catch (InputException &ie) {
            cout << endl << ie.what() << endl;
            cin.get();
            system("clear");
        }
    } while(error);
    return true;
}

std::string ConsoleView::readFilePath() const {
    std::string path;
    cout << "Enter file path: ";
    cin >> path;
    return path;
}

void ConsoleView::displayPlayerMoves(PlayerPtr &player) {
    cout << "Player moves: ";
    vector<string> moves = player->getMoves();
    for(auto &move : moves) {
        cout << move << " ";
    }
    cout << endl;
}

void ConsoleView::displayError(std::string message) const {
    cout << "ERROR: " << message;
}

bool ConsoleView::restartOrQuit() const {
    std::string choice;
    cout << "Restart(R) or quit(q)";
    if(choice == "q" || choice == "Q") return false;
    return true;
}

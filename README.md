# Console Chess
Console C++ program for Object Oriented Programming classes at TUL.

Program implements all of the chess rules including:
- castling ("O-O" move for kingside and "O-O-O" for queenside castling)
- en passant
- pawn promotion (to queen, rook, bishop, or knight at the choice of the player)
- stale mate detection
- move validation

## Game
Program provides console interface for user to interact with. After initial setup, where user can choose to start new game or load a save, game mode and players' colors, the board is displayed and players can move figures. Moves are enterd as commands in format of: [fileLetter][rankNumber]-[fileLetter][rankNumber] eg. "D1-G4". Input is validated in terms of syntax and validated in terms of chess rules.

![](/resources/game.gif)

## Loading and saving game
Game can be saved to text file before any move.
Load is possible at the start of the game.

![](/resources/save-load.gif)

## Game modes
 - 2 players
 - play with computer
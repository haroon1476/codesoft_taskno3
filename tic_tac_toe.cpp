
#include <iostream>
using namespace std;

// Enumerate player turns and game status
enum playerTurn { FIRST_PLAYER = 1, SECOND_PLAYER = 2 };
enum gameStatus { DRAW = 0, WIN = 1, IN_PROGRESS = 2 };

class gameBoard {
private:
    char board[3][3];

public:
    gameStatus current_game_status = IN_PROGRESS;
    int validMovesCount = 0;

    gameBoard() {
        char cellNum = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = cellNum++;
            }
        }
    }

    // Display the game board
    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    // Check if a position is valid
    bool isValidPosition(char pos) {
        return pos >= '1' && pos <= '9';
    }

    // Get the number of valid moves
    int getMovesCount() {
        return validMovesCount;
    }

    // Check for a win
    void checkWin(char playerSymbol) {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) {
                current_game_status = WIN;
                return;
            }
            if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol) {
                current_game_status = WIN;
                return;
            }
        }

        // Check diagonals
        if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) {
            current_game_status = WIN;
            return;
        }
        if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol) {
            current_game_status = WIN;
            return;
        }

        // Check for a draw
        if (validMovesCount == 9) {
            current_game_status = DRAW;
        }
    }

    // Mark the board with the player's symbol
    void markBoard(char pos, char playerSymbol) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == pos) {
                    board[i][j] = playerSymbol;
                    validMovesCount++;
                    checkWin(playerSymbol);
                }
            }
        }
    }

    // Check if a position is already marked
    bool isAlreadyMarked(char pos) {

        return pos == 'X' || pos == 'O';
    }

    // Get the current game status
    gameStatus getGameStatus() {
        return current_game_status;
    }

    // Check if a symbol is valid ('X' or 'O')
    bool isValidSymbol(char symbol) {
        return symbol == 'X' || symbol == 'O';
    }
};

class TicTacToe {
public:
    gameBoard board;

    void playGame() {
        char player1Symbol;
        char player2Symbol;

        // Get symbols for player 1 and player 2
        do {
            cout << "Enter Player 1's symbol ('X' or 'O'): ";
            cin >> player1Symbol;
        } while (!board.isValidSymbol(player1Symbol));

        player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';

        char currentPlayerSymbol = player1Symbol;
        char cellNumber;
        playerTurn currentPlayer = FIRST_PLAYER;

        while (board.getGameStatus() == IN_PROGRESS) {
            board.displayBoard();
            cout << "Player " << currentPlayer << " (" << currentPlayerSymbol << ") - Enter the cell number: ";
            cin >> cellNumber;

            if (board.isValidPosition(cellNumber) && !(board.isAlreadyMarked(cellNumber))) {
                board.markBoard(cellNumber, currentPlayerSymbol);
                currentPlayer = (currentPlayer == FIRST_PLAYER) ? SECOND_PLAYER : FIRST_PLAYER;
                currentPlayerSymbol = (currentPlayerSymbol == player1Symbol) ? player2Symbol : player1Symbol;
            }
            else {
                cout << "Invalid move. Try again.\n";
            }
        }

        board.displayBoard();
        if (board.getGameStatus() == WIN) {
            cout << "Player " << currentPlayer << " (" << currentPlayerSymbol << ") wins!\n";
        }
        else if (board.getGameStatus() == DRAW) {
            cout << "It's a draw!\n";
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}

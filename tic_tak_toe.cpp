#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'} };

char current_player = 'X';

void displayBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";
}

bool isWinner() {
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == current_player &&
            board[i][1] == current_player &&
            board[i][2] == current_player)
            return true;

    // Check columns
    for (int i = 0; i < 3; i++)
        if (board[0][i] == current_player &&
            board[1][i] == current_player &&
            board[2][i] == current_player)
            return true;

    // Check diagonals
    if (board[0][0] == current_player &&
        board[1][1] == current_player &&
        board[2][2] == current_player)
        return true;

    if (board[0][2] == current_player &&
        board[1][1] == current_player &&
        board[2][0] == current_player)
        return true;

    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void makeMove() {
    int choice;
    cout << "Player " << current_player << ", enter your move (1-9): ";
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        cout << "Invalid move! Try again.\n";
        makeMove();
    } else {
        board[row][col] = current_player;
    }
}

void switchPlayer() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int main() {
    cout << "===== TIC TAC TOE =====\n";
    displayBoard();

    while (true) {
        makeMove();
        displayBoard();

        if (isWinner()) {
            cout << "Player " << current_player << " wins!\n";
            break;
        }

        if (isDraw()) {
            cout << "It's a draw!\n";
            break;
        }

        switchPlayer();
    }

    return 0;
}

#include <iostream>
using namespace std;

const int SIZE = 3;          // board is SIZE x SIZE (cell numbers 1-9 fit SIZE 3)
char board[SIZE][SIZE];      // holds '1'-'9', 'X' or 'O'

// Fill the board with the numbers 1 to 9
void resetBoard() {
    char number = '1';
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = number;
            number++;
        }
    }
}

// Show the board on the screen
void printBoard() {
    cout << endl;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << " " << board[row][col] << " ";
            if (col < SIZE - 1) cout << "|";
        }
        cout << endl;
        if (row < SIZE - 1) cout << "---+---+---" << endl;
    }
    cout << endl;
}

// Try to place the player's mark. Returns true if the move worked.
bool makeMove(int choice, char player) {
    if (choice < 1 || choice > SIZE * SIZE) return false;   // not on the board

    int row = (choice - 1) / SIZE;
    int col = (choice - 1) % SIZE;

    if (board[row][col] == 'X' || board[row][col] == 'O') return false;   // taken

    board[row][col] = player;
    return true;
}

// Check if this player has a full row, column or diagonal
bool checkWin(char player) {
    for (int i = 0; i < SIZE; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != player) rowWin = false;
            if (board[j][i] != player) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    bool diag1 = true;
    bool diag2 = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != player) diag1 = false;
        if (board[i][SIZE - 1 - i] != player) diag2 = false;
    }
    return diag1 || diag2;
}

int main() {
    char player = 'X';
    int turns = 0;

    resetBoard();
    cout << "TIC TAC TOE" << endl;

    while (turns < SIZE * SIZE) {
        printBoard();
        cout << "Player " << player << ", choose a number: ";

        int choice;
        if (!(cin >> choice)) {          // user typed a letter instead of a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        if (!makeMove(choice, player)) {
            cout << "Invalid move, try again." << endl;
            continue;                    // same player tries again
        }
        turns++;

        if (checkWin(player)) {
            printBoard();
            cout << "Player " << player << " wins!" << endl;
            return 0;
        }

        // switch player
        if (player == 'X') player = 'O';
        else player = 'X';
    }

    printBoard();
    cout << "It's a draw!" << endl;
    return 0;
}

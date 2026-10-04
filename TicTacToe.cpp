#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace colors {
    const string reset ="\033[0m";
    const string pink = "\033[38;2;255;182;193m";
    const string cyan = "\033[38;2;175;238;238m";
    const string gray = "\033[38;2;150;150;150m";
    const string clear = "\033[H\033[J";
}

class TicTacToe {
    private:
     vector<vector<char>> board;
     char currentPlayer;

    public:
      TicTacToe() : board(3, vector<char>(3, ' ')), currentPlayer('X') {}
    
 void drawBoard() const {
    cout << colors::clear;
    cout << colors::pink << "=== X si O (C++) ===\n\n" << colors::reset;
    cout << "     0   1   2\n";

    for (int i = 0; i < 3; ++i) {
    
        cout << " " << i << " ";
        
        for (int j = 0; j < 3; ++j) {
            char val = board[i][j];
            if (val == 'X') {
                cout << colors::pink << "  X" << colors::reset;
            } else if (val == 'O') {
                cout << colors::cyan << "  O" << colors::reset;
            } else {
                cout << " ";
            }
        
            if (j < 2) {
                cout << colors::gray << "|" << colors::reset;
        }
    }
      cout << "\n";
      if (i < 2) {
        cout << colors :: gray << "    --+--+--\n" << colors :: reset;
      }
    }
    cout << "\n";
 }

 bool makeMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) return false;
    if (board[row][col] != ' ') return false;

    board[row][col] = currentPlayer;
    return true;
 }

 void switchPlayer() {
    currentPlayer = (currentPlayer == 'X')? 'O' : 'X';
 }

 bool checkWin() {
    for (int i = 0; i < 3; ++i) {
        //linii si coloane
        if (board[i][0] != ' ' && board [i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    //diagonale
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    
    return false;
 }

 bool isBoardFull() const{
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
 }
 char getCurrentPlayer() const { return currentPlayer;}
};

int main() {
    TicTacToe game;
    int row, col;

    while (true) {
        game.drawBoard();
        char current = game.getCurrentPlayer();

        cout << "Randul jucatorului ";
        if (current = 'X') {
            cout << colors::pink << "  X" << colors::reset;
        } else {
            cout << colors::cyan << "  O" << colors::reset;
        }
        cout << ".\nIntrodu linia si coloana (ex: 0 1): ";

        if (!(cin >> row >> col)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (!game.makeMove(row, col)) {
            continue;
        }

        if (game.checkWin()) {
            game.drawBoard();
            cout << "Felicitari! Jucatorul " << (current == 'X' ? colors::pink : colors::cyan) << current << colors::reset << " a castigat!\n";
            break;
        }
        if (game.isBoardFull()) {
            game.drawBoard();
            cout << "Remiza!\n";
            break;
        }
        game.switchPlayer();
    }
return 0;
}
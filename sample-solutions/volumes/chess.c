#include "student.h"
#include <stddef.h>

typedef struct {
    int x;
    int y;
} Direction;

void mark(int num_spaces, Direction movement[4], Position pos,
          char board[8][8]) {
    for (int i = 1; i <= num_spaces; ++i) {
        for (int j = 0; j < 4; ++j) {
            int new_row = pos.row + i * movement[j].x;
            int new_col = pos.col + i * movement[j].y;
            if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8)
                board[new_row][new_col] = 'X';
        }
    }
}

void mark_moves(char piece, Position pos, char board[8][8]) {
    /*
        Reference:
        K - King
        Q - Queen
        R - Rook
        B - Bishop
        N - Knight
    */
    Direction straight_move[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Direction diagonal_move[4] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    Direction knight_move1[4] = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    Direction knight_move2[4] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
    switch (piece) {
    case 'K':
        mark(1, straight_move, pos, board);
        mark(1, diagonal_move, pos, board);
        break;
    case 'Q':
        mark(8, straight_move, pos, board);
        mark(8, diagonal_move, pos, board);
        break;
    case 'R':
        mark(8, straight_move, pos, board);
        break;
    case 'B':
        mark(8, diagonal_move, pos, board);
        break;
    case 'N':
        mark(1, knight_move1, pos, board);
        mark(1, knight_move2, pos, board);
        break;
    }
    board[pos.row][pos.col] = piece;
}

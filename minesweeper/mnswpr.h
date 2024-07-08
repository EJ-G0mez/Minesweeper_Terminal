#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16
#define MAXBOMBS 40

struct tile {
    bool bomb;
    int adjacent;
    bool flagged;
    bool revealed;
};


void set_adjacent(struct tile board[SIZE][SIZE]);

void print_board(struct tile board[SIZE][SIZE]);

void check_adjacent(struct tile board[SIZE][SIZE], int myi, int myj, int theiri, int theirj);

void set_board(struct tile board[SIZE][SIZE]);

int check_tile(int x, int y, struct tile board[SIZE][SIZE]);

void set_flagged(int y, int x, struct tile board[SIZE][SIZE]);

int set_revealed(int y, int x, struct tile board[SIZE][SIZE]);

int clear_area(int y, int x, struct tile board[SIZE][SIZE]);

void print_cleared_board(struct tile board[SIZE][SIZE]);

void print_menu();

bool win_condition(struct tile board[SIZE][SIZE]);

void game_over();
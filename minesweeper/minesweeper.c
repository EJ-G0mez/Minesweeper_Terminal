#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8
#define MAXBOMBS 10

struct tile {
    bool bomb;
    int adjacent;
    bool flagged;
    bool revealed;
};

typedef struct tile tile;

void set_adjacent(tile board[SIZE][SIZE]);

void print_board(tile board[SIZE][SIZE]);

void check_adjacent(tile board[SIZE][SIZE], int myX, int myY, int theirx, int theiry);

void set_board(tile board[SIZE][SIZE]);

int check_tile(int x, int y, tile board[SIZE][SIZE]);

void set_flagged(int y, int x, tile board[SIZE][SIZE]);

int set_revealed(int y, int x, tile board[SIZE][SIZE]);

int clear_area(int y, int x, tile board[SIZE][SIZE]);

void print_over_board(tile board[SIZE][SIZE]);

void print_menu();

bool win_condition(tile board[SIZE][SIZE]);

void game_over();

int main(void){

    tile board[SIZE][SIZE];

    set_board(board);
    set_adjacent(board);
    print_menu();

    int x;
    int y;
    char start[10];
    int option;
    bool win;
    int reveal;
    scanf("%s", &start);
    if(strcmp("start",start) == 0){
        while(true){
            print_board(board);
            printf("Options: \n");
            printf("\t1. Reveal tile\n");
            printf("\t2. Flag/Unflag tile\n");
            printf("\t3. End game\n");
            printf("Input: ");
            scanf("%i", &option);
            switch(option){
                case 1:
                    printf("Coordinate X: ");
                    scanf("%i", &x);
                    printf("Coordinate Y: ");
                    scanf("%i", &y);
                    reveal = set_revealed(x,y,board);
                    if(reveal == 1){
                        print_board(board);
                        game_over();
                        return 0;
                    } else if(reveal == -1){
                        printf("Invalid coordintaes, please try again.\n");
                    } else if(reveal == -2){
                        printf("This tile has already been revealed\n");
                    } else if(reveal == 2){
                        printf("This tile has been flagged\n");
                    }
                    break;
                case 2:
                    printf("Coordinate X: ");
                    scanf("%i", &x);
                    printf("Coordinate Y: ");
                    scanf("%i", &y);
                    set_flagged(x,y,board);
                    break;
                case 3:
                    print_board(board);
                    return 0;
            }
            win = win_condition(board);
            if(win){
                print_board(board);
                return 1;
            }
        }
    }
}

void set_board(tile board[SIZE][SIZE]){

    srand(time(NULL));
    
    int bombs = 0;
    int x;
    int y;

    while(bombs < MAXBOMBS){
        x = rand() % SIZE;
        y = rand() % SIZE;
        board[x][y].bomb = true;
        bombs++;
    }

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j].bomb != true){
                board[i][j].bomb = false;      
            }
            board[i][j].adjacent = 0;
            board[i][j].flagged = false;
            board[i][j].revealed = false;
        }
    }
    
}

void set_adjacent(tile board[SIZE][SIZE]){

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(i != 0){
                if(j != 0){
                    check_adjacent(board, i, j, i, j-1);
                    check_adjacent(board, i ,j ,i-1, j-1);
                    if (i != SIZE-1){
                        check_adjacent(board,i,j, i+1, j-1);
                    }
                }
                if(j != SIZE-1){
                    check_adjacent(board,i,j ,i,j+1);
                    check_adjacent(board,i,j,i-1,j+1);
                   if(i != SIZE-1){
                    check_adjacent(board,i,j,i+1,j+1);
                   } 
                }
                check_adjacent(board,i,j,i-1, j);
                if(i != SIZE-1){
                    check_adjacent(board,i,j,i+1,j);
                }
            } else {
                if(j != 0){
                    check_adjacent(board, i, j, i, j-1);
                    check_adjacent(board,i,j, i+1, j-1);

                }
                if(j != SIZE-1){
                    check_adjacent(board,i,j ,i,j+1);
                    check_adjacent(board,i,j,i+1,j+1);
                }
                check_adjacent(board,i,j,i+1,j);
            }
        }
    }
}

void check_adjacent(tile board[SIZE][SIZE], int myX, int myY, int theirx, int theiry){
    if(!board[myX][myY].bomb){
        if(board[theirx][theiry].bomb == true){
            board[myX][myY].adjacent++;
        }
    }
}

void print_board(tile board[SIZE][SIZE]){
    printf("* $ *  ");
    for(int x = 0; x < SIZE; x++){
        if(x < 10){
            printf("+ %i +  ", x);
        } else {
            printf("+ %i + ", x);
        }
    }
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        if(i < 10){
            printf("+ %i +  ", i);
        } else {
            printf("+ %i + ", i);
        }
        for(int j = 0; j < SIZE; j++){
            if(board[i][j].revealed && !board[i][j].flagged && board[i][j].bomb){
                    printf("\033[1;30m[ X ]  \033[1;0m" );
            }
            if(board[i][j].revealed && !board[i][j].flagged && !board[i][j].bomb){
                switch(board[i][j].adjacent){
                    case 0:
                        printf("[ %i ]  ", board[i][j].adjacent);
                        break;
                    case 1:
                        printf("\033[1;34m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 2: 
                        printf("\033[1;32m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 3:
                        printf("\033[1;31m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 4:
                        printf("\033[1;36m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 5:
                        printf("\033[1;33m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 6:
                        printf("\033[1;35m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 7:
                        printf("\033[1;30m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 8:
                        printf("\033[1;37m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                }
            }
            if(!board[i][j].revealed && board[i][j].flagged){
                printf("\033[1;35m[ F ]  \033[1;0m");
            }
            if(!board[i][j].revealed && !board[i][j].flagged){
                printf("[ # ]  ");
            }
        }
        printf("\n");
    }
}

int check_tile(int x, int y, tile board[SIZE][SIZE]){
    if(x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0){
        return -1;
    }
    if(board[x][y].revealed){
        return -2;
    } else {
        if(board[x][y].flagged){
            if(board[x][y].bomb){
                return 2;
            }
        }else{
            if(board[x][y].bomb){
                return 1;
            }else{
                return 0;
            }
        }
    }
}

void set_flagged(int y, int x, tile board[SIZE][SIZE]){
    if(!board[x][y].revealed){
        board[x][y].flagged = !board[x][y].flagged;
    }
}

int set_revealed(int y, int x, tile board[SIZE][SIZE]){
    int tile;
    tile = check_tile(x,y,board);
    switch (tile){
    case -1:
        return -1;
    case -2:
        return -2;
    case 0:
        clear_area(y,x,board);
        return 0;
    case 1:
        board[x][y].revealed = true;
        return 1;
    case 2:
        return 2;
    default:
        return 0;
    }
}

int clear_area(int y, int x, tile board[SIZE][SIZE]){
    int tile = check_tile(x,y,board);
    if(tile != 0){
        return 0;
    }else{
        board[x][y].revealed = true;
        if(board[x][y].adjacent == 0){
            if(x != 0){
                if(y != 0){
                    clear_area(y-1,x,board); 
                    clear_area(y-1,x-1,board);
                    if (x != SIZE-1){
                        clear_area(y-1,x+1,board);
                    }
                }
                if(y != SIZE-1){
                    clear_area(y+1,x,board);
                    clear_area(y+1,x-1,board);
                    if(x != SIZE-1){
                        clear_area(y+1,x+1,board);
                    } 
                }
                clear_area(y,x-1,board);
                if(x != SIZE-1){
                    clear_area(y,x+1,board);
                }
            } else {
                if(y != 0){
                clear_area(y-1,x,board);
                clear_area(y-1,x+1,board);
                }
                if(y != SIZE-1){
                    clear_area(y+1,x ,board);
                    clear_area(y+1,x+1,board);
                }   
                clear_area(y,x+1,board);
            }
        }
        return 0;
    }
}

void print_over_board(tile board[SIZE][SIZE]){
     printf("* $ *  ");
    for(int x = 0; x < SIZE; x++){
        if(x < 10){
            printf("+ %i +  ", x);
        } else {
            printf("+ %i + ", x);
        }
    }
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        if(i < 10){
            printf("+ %i +  ", i);
        } else {
            printf("+ %i + ", i);
        }
        for(int j = 0; j < SIZE; j++){
            if(!board[i][j].flagged && board[i][j].bomb){
                    printf("\033[1;30m[ X ]  \033[1;0m" );
            }
            if(board[i][j].revealed && !board[i][j].flagged && !board[i][j].bomb){
                switch(board[i][j].adjacent){
                    case 0:
                        printf("[ %i ]  ", board[i][j].adjacent);
                        break;
                    case 1:
                        printf("\033[1;34m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 2: 
                        printf("\033[1;32m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 3:
                        printf("\033[1;31m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 4:
                        printf("\033[1;36m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 5:
                        printf("\033[1;33m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 6:
                        printf("\033[1;35m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 7:
                        printf("\033[1;30m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                    case 8:
                        printf("\033[1;37m[ %i ]  \033[0m", board[i][j].adjacent);
                        break;
                }
            }
            if(!board[i][j].revealed && board[i][j].flagged && board[i][j].bomb){
                printf("\033[1;35m[ F ]  \033[1;0m");
            }
            if(!board[i][j].revealed && board[i][j].flagged && !board[i][j].bomb){
                printf("\033[1;32m[ F ]  \033[1;0m");
            }
            if(!board[i][j].revealed && !board[i][j].flagged){
                printf("[ # ]  ");
            }
        }
        printf("\n");
    }
}

void print_menu(){

    printf("##################################################################\n");
    printf(" _      _  _      _____ ____  _      _____ _____ ____  _____ ____ \n");
    printf("/ \\__/|/ \\/ \\  /|/  __// ___\\/ \\  /|/  __//  __//  __\\/  __//  __\\ \n");
    printf("| |\\/||| || |\\ |||  \\  |    \\| |  |||  \\  |  \\  |  \\/||  \\  |  \\/|\n");
    printf("| |  ||| || | \\|||  /_ \\___ || |/\\|||  /_ |  /_ |  __/|  /_ |    /\n");
    printf("\\_/  \\|\\_/\\_/  \\|\\____\\\\____/\\_/  \\|\\____\\\\____\\\\_/   \\____\\\\_/\\_\\ \n");
    printf("##################################################################\n");
    printf("\033[1;33mWelcome to minesweeper!!!!\033[1;0m\n");
    printf("\033[1;33mWrite start to begin.\033[1;0m \n");
    printf("\033[1;33mPress Ctrl+C to end the program\033[1;0m \n");
}

bool win_condition(tile board[SIZE][SIZE]){
    int goodTiles;
    goodTiles = 0;
    int totalTiles;
    totalTiles = SIZE * SIZE;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j].revealed && !board[i][j].bomb){
                goodTiles++;
            }
            if(board[i][j].flagged && board[i][j].bomb){
                goodTiles++;
            }
        }
    }
    if(goodTiles == totalTiles){
        return true;
    } else {
        return false;
    }
}

void game_over(){
    printf("  /$$$$$$                                           /$$$$$$                               \n");
    printf(" /$$__  $$                                         /$$__  $$                              \n");
    printf("| $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$       | $$  \\ $$ /$$    /$$ /$$$$$$   /$$$$$$ \n");
    printf("| $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$      | $$  | $$|  $$  /$$//$$__  $$ /$$__  $$\n");
    printf("| $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$      | $$  | $$ \\  $$/$$/| $$$$$$$$| $$  \\__/\n");
    printf("| $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/      | $$  | $$  \\  $$$/ | $$_____/| $$      \n");
    printf("|  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$      |  $$$$$$/   \\  $/  |  $$$$$$$| $$      \n");
    printf(" \\______/  \\_______/|__/ |__/ |__/ \\_______/       \\______/     \\_/    \\_______/|__/      \n");
}
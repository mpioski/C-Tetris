#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
 
typedef enum {
    Empty = 0,
    Blue,
    Green
} BoardPieceColor;
 
#define COLOR_ENUM_SIZE 3
 
#define SQUARE_WIDTH    2
#define SQUARE_HEIGHT   2
 
#define STRAIGHT_WIDTH  1
#define STRAIGHT_HEIGHT 5
 
typedef enum {
    turn0,
    turn90,
    turn180,
    trun270
} BoardPieceOrientation;
 
typedef struct {
    BoardPieceColor color;
    int positionX;
    int positionY;
    BoardPieceOrientation orientation;
} TetrisPiece;
 
 
#define SCREEN_HEIGHT   100
 
#define BOARD_WIDTH     16
#define BOARD_HEIGHT    10
 
BoardPieceColor board[BOARD_HEIGHT][BOARD_WIDTH];
  
/*
    Teclas de controle:
        A = Move para esquerda
        D = Move para direita
        S = Move para baixo
        W = Escreve a peça permanentemente no tabuleiro
*/
 
/* Key Scan Codes:
UP = 72
DOWN = 80
LEFT = 75
RIGHT = 77
ESC = 27
*/
 
void clearBoard();
void clearScreen();
void printBoard();
BoardPieceColor newPieceColor();
TetrisPiece currentPiece;
void movePieceToRight();
void movePieceToLeft();
void movePieceDown();
void beepAlert();
void clearPieceFromBoard();
void writePieceToBoard();
 
int main() {
    srand((unsigned int)time(NULL));
    clearBoard();
    setlocale(LC_ALL, "Portuguese");
 
    char key;
 
    currentPiece.color = newPieceColor();
    currentPiece.positionX = 0;
    currentPiece.positionY = 0;
    currentPiece.orientation = turn0;
    writePieceToBoard();
 
    while (1) {
        clearScreen();
        printBoard();
        key = getchar();
 
        if (key == 'D' || key == 'd') {
            movePieceToRight();
        }
        if (key == 'A' || key == 'a') {
            movePieceToLeft();
        }
        if (key == 'S' || key == 's') {
            movePieceDown();
        }
        if (key == 'W' || key == 'w') {
            currentPiece.color = newPieceColor();
            currentPiece.positionX = 0;
            currentPiece.positionY = 0;
            currentPiece.orientation = turn0;
            writePieceToBoard();
        }
 
    }
 
}
 
void clearBoard() {
    int i, j;
    for (i = 0; i < BOARD_WIDTH; i++)
        for (j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = Empty;
 
}
 
void clearScreen() {
    int i;
    for (i = 0; i < SCREEN_HEIGHT; i++)
        puts("");
}
 
void printBoard() {
    int i, j;
 
    for (i = 0; i < BOARD_HEIGHT; i++) {
        printf("[");
        for (j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] == Empty)
                printf(" ");
            else {
                switch (board[i][j]){
                    case Blue:
                        printf("B");
                        break;
                    case Green:
                        printf("G");
                        break;
                }
            }
        }
        puts("]");
    }
}
 
BoardPieceColor newPieceColor() {
    return (BoardPieceColor)((rand() % (COLOR_ENUM_SIZE - 1)) + 1);
}
 
void movePieceToRight() {

    int i, j;
    int newPosX;
 
    newPosX = currentPiece.positionX + 1;
 
    switch (currentPiece.color)
    {
        case Blue:
            if (currentPiece.positionX + SQUARE_WIDTH >= BOARD_WIDTH) {
                beepAlert();
                return;
            }
 
            clearPieceFromBoard();
            for(i=0; i<SQUARE_WIDTH; i++) 
                for (j = 0; j<SQUARE_HEIGHT; j++) 
                    if (board[currentPiece.positionY + j][newPosX + i] != Empty) {
                        writePieceToBoard(); 
                        beepAlert();
                        return;
                    }
 
            clearPieceFromBoard();
            currentPiece.positionX = newPosX;
            writePieceToBoard();
            break;
 
        case Green:
            if (currentPiece.positionX + STRAIGHT_WIDTH >= BOARD_WIDTH) {
                beepAlert();
                return;
            }

            clearPieceFromBoard();
            for (i = 0; i<STRAIGHT_WIDTH; i++) 
                for (j = 0; j<STRAIGHT_HEIGHT; j++) 
                    if (board[currentPiece.positionY + j][newPosX + i] != Empty) {
                        writePieceToBoard();
                        beepAlert();
                        return;
                    }
 
            clearPieceFromBoard();
            currentPiece.positionX = newPosX;
            writePieceToBoard();
            break;
    }
}
 
void movePieceToLeft() {

    int i, j;
    int newPosX;
 
    newPosX = currentPiece.positionX - 1;
 
    switch (currentPiece.color)
    {
    case Blue:
        if (newPosX < 0) {
            beepAlert();
            return;
        }
 
        clearPieceFromBoard();
        for (i = 0; i<SQUARE_WIDTH; i++) 
            for (j = 0; j<SQUARE_HEIGHT; j++) 
                if (board[currentPiece.positionY + j][newPosX + i] != Empty) {
                    writePieceToBoard();
                    beepAlert();
                    return;
                }
 
        clearPieceFromBoard();
        currentPiece.positionX = newPosX;
        writePieceToBoard();
        break;
 
    case Green:
        if (newPosX < 0) {
            beepAlert();
            return;
        }
 
        clearPieceFromBoard();
        for (i = 0; i<STRAIGHT_WIDTH; i++) 
            for (j = 0; j<STRAIGHT_HEIGHT; j++) 
                if (board[currentPiece.positionY + j][newPosX + i] != Empty) {
                    writePieceToBoard();
                    beepAlert();
                    return;
                }
 
        clearPieceFromBoard();
        currentPiece.positionX = newPosX; 
        writePieceToBoard();
        break;
    }
}
 
void movePieceDown() {

    int i, j;
    int newPosY;
 
    newPosY = currentPiece.positionY + 1;
 
    switch (currentPiece.color)
    {
    case Blue:
        if (currentPiece.positionY + SQUARE_HEIGHT >= BOARD_HEIGHT) { 
            beepAlert();
            return;
        }

        clearPieceFromBoard();
        for (i = 0; i<SQUARE_WIDTH; i++) 
            for (j = 0; j<SQUARE_HEIGHT; j++)
                if (board[newPosY + j][currentPiece.positionX + i] != Empty) {
                    writePieceToBoard(); 
                    beepAlert();
                    return;
                }
 
        clearPieceFromBoard(); 
        currentPiece.positionY = newPosY;
        writePieceToBoard(); 
        break;
 
    case Green:
        if (currentPiece.positionY + STRAIGHT_HEIGHT >= BOARD_HEIGHT) { 
            beepAlert();
            return;
        }
 
        clearPieceFromBoard();
        for (i = 0; i<STRAIGHT_WIDTH; i++)
            for (j = 0; j<STRAIGHT_HEIGHT; j++)
                if (board[newPosY + j][currentPiece.positionX + i] != Empty) {
                    writePieceToBoard(); 
                    beepAlert();
                    return;
                }

        clearPieceFromBoard();
        currentPiece.positionY = newPosY; 
        writePieceToBoard();
        break;
    }
}
 
void beepAlert() {
    printf("\a\n");
}
 
void clearPieceFromBoard() {
    int i, j;
 
    switch (currentPiece.color)
    {
        case Blue:
            for (i = 0; i<SQUARE_WIDTH; i++) 
                for (j = 0; j<SQUARE_HEIGHT; j++)
                    board[currentPiece.positionY + j][currentPiece.positionX + i] = Empty;
            break;
        case Green:
            for (i = 0; i<STRAIGHT_WIDTH; i++)
                for (j = 0; j<STRAIGHT_HEIGHT; j++)
                    board[currentPiece.positionY + j][currentPiece.positionX + i] = Empty;
            break;
    }
}
 
void writePieceToBoard() {
    int i, j;
    switch (currentPiece.color)
    {
        case Blue:
            for (i = 0; i<SQUARE_WIDTH; i++) 
                for (j = 0; j<SQUARE_HEIGHT; j++) 
                    board[currentPiece.positionY + j][currentPiece.positionX + i] = Blue;
            break;
        case Green:
            for (i = 0; i<STRAIGHT_WIDTH; i++) 
                for (j = 0; j<STRAIGHT_HEIGHT; j++)
                    board[currentPiece.positionY + j][currentPiece.positionX + i] = Green;
            break;
    }
}

// tank_game.h

#ifndef TANK_GAME_H
#define TANK_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Defines
#define BOARD_ROWS      11
#define BOARD_COLS      11
#define SAFETY_WALL     1
// Total size includes safety walls on both sides
#define TOTAL_ROWS      (BOARD_ROWS + 2 * SAFETY_WALL)
#define TOTAL_COLS      (BOARD_COLS + 2 * SAFETY_WALL)

#define EXIT_CODE       999
#define MAX_RICOCHETS   5

// Symbols
#define SYM_EMPTY       ' '
#define SYM_WALL        'X'
#define SYM_TANK        'O'
#define SYM_BORDER      '#'

// Directions
#define DIR_UP          1
#define DIR_RIGHT       2
#define DIR_DOWN        3
#define DIR_LEFT        4

// Player IDs
#define PLAYER_1        1
#define PLAYER_2        2

// Struct definition
typedef struct Position
{
    int nRow;
    int nCol;
} Position;

// Function Prototypes

void InitGame(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
              Position* outPosP1,
              Position* outPosP2);

void PrintBoard(char arrcBoard[TOTAL_ROWS][TOTAL_COLS]);

int MakeMove(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
             Position* iopTankPos,
             Position inEnemyPos,
             int inActionType);

void MoveTank(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
              Position* iopTankPos,
              Position inEnemyPos);

int FireNormal(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
               Position inTankPos,
               Position inEnemyPos);

int FireRicochet(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
                 Position inTankPos,
                 Position inEnemyPos);

int AirdropBomb(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
                Position inTankPos,
                Position inEnemyPos);

int CheckWallsRemaining(char arrcBoard[TOTAL_ROWS][TOTAL_COLS]);

#endif // TANK_GAME_H
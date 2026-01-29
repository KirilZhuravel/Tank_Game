// main.c

#include "tank_game.h"

//---
//
// Tank Strategy Game
//
// General      : A 2-player turn-based tank game with destructible environment.
//
// Input        : User commands for movement and firing (integers).
//
// Process      : Manages turns, movement logic, firing calculations, and win conditions.
//
// Output       : Prints the board state and game result.
//
// Programmer   : Kiril Zhuravel
// Student No   : 345959019
// Date         : 13.12.2025
//
//---
int main(void)
{
    // Variable definition
    char arrcBoard[TOTAL_ROWS][TOTAL_COLS];
    Position posPlayer1;
    Position posPlayer2;
    int nTurnCounter = 0;
    int nAction;
    int nGameStatus = 0; // 0=Running, 1=P1 Win, 2=P2 Win, 3=Draw
    int nMoveResult;
    Position* pCurrentPos;
    Position enemyPos;
    int nCurrentPlayer;

    // Code section
    InitGame(arrcBoard, &posPlayer1, &posPlayer2);

    // Main Game Loop
    while (nGameStatus == 0)
    {
        PrintBoard(arrcBoard);

        // Determine whose turn it is
        if (nTurnCounter % 2 == 0)
        {
            nCurrentPlayer = PLAYER_1;
            pCurrentPos = &posPlayer1;
            enemyPos = posPlayer2;
            printf("Player 1 (Left Tank) Turn.\n");
        }
        else
        {
            nCurrentPlayer = PLAYER_2;
            pCurrentPos = &posPlayer2;
            enemyPos = posPlayer1;
            printf("Player 2 (Right Tank) Turn.\n");
        }

        // Check for Draw (No walls left)
        if (CheckWallsRemaining(arrcBoard) == 0)
        {
            nGameStatus = 3;
            break;
        }

        // Menu
        printf("1. Move\n");
        printf("2. Normal Fire\n");
        printf("3. Ricochet Fire\n");
        printf("4. Airdrop Bomb\n");
        printf("999. Exit\n");
        printf("Choose action: ");
        scanf("%d", &nAction);

        if (nAction == EXIT_CODE)
        {
            printf("Exiting game...\n");

            break;
        }

        // Execute Move
        nMoveResult = MakeMove(arrcBoard, pCurrentPos, enemyPos, nAction);

        // Check Move Result
        if (nMoveResult == 1)
        {
            // Enemy hit -> Current player wins
            nGameStatus = nCurrentPlayer;
        }
        else if (nMoveResult == 2)
        {
            // Self hit -> Enemy wins
            if (nCurrentPlayer == PLAYER_1)
            {
                nGameStatus = PLAYER_2;
            }
            else
            {
                nGameStatus = PLAYER_1;
            }
        }

        nTurnCounter++;
    }

    // End Game Messages
    PrintBoard(arrcBoard);

    if (nGameStatus == 1)
    {
        printf("Player 1 WINS!\n");
    }
    else if (nGameStatus == 2)
    {
        printf("Player 2 WINS!\n");
    }
    else if (nGameStatus == 3)
    {
        printf("Game Over! It's a DRAW (No walls left).\n");
    }

    return (0);
}
// tank_game.c

#include "tank_game.h"

//---
//
// Init Game
//
// General      : Initializes the board with walls, borders, and tanks.
//
// Parameters   :
// arrcBoard    : The game board array (Out)
// outPosP1     : Pointer to Player 1 position (Out)
// outPosP2     : Pointer to Player 2 position (Out)
//
// Return Value : None.
//
//---
void InitGame(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
              Position* outPosP1,
              Position* outPosP2)
{
    // Variable definition
    int nRow;
    int nCol;
    int nPlayRow;
    int nPlayCol;

    // Code section
    // Initialize random seed
    srand((unsigned)time(NULL));

    // Fill the board
    for (nRow = 0; nRow < TOTAL_ROWS; ++nRow)
    {
        for (nCol = 0; nCol < TOTAL_COLS; ++nCol)
        {
            // Check for safety wall (borders)
            if (nRow == 0 || nRow == TOTAL_ROWS - 1 ||
                nCol == 0 || nCol == TOTAL_COLS - 1)
            {
                arrcBoard[nRow][nCol] = SYM_BORDER;
            }
            else
            {
                // Inner field logic (convert to 1-based index for logic check)
                // However, our loop indices match the matrix indices directly.
                // We need to check parity for destructible walls.
                // The task says: Even indices for both row and col inside the field.
                // Since we have a safety wall of 1, the "game" index 1 is actually "logical" index 1.
                // Let's rely on absolute matrix indices for simplicity, ensuring consistency.

                // Adjusting to 1-based logic of the inner field:
                nPlayRow = nRow;
                nPlayCol = nCol;

                // Task: "Even indices". If we assume 1-based logic (1..11),
                // then (2,2), (2,4)... are walls.
                // In our matrix (indices 1..11), this maps directly.
                if ((nPlayRow % 2 == 0) && (nPlayCol % 2 == 0))
                {
                    arrcBoard[nRow][nCol] = SYM_WALL;
                }
                else
                {
                    arrcBoard[nRow][nCol] = SYM_EMPTY;
                }
            }
        }
    }

    // Set Tanks Position
    // Player 1 (Left): Middle of column, left side.
    // Middle of 11 rows is row index 6 (1+5). Col index 1.
    outPosP1->nRow = 6;
    outPosP1->nCol = 1;
    arrcBoard[6][1] = SYM_TANK;

    // Player 2 (Right): Middle of column, right side.
    // Row index 6. Col index 11.
    outPosP2->nRow = 6;
    outPosP2->nCol = 11;
    arrcBoard[6][11] = SYM_TANK;
}

//---
//
// Print Board
//
// General      : Prints the current state of the game board.
//
// Parameters   :
// arrcBoard    : The game board array (In)
//
// Return Value : None.
//
//---
void PrintBoard(char arrcBoard[TOTAL_ROWS][TOTAL_COLS])
{
    // Variable definition
    int nRow;
    int nCol;

    // Code section
    printf("\n   Current Battlefield:\n");

    for (nRow = 0; nRow < TOTAL_ROWS; ++nRow)
    {
        for (nCol = 0; nCol < TOTAL_COLS; ++nCol)
        {
            printf("%c ", arrcBoard[nRow][nCol]);
        }
        printf("\n");
    }
    printf("\n");
}

//---
//
// Make Move
//
// General      : Routes the user choice to specific action functions.
//
// Parameters   :
// arrcBoard    : The game board (In/Out)
// iopTankPos   : Current player's position pointer (In/Out)
// inEnemyPos   : Enemy player's position (In)
// inActionType : The selected menu option (In)
//
// Return Value : 0 if game continues, 1 if current player wins, 2 if current player loses (suicide).
//
//---
int MakeMove(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
             Position* iopTankPos,
             Position inEnemyPos,
             int inActionType)
{
    // Variable definition
    int nResult = 0;

    // Code section
    switch (inActionType)
    {
    case (1):
    {
        MoveTank(arrcBoard, iopTankPos, inEnemyPos);

        break;
    }
    case (2):
    {
        nResult = FireNormal(arrcBoard, *iopTankPos, inEnemyPos);

        break;
    }
    case (3):
    {
        nResult = FireRicochet(arrcBoard, *iopTankPos, inEnemyPos);

        break;
    }
    case (4):
    {
        nResult = AirdropBomb(arrcBoard, *iopTankPos, inEnemyPos);

        break;
    }
    default:
    {
        printf("Invalid action!\n");

        break;
    }
    }

    return (nResult);
}

//---
//
// Move Tank
//
// General      : Handles tank movement logic (stops at obstacles).
//
// Parameters   :
// arrcBoard    : The game board (In/Out)
// iopTankPos   : Pointer to tank position (In/Out)
// inEnemyPos   : Enemy tank position (In)
//
// Return Value : None.
//
//---
void MoveTank(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
              Position* iopTankPos,
              Position inEnemyPos)
{
    // Variable definition
    int nDir;
    int nSteps;
    int nStepCount;
    int nDRow = 0;
    int nDCol = 0;
    int nNextRow;
    int nNextCol;

    // Code section
    printf("Enter Direction (1-Up, 2-Right, 3-Down, 4-Left): ");
    scanf("%d", &nDir);
    printf("Enter Steps: ");
    scanf("%d", &nSteps);

    // Set Delta based on direction
    if (nDir == DIR_UP)    { nDRow = -1; }
    if (nDir == DIR_DOWN)  { nDRow = 1; }
    if (nDir == DIR_RIGHT) { nDCol = 1; }
    if (nDir == DIR_LEFT)  { nDCol = -1; }

    // Clear current position
    arrcBoard[iopTankPos->nRow][iopTankPos->nCol] = SYM_EMPTY;

    // Process movement step by step
    for (nStepCount = 0; nStepCount < nSteps; ++nStepCount)
    {
        nNextRow = iopTankPos->nRow + nDRow;
        nNextCol = iopTankPos->nCol + nDCol;

        // Check for collision (Border, Wall, or Enemy Tank)
        if (arrcBoard[nNextRow][nNextCol] != SYM_EMPTY)
        {
            printf("Movement blocked at (%d, %d)\n", nNextRow, nNextCol);

            break; // Stop movement
        }

        // Update position
        iopTankPos->nRow = nNextRow;
        iopTankPos->nCol = nNextCol;
    }

    // Place tank at new position
    arrcBoard[iopTankPos->nRow][iopTankPos->nCol] = SYM_TANK;
}

//---
//
// Fire Normal
//
// General      : Fires a shot in a straight line.
//
// Parameters   :
// arrcBoard    : The game board (In/Out)
// inTankPos    : Firing tank position (In)
// inEnemyPos   : Enemy tank position (In)
//
// Return Value : 1 if enemy hit, 0 otherwise.
//
//---
int FireNormal(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
               Position inTankPos,
               Position inEnemyPos)
{
    // Variable definition
    int nDir;
    int nDRow = 0;
    int nDCol = 0;
    int nCurrRow;
    int nCurrCol;
    int nHit = 0;

    // Code section
    printf("Enter Fire Direction (1-Up, 2-Right, 3-Down, 4-Left): ");
    scanf("%d", &nDir);

    if (nDir == DIR_UP)    { nDRow = -1; }
    if (nDir == DIR_DOWN)  { nDRow = 1; }
    if (nDir == DIR_RIGHT) { nDCol = 1; }
    if (nDir == DIR_LEFT)  { nDCol = -1; }

    nCurrRow = inTankPos.nRow + nDRow;
    nCurrCol = inTankPos.nCol + nDCol;

    while (1)
    {
        // Check Boundary (Safety Wall)
        if (arrcBoard[nCurrRow][nCurrCol] == SYM_BORDER)
        {
            // Hit edge, nothing happens
            break;
        }

        // Check Destructible Wall
        if (arrcBoard[nCurrRow][nCurrCol] == SYM_WALL)
        {
            arrcBoard[nCurrRow][nCurrCol] = SYM_EMPTY;
            printf("Wall destroyed at (%d, %d)\n", nCurrRow, nCurrCol);

            break; // Shot stops
        }

        // Check Enemy Tank
        if (nCurrRow == inEnemyPos.nRow && nCurrCol == inEnemyPos.nCol)
        {
            printf("Direct hit on enemy tank!\n");
            nHit = 1;

            break;
        }

        // Move projectile
        nCurrRow += nDRow;
        nCurrCol += nDCol;
    }

    return (nHit);
}

//---
//
// Fire Ricochet
//
// General      : Fires a shot that turns right upon hitting borders.
//
// Parameters   :
// arrcBoard    : The game board (In/Out)
// inTankPos    : Firing tank position (In)
// inEnemyPos   : Enemy tank position (In)
//
// Return Value : 1 if enemy hit, 2 if self hit, 0 otherwise.
//
//---
int FireRicochet(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
                 Position inTankPos,
                 Position inEnemyPos)
{
    // Variable definition
    int nDir;
    int nDRow = 0;
    int nDCol = 0;
    int nCurrRow;
    int nCurrCol;
    int nBounces = 0;
    int nTemp;

    // Code section
    printf("Enter Initial Direction (1-Up, 2-Right, 3-Down, 4-Left): ");
    scanf("%d", &nDir);

    // Initial Delta
    if (nDir == DIR_UP)    { nDRow = -1; nDCol = 0; }
    if (nDir == DIR_DOWN)  { nDRow = 1;  nDCol = 0; }
    if (nDir == DIR_RIGHT) { nDRow = 0;  nDCol = 1; }
    if (nDir == DIR_LEFT)  { nDRow = 0;  nDCol = -1; }

    nCurrRow = inTankPos.nRow + nDRow;
    nCurrCol = inTankPos.nCol + nDCol;

    while (nBounces < MAX_RICOCHETS)
    {
        // Check Boundary -> Ricochet
        if (arrcBoard[nCurrRow][nCurrCol] == SYM_BORDER)
        {
            // Step back
            nCurrRow -= nDRow;
            nCurrCol -= nDCol;

            // Change Direction 90 degrees clockwise (Right)
            // (1,0) -> (0,-1) -> (-1,0) -> (0,1) -> (1,0)
            // Logic: old_row -> new_col, old_col -> -new_row (Standard rotation matrix)
            // Or simpler mapping for Grid:
            // Up(-1,0) -> Right(0,1)
            // Right(0,1) -> Down(1,0)
            // Down(1,0) -> Left(0,-1)
            // Left(0,-1) -> Up(-1,0)

            if (nDRow == -1 && nDCol == 0)      { nDRow = 0; nDCol = 1; } // Up -> Right
            else if (nDRow == 0 && nDCol == 1)  { nDRow = 1; nDCol = 0; } // Right -> Down
            else if (nDRow == 1 && nDCol == 0)  { nDRow = 0; nDCol = -1; } // Down -> Left
            else if (nDRow == 0 && nDCol == -1) { nDRow = -1; nDCol = 0; } // Left -> Up

            nBounces++;
            printf("Ricochet! Count: %d\n", nBounces);
        }
        // Check Destructible Wall
        else if (arrcBoard[nCurrRow][nCurrCol] == SYM_WALL)
        {
            arrcBoard[nCurrRow][nCurrCol] = SYM_EMPTY;
            printf("Wall destroyed at (%d, %d)\n", nCurrRow, nCurrCol);

            return (0);
        }
        // Check Enemy Tank
        else if (nCurrRow == inEnemyPos.nRow && nCurrCol == inEnemyPos.nCol)
        {
            printf("Ricochet hit on enemy!\n");

            return (1);
        }
        // Check Self Hit
        else if (nCurrRow == inTankPos.nRow && nCurrCol == inTankPos.nCol)
        {
            printf("Suicide! You hit yourself!\n");

            return (2);
        }

        // Move projectile
        nCurrRow += nDRow;
        nCurrCol += nDCol;
    }

    printf("Ricochet missile fizzled out.\n");

    return (0);
}

//---
//
// Airdrop Bomb
//
// General      : Drops a 3x3 bomb with random destruction pattern.
//
// Parameters   :
// arrcBoard    : The game board (In/Out)
// inTankPos    : Firing tank position (In)
// inEnemyPos   : Enemy tank position (In)
//
// Return Value : 1 if enemy hit, 2 if self hit, 0 otherwise.
//
//---
int AirdropBomb(char arrcBoard[TOTAL_ROWS][TOTAL_COLS],
                Position inTankPos,
                Position inEnemyPos)
{
    // Variable definition
    int nTargetRow;
    int nTargetCol;
    int i;
    int j;
    int nRandVal;
    int nCheckRow;
    int nCheckCol;
    int nEnemyHit = 0;
    int nSelfHit = 0;

    // Code section
    printf("Enter Target Row (1-%d): ", BOARD_ROWS);
    scanf("%d", &nTargetRow);
    printf("Enter Target Col (1-%d): ", BOARD_COLS);
    scanf("%d", &nTargetCol);

    // Iterate 3x3 area around target
    for (i = -1; i <= 1; ++i)
    {
        for (j = -1; j <= 1; ++j)
        {
            nCheckRow = nTargetRow + i;
            nCheckCol = nTargetCol + j;

            // Generate random 0 or 1
            nRandVal = rand() % 2;

            // Only process if inside board and random val is 1
            if (nRandVal == 1 &&
                arrcBoard[nCheckRow][nCheckCol] != SYM_BORDER)
            {
                // Check contents
                if (arrcBoard[nCheckRow][nCheckCol] == SYM_WALL)
                {
                    arrcBoard[nCheckRow][nCheckCol] = SYM_EMPTY;
                }
                else if (nCheckRow == inEnemyPos.nRow && nCheckCol == inEnemyPos.nCol)
                {
                    nEnemyHit = 1;
                }
                else if (nCheckRow == inTankPos.nRow && nCheckCol == inTankPos.nCol)
                {
                    nSelfHit = 1;
                }
            }
        }
    }

    if (nSelfHit)
    {
        return (2);
    }
    if (nEnemyHit)
    {
        return (1);
    }

    return (0);
}

//---
//
// Check Walls Remaining
//
// General      : Checks if any destructible walls exist on board.
//
// Parameters   :
// arrcBoard    : The game board (In)
//
// Return Value : 1 if walls exist, 0 if empty (Draw).
//
//---
int CheckWallsRemaining(char arrcBoard[TOTAL_ROWS][TOTAL_COLS])
{
    // Variable definition
    int nRow;
    int nCol;

    // Code section
    for (nRow = 0; nRow < TOTAL_ROWS; ++nRow)
    {
        for (nCol = 0; nCol < TOTAL_COLS; ++nCol)
        {
            if (arrcBoard[nRow][nCol] == SYM_WALL)
            {
                return (1);
            }
        }
    }

    return (0);
}
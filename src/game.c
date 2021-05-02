#include <stdio.h>
#include "console.h"

// ============== Setup Stuff  =================
int frame = 1;
int doLoop = 1;
int finish = 0;
void setup();
void draw();

#define noLoop()    \
    do              \
    {               \
        doLoop = 0; \
        return;     \
    } while (0);

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)
// =============================================

// ============= Game Functions  ================
void drawMenu();
void drawGrid();
void drawTutorial();
void switchPlayer();
int checkWinner(char[3][3]);
void humanMove();
void aiMove();
int scores(int);
int minimax(char[3][3], int, int);
// =============================================

// ============== GLobal Vars  =================
char grid[3][3];
int mode = 0;
char currentPlayer[] = "Player X";

struct Position
{
    int x;
    int y;
};
struct Position pos;
// =============================================

void setup()
{
    clear();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = ' ';
    mode = 0;
    currentPlayer[7] = 'X';
    drawMenu();
    switch (mode)
    {
    case 1:
    case 2:
        doLoop = 1;
        draw();
        break;
    case 3:
        drawTutorial();
        setup();
        break;
    case 4:
        finish = 1;
        noLoop();
    }
}

void draw()
{
    clear();
    drawGrid();
    int winner = checkWinner(grid);

    if (winner)
    {
        if (winner == 1)
            printf("The Winner is X!!!\n");
        else if (winner == 2)
            printf("The Winner is O!!!\n");
        else
            printf("It's a Tie!!!\n");
        pause();
        printf("\n");
        noLoop();
    }

    clear();
    drawGrid();
    if (mode == 2 && currentPlayer[7] == 'X')
        aiMove();
    else
        humanMove();
    switchPlayer();
    ++frame;
}

void drawMenu()
{
    puts("Choose the mode that you want: ");
    puts("===============================");
    puts("1- Player vs Player Mode");
    puts("2- Player vs Computer Mode");
    puts("3- Tutorial");
    puts("4- Exit");

    int choice = 0;
    do
    {
        printf(": ");
        scanf("%d", &choice);
        getchar();

        if (choice < 1 || choice > 4)
        {
            printf("Not a valid option! Please choose again.\n");
            choice = 0;
        }
    } while (!choice);
    mode = choice;
}

void drawGrid()
{
    printf("   0   1   2\n");
    printf("0  %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
    printf("  -----------\n");
    printf("1  %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
    printf("  -----------\n");
    printf("2  %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
}

void drawTutorial()
{
    clear();
    puts("Tutorial: ");
    puts("=========");
    puts("Below is the grid for tic-tac-toe");
    drawGrid();
    pause();

    clear();
    puts("Tutorial: ");
    puts("=========");
    puts("You need to type row,col to place your your symbol in the cell");
    puts("For example let me say I Player X type 0,1");
    grid[0][1] = 'X';
    drawGrid();
    puts("\nNow I got My Symbol X into 0,1");
    puts("That's the end of the tutorial, enjoy!\n");
    pause();
}

void switchPlayer()
{
    if (currentPlayer[7] == 'X')
        currentPlayer[7] = 'O';
    else
        currentPlayer[7] = 'X';
}

int checkWinner(char board[3][3])
{
    // Check Horizentally
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
        {
            if (board[i][0] == 'X')
                return 1;
            else
                return 2;
        }

    // Check Vertically
    for (int j = 0; j < 3; j++)
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[2][j] != ' ')
        {
            if (board[0][j] == 'X')
                return 1;
            else
                return 2;
        }

    // Check Diagonally
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
    {
        if (board[1][1] == 'X')
            return 1;
        else
            return 2;
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[1][1] != ' ')
    {
        if (grid[1][1] == 'X')
            return 1;
        else
            return 2;
    }

    // Check For Tie
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
                count++;
    if (count == 0)
        return 3;
    return 0;
}

void humanMove()
{
    int success;
    do
    {
        printf("%s's Turn: ", currentPlayer);
        scanf("%d,%d", &pos.x, &pos.y);
        getchar();
        if ((pos.x < 0 || pos.x > 2) && (pos.y < 0 || pos.y > 2))
        {
            printf("Choose numbers between 0 and 2.\n");
            success = 0;
        }
        else if (grid[pos.x][pos.y] == ' ')
        {
            grid[pos.x][pos.y] = currentPlayer[7];
            success = 1;
        }
        else
        {
            printf("Spot Not available please choose again.\n");
            success = 0;
        }
    } while (!success);
}

void aiMove()
{
    int bestScore = -__INT_MAX__;
    struct Position bestMove;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
            {
                grid[i][j] = 'X'; // AI is X.
                int score = minimax(grid, 0, 0);
                grid[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove.x = i;
                    bestMove.y = j;
                }
            }
    grid[bestMove.x][bestMove.y] = 'X';
}

int scores(int result)
{
    if (result == 1)
        return 1;
    else if (result == 2)
        return -1;
    else
        return 0;
}

int minimax(char board[3][3], int depth, int isMax)
{
    int result = checkWinner(board);
    if (result != 0)
        return scores(result);
    if (isMax)
    {
        int bestScore = -__INT_MAX__;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int score = minimax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
        return bestScore;
    }
    else
    {
        int bestScore = __INT_MAX__;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = minimax(grid, depth + 1, 1);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
        return bestScore;
    }
}
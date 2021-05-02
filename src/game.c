#include <stdio.h>
#include "console.h"

// ============== Setup Stuff  =================
int frame = 1;
int doLoop = 1;
void setup();
void draw();

#define noLoop()    \
    do              \
    {               \
        doLoop = 0; \
        return;     \
    } while (0);
// =============================================

// ============= Game Functions  ================
void drawMenu();
void drawGrid();
void drawTutorial();
void switchPlayer();
void checkWinner();
// =============================================

// ============== GLobal Vars  =================
char grid[3][3];
int mode = 0;
char currentPlayer[] = "Player X";
int winner = 0;

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
    drawMenu();
    switch (mode)
    {
    case 1:
        draw();
        break;
    case 3:
        drawTutorial();
        setup();
        break;
    }
}

void draw()
{
    clear();
    drawGrid();
    checkWinner();

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
        if (choice == 2)
        {
            printf("AI is not available at the moment... Please choose again.\n");
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

void checkWinner()
{
    // Check Horizentally
    for (int i = 0; i < 3; i++)
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][2] != ' ')
        {
            if (grid[i][0] == 'X')
                winner = 1;
            else
                winner = 2;
            return;
        }

    // Check Vertically
    for (int j = 0; j < 3; j++)
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j] && grid[2][j] != ' ')
        {
            if (grid[0][j] == 'X')
                winner = 1;
            else
                winner = 2;
            return;
        }

    // Check Diagonally
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[1][1] != ' ')
    {
        if (grid[1][1] == 'X')
            winner = 1;
        else
            winner = 2;
        return;
    }
    if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[1][1] != ' ')
    {
        if (grid[1][1] == 'X')
            winner = 1;
        else
            winner = 2;
        return;
    }

    // Check For Tie
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
                count++;
    if (count == 0)
        winner = 3;
    return;
}
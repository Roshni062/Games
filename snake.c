#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[200], tailY[200];
int nTail;
int speed = 120; // lower = faster

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

// Move cursor without flicker
void gotoxy(int x, int y)
{
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


// Hide blinking cursor
void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void Setup()
{
    hideCursor();
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    score = 0;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void Draw()
{
    gotoxy(0, 0);

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Middle
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("#"); // Left border
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == y && j == x)
            {
                printf("\x1b[92mO\x1b[0m"); // Green Snake Head
            }
            else if (i == fruitY && j == fruitX)
            {
                printf("\x1b[91mF\x1b[0m"); // Red Fruit
            }
            else
            {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("\x1b[93mo\x1b[0m"); // Yellow tail
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }
        }
        printf("#\n"); // Right border
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\nScore: %d", score);
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;

        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;

        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;

        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;

        case 'x':
        case 'X':
            gameOver = 1;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // Wall collision (GAME OVER)
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    // Tail collision
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    // Fruit collision
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nTail++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;

        // Increase speed slightly
        if (speed > 40)
            speed -= 5;
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }

    gotoxy(0, HEIGHT + 3);
    printf("\nGAME OVER! Final Score: %d\n", score);
    return 0;
}

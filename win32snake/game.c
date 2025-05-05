#include "game.h"

void InitGame(HWND hWnd)
{
    unsigned seed = (unsigned)time(NULL);

    srand(seed);

    game = FALSE;

    GenerateSnake();

    GenerateSnakeFood();

    InvalidateRect(hWnd, NULL, TRUE);
}

void StartGame(HWND hWnd)
{
    SetTimer(hWnd, TIMER_ID, TIMER_INTERVAL, NULL);

    game = TRUE;
}

void GameOver(HWND hWnd)
{
    KillTimer(hWnd, TIMER_ID);

    game = FALSE;

    GenerateSnake();

    GenerateSnakeFood();

    InvalidateRect(hWnd, NULL, TRUE);
}



void HandleInput(HWND hWnd, WPARAM wParam)
{
    switch (wParam)
    {
    case VK_UP:
    case 'W':
    case 'w':
        if (snakeDirection.y != 1)
        {
            snakeDirection = (POINT){
                .x = 0,
                .y = -1,
            };
        }

        if (!game)
        {
            StartGame(hWnd);
        }

        break;

    case VK_DOWN:
    case 'S':
    case 's':
        if (snakeDirection.y != -1)
        {
            snakeDirection = (POINT){
                .x = 0,
                .y = 1,
            };
        }

        if (!game)
        {
            StartGame(hWnd);
        }

        break;

    case VK_LEFT:
    case 'A':
    case 'a':
        if (snakeDirection.x != 1)
        {
            snakeDirection = (POINT){
                .x = -1,
                .y = 0,
            };
        }

        if (!game)
        {
            StartGame(hWnd);
        }

        break;

    case VK_RIGHT:
    case 'D':
    case 'd':
        if (snakeDirection.x != -1)
        {
            snakeDirection = (POINT){
                .x = 1,
                .y = 0,
            };
        }

        if (!game)
        {
            StartGame(hWnd);
        }

        break;

    default:
        break;
    }
}



void GenerateSnake()
{
    snake[0] = (POINT){
        .x = COLS_COUNT / 2,
        .y = ROWS_COUNT / 2,
    };

    snakeLength = 1;
}

void GenerateSnakeFood()
{
    BOOL check = TRUE;

    do
    {
        check = TRUE;

        snakeFood = (POINT){
            .x = rand() % COLS_COUNT,
            .y = rand() % ROWS_COUNT,
        };

        for (int i = 0; i < snakeLength; i++)
        {
            if (snake[i].x == snakeFood.x && snake[i].y == snakeFood.y)
            {
                check = FALSE;
            }
        }
    } while (!check);
}



void DrawField(HDC hDC)
{
    for (int y = 0; y < ROWS_COUNT; y++)
    {
        for (int x = 0; x < COLS_COUNT; x++)
        {
            RECT lprc = {
                x * CELL_WIDTH,
                y * CELL_HEIGHT,
                (x + 1) * CELL_WIDTH,
                (y + 1) * CELL_HEIGHT,
            };

            HBRUSH hbr;

            if (y % 2 == 0)
            {
                if (x % 2 == 0)
                {
                    hbr = CreateSolidBrush(RGB(125, 250, 0));
                }
                else
                {
                    hbr = CreateSolidBrush(RGB(175, 255, 45));
                }
            }
            else
            {
                if (x % 2 == 0)
                {
                    hbr = CreateSolidBrush(RGB(175, 255, 45));
                }
                else
                {
                    hbr = CreateSolidBrush(RGB(125, 250, 0));
                }
            }

            FillRect(hDC, &lprc, hbr);

            DeleteObject(hbr);
        }
    }
}

void DrawSnake(HDC hDC)
{
    for (int i = 0; i < snakeLength; i++)
    {
        RECT lprc = {
            snake[i].x * CELL_WIDTH,
            snake[i].y * CELL_HEIGHT,
            (snake[i].x + 1) * CELL_WIDTH,
            (snake[i].y + 1) * CELL_HEIGHT,
        };

        HBRUSH hbr;

        if (i % 2 == 0)
        {
            hbr = CreateSolidBrush(RGB(0, 0, 128));
        }
        else
        {
            hbr = CreateSolidBrush(RGB(0, 0, 255));
        }

        FillRect(hDC, &lprc, hbr);

        DeleteObject(hbr);
    }
}

void DrawSnakeFood(HDC hDC)
{
    RECT lprc = {
        snakeFood.x * CELL_WIDTH,
        snakeFood.y * CELL_HEIGHT,
        (snakeFood.x + 1) * CELL_WIDTH,
        (snakeFood.y + 1) * CELL_HEIGHT,
    };

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));

    FillRect(hDC, &lprc, hbr);

    DeleteObject(hbr);
}



BOOL MoveSnake()
{
    POINT snakeHead = snake[0];

    POINT newSnakeHead = (POINT){
        .x = snakeHead.x + snakeDirection.x,
        .y = snakeHead.y + snakeDirection.y,
    };

    if (newSnakeHead.x < 0)
    {
        newSnakeHead.x = COLS_COUNT - 1;
    }

    if (newSnakeHead.y < 0)
    {
        newSnakeHead.y = ROWS_COUNT - 1;
    }

    if (newSnakeHead.x > COLS_COUNT - 1)
    {
        newSnakeHead.x = 0;
    }

    if (newSnakeHead.y > ROWS_COUNT - 1)
    {
        newSnakeHead.y = 0;
    }

    for (int i = 1; i < snakeLength; i++)
    {
        if (snake[i].x == newSnakeHead.x && snake[i].y == newSnakeHead.y)
        {
            return FALSE;
        }
    }

    POINT snakeTail = snake[snakeLength - 1];

    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    snake[0] = newSnakeHead;

    if (newSnakeHead.x == snakeFood.x && newSnakeHead.y == snakeFood.y)
    {
        snake[snakeLength++] = snakeTail;

        GenerateSnakeFood();
    }

    return TRUE;
}

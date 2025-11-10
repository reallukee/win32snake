#ifndef GAME_H
#define GAME_H

#include "header.h"

#define TIMER_INTERVAL      100

#define CELL_WIDTH          25
#define CELL_HEIGHT         25
#define COLS_COUNT          21
#define ROWS_COUNT          21
#define CANVAS_WIDTH        CELL_WIDTH * COLS_COUNT
#define CANVAS_HEIGHT       CELL_HEIGHT * ROWS_COUNT

#define SNAKE_MAX_LENGTH    COLS_COUNT * ROWS_COUNT

#define TOROIDAL_FIELD      TRUE

static BOOL game;

POINT* snake;
size_t snakeCapacity;
size_t snakeLength;
POINT snakeDirection;
POINT snakeFood;

void TimerProc(
    HWND hwnd,
    UINT uMsg,
    UINT_PTR idEvent,
    DWORD dwTime);

void InitGame(HWND hWnd);
void StartGame(HWND hWnd);
void GameOver(HWND hWnd);

void HandleInput(
    HWND hWnd,
    WPARAM wParam);

void GenerateSnake();
void GenerateSnakeFood();

void DrawField(HDC hDC);
void DrawSnake(HDC hDC);
void DrawSnakeFood(HDC hDC);

BOOL MoveSnake();

#endif // !GAME_H

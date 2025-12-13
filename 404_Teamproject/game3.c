#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "game3.h"
#include "badending.h"

#define WIDTH 30
#define HEIGHT 20
#define LASER_COUNT 5
#define GOAL_TIME 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void startScreen() {
    system("cls");
    hideCursor();

    int midX = WIDTH / 2 - 7;
    int midY = HEIGHT / 2 - 2;

    gotoxy(midX, midY);
    printf("=== 레이저 피하기 GAME ===");

    gotoxy(midX + 2, midY + 2);
    printf("START (Press Enter)");

    // Enter 키 입력 대기
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 13) break; // Enter
        }
    }
}

void start_game() {
    srand((unsigned)time(NULL));

    startScreen();

    int playerX = WIDTH / 2;
    int playerY = HEIGHT - 2;

    int laserX[LASER_COUNT];
    int laserY[LASER_COUNT];

    for (int i = 0; i < LASER_COUNT; i++) {
        laserX[i] = rand() % WIDTH;
        laserY[i] = rand() % HEIGHT - HEIGHT;
    }

    int gameOver = 0;

    system("cls");
    hideCursor();

    DWORD startTime = GetTickCount();

    while (!gameOver) {
        DWORD now = GetTickCount();
        int elapsed = (now - startTime) / 1000;
        if (elapsed >= GOAL_TIME) {
            gameOver = 2; // 성공
        }

        // --- 키 입력 ---
        if (_kbhit()) {
            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 75 && playerX > 0) playerX--;
                if (key == 77 && playerX < WIDTH - 1) playerX++;
            }
            if (key == 27) break; // ESC
        }

        // --- 레이저 이동 ---
        for (int i = 0; i < LASER_COUNT; i++) {
            laserY[i]++;
            if (laserY[i] >= HEIGHT) {
                laserY[i] = 0;
                laserX[i] = rand() % WIDTH;
            }
            if (laserX[i] == playerX && laserY[i] == playerY) {
                gameOver = 1;
            }
        }

        // --- 화면 출력 ---
        system("cls");

        gotoxy(0, 0);
        printf("Time: %d / %d s", elapsed, GOAL_TIME);

        for (int i = 0; i < LASER_COUNT; i++) {
            gotoxy(laserX[i], laserY[i]);
            printf("|");
        }

        gotoxy(playerX, playerY);
        printf("@");

        gotoxy(0, HEIGHT - 1);
        for (int i = 0; i < WIDTH; i++) printf("-");

        Sleep(30);
    }

    system("cls");

    if (gameOver == 2) {
        printf("\n\n   Success!! \n\n");
    }
    else {
    badending();
    return;
    }

    system("pause");
    return 0;
}

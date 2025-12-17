#include "game5.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "badending.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

/* ---------- 입력 처리 ---------- */
int timed_input(char* ch, double seconds) {
#ifdef _WIN32
    double start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < seconds) {
        if (_kbhit()) {
            *ch = _getch();
            return 1;
        }
        Sleep(10);
    }
    return 0;
#else
    struct termios oldt, newt;
    struct timeval tv;
    fd_set readfds;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    tv.tv_sec = (int)seconds;
    tv.tv_usec = (seconds - tv.tv_sec) * 1000000;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
    if (result > 0) {
        read(STDIN_FILENO, ch, 1);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 1;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
#endif
}

void clear_input_buffer(void) {
#ifdef _WIN32
    while (_kbhit()) _getch();
#else
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

/* ---------- 애니메이션 ---------- */
void attack_animation(int direction) {
    if (direction == 0) {
        printf("\n경비원이 왼쪽에서 공격한다!\n");
        printf("   (    )\n");
        printf("  (   )\n");
        printf(" (  )   \n");
    }
    else {
        printf("\n경비원이 오른쪽에서 공격한다!\n");
        printf("   (  )\n");
        printf("    (   )\n");
        printf("     (    )\n");
    }

#ifdef _WIN32
    Sleep(500);
#else
    usleep(500000);
#endif
}

void dodge_animation(int direction) {
    if (direction == 0)
        printf("↩왼쪽으로 회피했다!\n\n");
    else
        printf("↪오른쪽으로 회피했다!\n\n");

#ifdef _WIN32
    Sleep(700);
#else
    usleep(700000);
#endif
}

/* ---------- 게임 로직 ---------- */
void show_intro(void) {
    printf("=== 피하기 게임! ===\n");
    printf("경비원이 다가온다!\n");
    printf("2초 안에 L(왼쪽) 또는 R(오른쪽)을 눌러 회피하라!\n");
    printf("두 번 맞으면 패배한다!\n\n");

#ifdef _WIN32
    Sleep(1500);
    system("cls");
#else
    usleep(1500000);
    system("clear");
#endif
}

int play_round(int round, int* hits, int* success) {
    char playerInput;
    char correctKey;
    int direction = rand() % 2;

    correctKey = (direction == 0) ? 'L' : 'R';

    printf("%d번째 공격!\n", round);
    attack_animation(direction);
    printf("빠르게 눌러! (L/R): ");

    int inputReceived = timed_input(&playerInput, 2.0);

    if (!inputReceived) {
        printf("\n너무 느리다! 맞았다!\n\n");
        (*hits)++;
    }
    else {
        playerInput = toupper(playerInput);
        if (playerInput == correctKey) {
            printf("\n회피 성공!\n");
            dodge_animation(direction);
            (*success)++;
        }
        else {
            printf("\n잘못된 방향! 맞았다!\n\n");
            (*hits)++;
        }
    }

#ifdef _WIN32
    Sleep(1500);
    system("cls");
#else
    usleep(1500000);
    system("clear");
#endif

    clear_input_buffer();
    return (*hits < 2);
}

void show_result(int success, int totalRounds) {
    printf("=== 결과 ===\n");
    printf("성공한 회피: %d / %d\n", success, totalRounds);

    if (success >= 4) {
        printf("대부분의 공격을 피했다! 탈출 성공!\n");
        Sleep(1500);
        system("cls");
        return;
    }
    else {
        printf("회피에 실패했다... 경비원에게 붙잡혔다.\n");
        Sleep(1500);
        system("cls");
        badending();
        return;
    }
}

/* ---------- 외부 호출 함수 ---------- */
void start_dodge_game(void) {
    srand((unsigned int)time(NULL));
    system("cls");
    int success = 0;
    int hits = 0;
    const int totalRounds = 6;

    show_intro();

    for (int i = 1; i <= totalRounds; i++) {
        if (!play_round(i, &hits, &success)) {
            printf("두 번 맞았다... 쓰러졌다.\n");
            printf("경비원이 너를 제압했다.\n");
            Sleep(1500);
            system("cls");
            badending();
            return;
        }
    }

    show_result(success, totalRounds);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game2.h"

void Guess_number() {
    int answer, guess;

    // 시작 화면
    printf("=== 숫자 맞추기 GAME ===\n");
    printf("> START (엔터를 누르세요)\n");

    // 엔터 입력 대기
    getchar(); // 한 번만 엔터를 누르면 진행

    // 난수 생성
    srand(time(NULL));
    answer = rand() % 21; // 0~20 범위 난수

    printf("0~20 범위의 정수를 입력하세요.\n");

    while (1) {
        printf("입력: ");
        scanf("%d", &guess);

        if (guess == answer) {
            printf("Success!!\n");
            break;
        }
        else if (guess < answer) {
            printf("더 큰 숫자입니다.\n");
        }
        else {
            printf("더 작은 숫자입니다.\n");
        }
    }
}

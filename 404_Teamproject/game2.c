#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include"game2.h"
#include "badending.h"

void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Sequence Memory Game");
}

void number_Game() {
    SetConsoleView();
    int* pNums;

    while (1) {
        int n;
        int num;
        int ok;
        int i;

        srand((unsigned)time(NULL));

        // 숫자 개수 입력
        printf("몇 개의 숫자 : ");
        scanf_s("%d", &n);

        // 메모리 할당
        pNums = (int*)malloc(sizeof(int) * n);

        // 1~100 난수들을 입력받음
        for (i = 0; i < n; ++i)
            pNums[i] = rand() % 100 + 1;

        // 숫자들을 보여 준다
        for (i = 0; i < n; ++i)
        {
            printf("\r%d", pNums[i]);
            Sleep(1000);
            printf("\r     ");
        }

        printf("\n\n");

        // 숫자 확인
        printf("숫자들을 순서대로 입력\n");

        ok = 1;
        for (i = 0; i < n; ++i)
        {
            scanf_s("%d", &num);
            if (num != pNums[i])
                ok = 0;
        }

        if (!ok){
             badending();
             return;
        }
        else {
            printf("맞았습니다.\n");
            break;
        }

    }
    // 메모리 해제
    free(pNums);
}

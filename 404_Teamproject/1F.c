#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include"4F.h"
#include"3F.h"
#include"2F.h"
#include"1F.h"
#include"story.h"
#include "keys.h"
#include "save.h"




void event1F();
//void slowPrintChar(const char* text, int delay) {
//    while (*text) {
//        // 키 눌렀는지 체크
//        if (_kbhit()) {
//            _getch(); // 눌린 키 입력 제거
//
//            // 남은 텍스트 한 번에 출력
//            printf("%s", text);
//            fflush(stdout);
//            return;
//        }
//
//        putchar(*text);
//        fflush(stdout);
//        Sleep(delay);
//        text++;
//    }
//}

//void scene(const char* text) {
//    slowPrintChar(text, 28);
//
//    printf("\n\n[Enter 입력]");
//
//    while (1) {
//        int key = _getch();
//        if (key == '\r') break;
//    }
//
//    system("cls");
//}

//void fileprint(char* f) {  //텍스트 화면 출력하는 함수
//    FILE* p = fopen(f, "r");
//    if (!p)return;
//    char line[500];
//    while (fgets(line, sizeof(line), p))printf("%s", line);
//    fclose(p);
//}

void choice1F() { // 1층
    saveData.checkpoint = 1;
    saveGame();
    if (!alarmOff) {
        event1F();   // 보안 켜져 있을 때만 실행
    }
    while (1) {
        system("cls");
        fileprint("floor1.txt");
        printf("\n[L: 왼쪽(열쇠방) | U: 위층 | G: 현관문 | I: 인벤토리 | ESC: 종료]\n");

        int s = _getch();

        if (s == 'L' || s == 'l') {
            system("cls");
            keyroom();
        }

        else if (s == 'i' || s == 'I') {
            system("cls");
            showInventory();
            system("cls");
            fileprint("floor1.txt");
            printf("\n[L: 왼쪽(열쇠방) | U: 위층 | G: 현관문 | I: 인벤토리 | ESC: 종료]\n");
        }

        else if (s == 'G' || s == 'g') {
            system("cls");
            door();
        }
        else if (s == 'U' || s == 'u') {
            system("cls");
            slowPrintChar("위층으로 올라갑니다...\n", 20);
            printf("\n[Enter 키를 누르세요]");
            while (_getch() != '\r');
            system("cls");
            choice2F();
        }
        else if (s == 27) {
            system("cls");
            menu();
            break;
        }
        else continue;
    }
}

void door() {  //1층 현관문
    fileprint("door.txt");

    while (1) {
        int s = _getch();

        if (s == '1' && hasItem("열쇠")) {
            happyending();
        }
        else if (s == 27) return;
        else if (s == 'i' || s == 'I') {
            system("cls");
            showInventory();
            system("cls");
            fileprint("door.txt");
        }
        else {
            slowPrintChar("\n열쇠가 필요합니다.\n", 20);
            Sleep(1500);
            system("cls");
            fileprint("door.txt");
        }
    }
}

void happyending() { // 해피엔딩
    system("cls");
    scene("최종훈은 건물로부터 탈출하는 데 성공했다.");
    system("cls");
    fileprint("happyending1.txt");
    Sleep(1500);
    system("cls");
    scene("최종훈의 눈앞에는 숲길이 펼쳐져 있었다.\n"
        "그는 이틀동안 쉬지 않고 걸었고,\n"
        "기적처럼 지나가던 차량의 도움을 받았다.\n");
    system("cls");
    scene("최종훈은 깨달았다.\n"
        "세상에 아무조건 없이 많은 보수를 주는 일은 없으며, \n"
        "단번에 큰 성공을 얻으려는 욕심은 오히려 위험을 불러온다는 사실을.");
    system("cls");
    scene("그는 현실적인 조건의 IT 회사에 취업했다.\n"
        "작은 회사였지만, 성실하게 일하며 경력을 쌓아갔다.\n");
    fileprint("happyending2.txt");
    Sleep(1500);
    system("cls");
    scene("--HAPPY END--");
    system("cls");
    menu();

}
void event1F() { //1층
    if (alarmOff)return;
    int trigger = rand() % 100;
    if (trigger >= 50) return;

    system("cls");
    printf("조직원의 발소리가 들린다...\n");
    printf("어떻게 할까?\n\n");
    printf("1. 담요를 이용해 몸을 숨긴다.\n");
    printf("2. 조직원과 맞서 싸운다.\n");

    DWORD start = GetTickCount();

    while (1) {
        if (GetTickCount() - start > 2000) {
            printf("\n시간 초과! 조직원이 발견했다!\n");
            Sleep(1000);
            chooseMiniGame();
            return;
        }

        if (_kbhit()) {
            char c = _getch();

            //  1번 선택
            if (c == '1') {
                if (hasItem("담요")) {
                    printf("\n담요를 덮고 몸을 숨겼다...\n");
                    Sleep(1000);
                    printf("조직원이 그냥 지나갔다.\n");
                    printf("\n[아무 키나 누르세요]");
                    _getch();
                    system("cls");
                    fileprint("floor1.txt");
                    printf("\n[L: 왼쪽(열쇠방) | U: 위층 | G: 현관문 | I: 인벤토리 | ESC: 종료]\n");
                    return;
                }
                else {
                    printf("\n담요가 없다!\n");
                    Sleep(800);
                    chooseMiniGame();
                    return;
                }
            }

            //  2번 선택
            else if (c == '2') {
                system("cls");
                printf("망치를 사용할까?\n\n");
                printf("1. 사용한다.\n");
                printf("2. 무서워...사용하지 않는다.\n");

                char s = _getch();

                if (s == '1' && hasItem("망치")) {
                    printf("\n망치로 조직원을 제압했다!\n");
                    Sleep(1000);
                    printf("조용히 지나갈 수 있었다.\n");
                    printf("\n[아무 키나 누르세요]");
                    _getch();

                    system("cls");
                    fileprint("rightroom.txt");
                    return;
                }


                printf("\n조직원과 마주쳤다!\n");
                Sleep(1000);
                chooseMiniGame();
                return;
            }
        }
    }
}
void keyroom() {
    fileprint("keyroom.txt");
    while (1) {
        int s = _getch();

        if (s == '1') {       // 열쇠 얻기
            if (!hasItem("열쇠")) {
                addItem("열쇠");
                slowPrintChar("열쇠를 획득했습니다.\n", 20);
            }
            else {
                slowPrintChar("이미 소유한 아이템입니다.\n", 20);
            }
            Sleep(1000);
            system("cls");
            fileprint("keyroom.txt");

        }
        else if (s == 'i' || s == 'I') {
            system("cls");
            showInventory();
            system("cls");
            fileprint("keyroom.txt");

        }
        else if (s == 27) return;
    }
}
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h> 
#include"4F.h"
#include"3F.h"
#include"2F.h"
#include"1F.h"
#include "keys.h"
#include "save.h"
#include "story.h"


void slowPrintChar(const char* text, int delay) {
    while (*text) {
        // 키 눌렀는지 체크
        if (_kbhit()) {
            _getch(); // 눌린 키 입력 제거

            // 남은 텍스트 한 번에 출력
            printf("%s", text);
            fflush(stdout);
            return;
        }

        putchar(*text);
        fflush(stdout);
        Sleep(delay);
        text++;
    }
}
void scene(const char* text) {
    slowPrintChar(text, 28);

    printf("\n\n[Enter 입력]");

    while (1) {
        int key = _getch();
        if (key == '\r') break;
    }

    system("cls");
}

void fileprint(char* f) {  //텍스트 화면 출력하는 함수
    FILE* p = fopen(f, "r");
    if (!p)return;
    char line[500];
    while (fgets(line, sizeof(line), p))printf("%s", line);
    fclose(p);
}

void chooseMiniGame() {//미니게임 3개 중 랜덤출제
    int r = rand() % 3;  // 0,1,2 중 하나

    switch (r) {
    case 0: start_game(); break;//위에서 떨어지는 거 피하기
    case 1: number_Game(); break;//게임2
    case 2: startGame(); break;//공룡게임
    }
}

void event2F1() { // 2층 복도
    int trigger = rand() % 100;
    if (trigger >= 98) return;

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

            // 1번 선택
            if (c == '1') {
                if (hasItem("담요")) {
                    printf("\n담요를 덮고 몸을 숨겼다...\n");
                    Sleep(1000);
                    printf("조직원이 그냥 지나갔다.\n");
                    printf("\n[아무 키나 누르세요]");
                    _getch();
                    system("cls");
                    fileprint("floor2.txt");
                    return;
                }
                else {
                    printf("\n담요가 없다!\n");
                    Sleep(800);
                    chooseMiniGame();
                    return;
                }
            }

            // 2번 선택
            else if (c == '2') {
                printf("\n조직원과 마주쳤다!\n");
                Sleep(1000);
                chooseMiniGame();
                return;
            }
        }
    }
}


void event2F2() { // 조직원 방
    int trigger = rand() % 100;
    if (trigger >= 98) return;

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
                    fileprint("floor2.txt");
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
                printf("\n조직원과 마주쳤다!\n");
                Sleep(1000);
                chooseMiniGame();
                return;
            }
        }
    }
}


void event2F3() { // 보안실
    int trigger = rand() % 100;
    if (trigger >= 98) return;

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
                    fileprint("floor2.txt");
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
                printf("\n조직원과 마주쳤다!\n");
                Sleep(1000);
                chooseMiniGame();
                return;
            }
        }
    }
}


void choice2F() { //2층에서 방 선택하기
    saveData.checkpoint = 2;
    saveGame();
    system("cls");
    fileprint("floor2.txt");


    while (1) {
        if (!alarmOff) {
            event2F1();
        }
        int s = _getch();
        
        if (s == 'L' || s == 'l') {
            system("cls");
            leftroom2F();
            system("cls");
            fileprint("floor2.txt");
        }

        else if (s == 'i' || s == 'I') {
            system("cls");
            showInventory();
            system("cls");
            fileprint("floor2.txt");
        }

        else if (s == 'R' || s == 'r') {
            system("cls");
            rightroom2F();
            system("cls");
            fileprint("floor2.txt");
        }
        else if (s == 'U' || s == 'u') {
            system("cls");
            floor3();
        }
        else if (s == 'D' || s == 'd') {
            system("cls");
            slowPrintChar("아래층으로 내려갑니다...\n", 20);
            printf("\n[Enter 키를 누르세요]");
            while (_getch() != '\r');

            system("cls");
            choice1F();
        }
        else if (s == 27) {
            system("cls");
            menu();
            break;
        }
        else continue;
    }
}

void leftroom2F() {//조직방
    if (!alarmOff) {
        event2F2();
    }
    system("cls");
    fileprint("leftroom.txt");
    scene(
        "\n여기가 그 일기에 적힌 조직원 휴게소야...\n"
        "일기에 적힌대로라면, 이 방 안에 시설 내 주요 구역\n"
        "비밀번호가 적힌 자료가 분명 있을거야...\n"
        "보안실의 비밀번호를 알기위해서는 그 자료가 꼭 필요해...\n"
    );
    fileprint("leftroom.txt");
    printf("\n");
    while (1) {
        int s = _getch();
        switch (s) {
        case'1':system("cls");fileprint("data1_left.txt");//자료 1
            scene("\n...뒷자리가 찢어져있네\n"
                "나머지 조각이 방 어딘가에 남아있을거야...\n"
                "잘 찾아봐야겠어");
            fileprint("data1_left.txt");
            while (_getch() != 27);
            system("cls");fileprint("leftroom.txt");break;
        case'2':system("cls");fileprint("data4_left.txt");//자료 2
            while (_getch() != 27);
            system("cls");fileprint("leftroom.txt");break;
        case 27:return;//esc누르면 자료보기 종료
        }
    }
}



void rightroom2F() {//보안실
    if (!alarmOff) {
        event2F3();
    }
    system("cls");
    fileprint("password.txt");
    printf("\n");
    char input[10];
    int i = 0;
    printf("비밀번호를 입력하세요 : ");
    while (1) {
        int s = _getch();
        if (s == 27) {
            system("cls");
            choice2F();     // 2층 선택 화면으로 복귀
            return;
        }
        if (s == '\r') { //엔터 입력 시 종료
            input[i] = '\0';
            break;
        }
        if (s == 8) { // 비밀번호 지우기
            if (i > 0) {
                i--;
                input[i] = '\0';
                printf("\r비밀번호를 입력하세요 : ");
                for (int k = 0;k < i;k++)putchar('*');

                putchar(' ');
                printf("\r비밀번호를 입력하세요 : ");
                for (int k = 0;k < i;k++)putchar('*');

                fflush(stdout);
            }
            continue;
        }
        if (s >= '0' && s <= '9' && i < 9) {
            putchar('*');
            input[i++] = s;
            fflush(stdout);
        }

    }
    int password = atoi(input);
    system("cls");
    if (password != 2115) { //비밀번호 일치하는지 확인
        printf("비밀번호가 일치하지 않습니다.");
        Sleep(1500);
        return;
    }
    fileprint("password.txt");
    printf("문이 열립니다.");
    Sleep(1000);
    system("cls");
    fileprint("rightroom.txt");
    Sleep(2000);
    system("cls");
    scene(
        "\n이렇게 철통같은 보안 시스템이라니...\n"
        "지금까지 단 한 사람도 탈출하지 못했다는 데에는 이유가 있었군...\n"
        "일기 내용에 따르면 이곳에서 경보 시스템을 해제할 수 있다고 한다...\n"
        "저 복잡한 장치들 중 하나가 경보를 끌 수 있는 조작장치일거야.\n"
        "지체할 시간이 없어. 빨리 찾아야 해...");
    system("cls");
    fileprint("rightroom.txt");
    printf("\n");
    while (1) {
        int s = _getch();
        if (s == '1') {
            system("cls");
            Guess_number();
            system("cls");
            printf("보안시스템 OFF");
            alarmOff = 1;
            Sleep(1500);
            system("cls");
            fileprint("rightroom.txt");
        }
        else if (s == 27)return;
    }
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include"4F.h"
#include"3F.h"
#include"2F.h"
#include"1F.h"
#define MAX_ITEMS 10
#include "keys.h"
#include "save.h"
#include"story.h"



char inventory[MAX_ITEMS][50];
int itemCount = 0;

void addItem(const char* item) {
    if (saveData.itemCount >= MAX_ITEMS) return;

    strcpy(saveData.inventory[saveData.itemCount], item);
    saveData.itemCount++;

    saveGame(); // 아이템 얻자마자 저장 (선택)
}

int hasItem(const char* item) {
    for (int i = 0; i < saveData.itemCount; i++) {
        if (strcmp(saveData.inventory[i], item) == 0)
            return 1;
    }
    return 0;
}

void showInventory() {
    system("cls");
    printf("==== 인벤토리 ====\n\n");

    if (saveData.itemCount == 0) {
        printf("인벤토리가 비어 있습니다.\n");
    }
    else {
        for (int i = 0; i < saveData.itemCount; i++) {
            printf("%d) %s\n", i + 1, saveData.inventory[i]);
        }
    }

    printf("\n[ESC 키를 누르면 돌아갑니다]");
    while (_getch() != 27);
}


//void slowPrintChar(const char* text, int delay) {
//    while (*text) {
//        if (_kbhit()) {
//            _getch();
//            printf("%s", text);
//            fflush(stdout);
//            return;
//        }
//        putchar(*text);
//        fflush(stdout);
//        Sleep(delay);
//        text++;
//    }
//}

//void scene(const char* text) {
//    slowPrintChar(text, 28);
//    printf("\n\n[Enter 키를 누르면 다음 장면으로 넘어갑니다]");
//    while (_getch() != '\r');
//    system("cls");
//}

void showAsciiArtFull(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("%s 파일을 찾을 수 없습니다!\n", filename);
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}
/* ========== 수정된 floor3() ========== */
/*  - 매 루프 시작 시 31.txt를 다시 그리도록 함
    - 서브룸에서 돌아오면 화면이 갱신되어 항상 3층 복도로 복귀된 것처럼 보임 */
void floor3() {
    while (1) {
        saveData.checkpoint = 3;
        saveGame();
        system("cls");
        showAsciiArtFull("31.txt");
        printf("\n[L: 왼쪽(행정실) | R: 오른쪽(빈 방) | D: 아래층 | I: 인벤토리 | ESC: 종료]\n");

        int key = _getch();


        if (key == 'l' || key == 'L') {
            floor3_left();
            continue;
        }
        else if (key == 'r' || key == 'R') {
            floor3_right();
            continue;
        }
        else if (key=='i'||key=='I') {
            system("cls");
            showInventory();
            system("cls");
            fileprint("31.txt");
        }
        else if (key == 'u' || key == 'U') {
            system("cls");
            slowPrintChar("위층으로 올라갑니다...\n", 20);
            printf("\n[Enter 키를 누르세요]");
            while (_getch() != '\r');

            system("cls");
            corridor();
            continue;
        }
        else if (key == 'd' || key == 'D') {
            system("cls");
            slowPrintChar("아래층으로 내려갑니다...\n", 20);
            printf("\n[Enter 키를 누르세요]");
            while (_getch() != '\r');

            system("cls");
            choice2F();   // ⭐ 2층 호출
            continue;     // 돌아오면 다시 3층 화면
        }
        else if (key == 27) {
            system("cls");
            menu();
            break;
        }
    }
}


/* ========== 이하 기존 함수들 (변경 없음) ========== */

void floor3_left() {
    system("cls");
    slowPrintChar("=== 행정실 ===\n\n", 28);
    showAsciiArtFull("32.txt");
    slowPrintChar("\n(방에는 여러대의 컴퓨터와 정돈된 서류뭉치들이 보인다)\n", 28);
    slowPrintChar("\n여긴,, 행정실인가? 다른 독방들이랑은 완전히 다른 분위기인데,,\n", 28);
    slowPrintChar("\n(책상위에 놓인 \"인원 관리 명부\"라는 서류가 눈에 들어온다.)\n", 28);

    printf("\n[Enter 키를 누르세요]");
    while (_getch() != '\r');

    system("cls");
    slowPrintChar("=== 행정실 ===\n\n", 28);
    showAsciiArtFull("32.txt");
    slowPrintChar("\n[ESC: 복도] [R: 서류 확인]\n", 28);

    while (1) {
        int key = _getch();
        if (key == 'R' || key == 'r') {
            system("cls");
            slowPrintChar("=== 행정실 - 서류 확인 ===\n\n", 28);
            slowPrintChar("장현수(22), 보이스피싱 담당, 2023.11.01 폐기 (건강 악화)\n", 20);
            slowPrintChar("전호진(32), 보이스피싱 담당, 업무효율 우수\n", 20);
            slowPrintChar("박지원(25), 보이스피싱 담당, 업무효율 양호\n", 20);
            slowPrintChar("임미선(27), 서버관리 담당, 2024.09.12 폐기 (탈출시도 3회 적발)\n", 20);
            slowPrintChar("최종훈(29), (보이스피싱+서버관리) 담당, 업무효율 저조\n", 20);
            printf("\n[Enter]");
            while (_getch() != '\r');
            system("cls");
            slowPrintChar("...", 20);
            printf("\n[Enter]");
            while (_getch() != '\r');
            system("cls");
            slowPrintChar("마치 사람을 공장부품 다루듯 취급하고 있다...\n", 20);
            slowPrintChar("만약 탈출에 실패한다면 평생을 이곳에서 이들의 노예로 살아가다가\n", 20);
            slowPrintChar("비참한 최후를 맞이하겠지...\n", 20);
            slowPrintChar("반드시 이곳에서 탈출해야 한다..\n", 20);
            printf("\n[Enter 키를 누르면 돌아갑니다]\n");
            while (_getch() != '\r');
            system("cls");
            slowPrintChar("=== 행정실 ===\n\n", 28);
            showAsciiArtFull("32.txt");
            slowPrintChar("\n[ESC: 복도] [R: 서류 확인]\n", 28);
        }
        else if (key == 'i' || key == 'I') {
            showInventory();
            system("cls");
            slowPrintChar("=== 행정실 ===\n\n", 28);
            showAsciiArtFull("32.txt");
            slowPrintChar("\n[ESC: 복도] [R: 서류 확인]\n", 28);
        }
        else if (key == 27) { // ESC
            break;
        }
    }
}

void showDiaryStory() {
    system("cls");
    slowPrintChar("[피해자의 일기 - 1P]\n\n", 28);
    slowPrintChar("감금 1일차…\n", 28);
    slowPrintChar("여기가 어디인지 알 수 없다.\n", 28);
    slowPrintChar("놈들은 면접을 핑계로 나를 불러내더니, 순식간에 태도가 돌변해 나를 제압했다.\n", 28);
    slowPrintChar("그리고 이 좁은 방에 가둬버렸다.\n", 28);
    slowPrintChar("내 소지품은 모두 빼앗겼고, 앞으로 내가 해야 할 일은 보이스피싱이라고 했다.\n", 28);
    slowPrintChar("무슨 일이 어떻게 돌아가는 건지, 도통 감이 잡히지 않는다...\n", 28);
    printf("\n[Enter]");
    while (_getch() != '\r');

    system("cls");
    slowPrintChar("[피해자의 일기 - 2P]\n\n", 28);
    slowPrintChar("이곳에 잡혀온 지 거의 한 달이 지났다...\n", 28);
    slowPrintChar("놈들은 단 하루도 제대로 쉬게 해주지 않고 나를 혹사시킨다.\n", 28);
    slowPrintChar("조금이라도 눈에 거슬리면, 곧바로 폭언과 폭력이 뒤따른다.\n", 28);
    slowPrintChar("난 이 지옥같은 곳에서 어떻게든 탈출하기위해 틈나는 대로 정보를 모으고 있다….\n", 28);
    slowPrintChar("며칠 전, 복도에서 조직원들이 떠드는 걸 들었다.\n", 28);
    slowPrintChar("1층의 열쇠 보관방에는 경보 시스템이 깔려 있어서, 함부로 다가가면 바로 경보가 울린다고 했다.\n", 28);
    slowPrintChar("그리고 그 경보는 2층 보안실에서만 끌 수 있다고….\n", 28);
    slowPrintChar(" 그 말이 사실이라면, 정문 열쇠를 얻기 위해서는 보안실을 먼저 공략해야한다.\n", 28);
    printf("\n[Enter]");
    while (_getch() != '\r');

    system("cls");
    slowPrintChar("[피해자의 일기 - 3P]\n\n", 28);
    slowPrintChar("며칠전, 건물내부청소에 동원되어 2층에 있는 조직원휴게실 내부를 정리하던 중이었다.\n", 28);
    slowPrintChar("바로 뒤에서 조직원이 나의 모든 행동을 날카롭게 지켜보고 있었기에 자세히 보지는 못했지만\n", 28);
    slowPrintChar("책상 한쪽 서류철에서 시설 비밀번호 목록이라는 글자가 스치듯 보였다.\n", 28);
    slowPrintChar("확인할 방법은 없지만,,, 2층의 보안실 비밀번호 단서가 이 방에 있을 가능성은 꽤 높아보인다. \n", 28);
    printf("\n[Enter]");
    while (_getch() != '\r');

    system("cls");
    slowPrintChar("[피해자의 일기 - 4P]\n\n", 28);
    slowPrintChar("요즘들어 몸 상태가 눈에 띄게 나빠지고 있다...\n", 28);
    slowPrintChar("며칠째 기침이 가라앉질 않고, 밤에는 숨이 차서 제대로 잠도 못 잔다.\n", 28);
    slowPrintChar("당연히 이놈들이 제대로된 치료를 해줄리는 없었다.\n", 28);
    slowPrintChar("쉽게 구할 수 있는 감기약 한알조차도 허락되지 않는다...\n", 28);
    slowPrintChar("이상한점은,,, 건강이 악화되어 내가 맡은 업무를 제대로 수행하지 못하는 상황에도 아무런 관심 없이 방치되는 느낌을 받는다.\n", 28);
    slowPrintChar("예전에는 할당량을 조금이라도 못채우면 곧바로 구타가 시작됐는데, , , \n", 28);
    slowPrintChar("이놈들이 내 편의를 봐줄리가 없다는걸 알면서 이렇게 방치당하니 \n", 28);
    slowPrintChar("오히려 더 불안하다...\n", 28);
    printf("\n[Enter]");
    while (_getch() != '\r');

    system("cls");
    slowPrintChar("..... 일기내용은 이게 끝이다.\n\n", 28);
    slowPrintChar("이 피해자는 얼마나 힘들고 공포스러웠을까.... 마음 한켠이 무거워진다.\n\n", 28);
    slowPrintChar("하지만 당장은 이 정보를 활용해서 이곳을 탈출하는게 우선이다...\n\n", 28);
    slowPrintChar("이 정보를 바탕으로 움직여야 해.\n", 28);
    slowPrintChar("2층 휴게실에서 비밀번호 관련 자료를 찾고,\n", 28);
    slowPrintChar("보안실에 들어가 경보 시스템을 해제한 후,\n", 28);
    slowPrintChar("정문 열쇠를 찾아 탈출한다...\n", 28);
    printf("\n[Enter]");
    while (_getch() != '\r');
}

void floor3_right() {
    system("cls");
    slowPrintChar("=== 3층 - 빈 피해자의 방 ===\n\n", 28);
    showAsciiArtFull("33.txt");


    while (1) {
        int key = _getch();
        if (key == 'L' || key == 'l') {
            showDiaryStory();
            system("cls");
            slowPrintChar("=== 3층 - 빈 피해자의 방 ===\n\n", 28);
            showAsciiArtFull("33.txt");

        }
        else if (key == 'R' || key == 'r') {
            system("cls");
            slowPrintChar("=== 기록 ===\n\n", 28);
            showAsciiArtFull("33_1.txt");
            printf("\n[Enter 키를 누르면 돌아갑니다]");
            while (_getch() != '\r');
            system("cls");
            slowPrintChar("=== 3층 - 빈 피해자의 방 ===\n\n", 28);
            showAsciiArtFull("33.txt");

        }
        else if (key == 'i' || key == 'I') {
            showInventory();
            system("cls");
            slowPrintChar("=== 3층 - 빈 피해자의 방 ===\n\n", 28);
            showAsciiArtFull("33.txt");

        }
        else if (key == 27) { // ESC
            break; // 돌아오면 floor3 루프가 화면을 다시 그림
        }
    }
}

void floor2() {
    system("cls");
    slowPrintChar("=== 2층 복도 (임시 화면) ===\n", 20);
    slowPrintChar("아직 구현되지 않았습니다.\n", 20);
    printf("\n[ESC 키를 누르면 돌아갑니다]");
    while (_getch() != 27);
}

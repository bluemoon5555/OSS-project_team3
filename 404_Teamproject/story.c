#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include "story.h"
#include"2F.h"
#include"save.h"

//typedef struct {
//    int checkpoint;
//}SaveData;

//SaveData saveData = { 0 };
int choice;

//void saveGame() {
//    FILE* fp = fopen("save.dat", "wb");
//    if (!fp) return;
//    fwrite(&saveData, sizeof(SaveData), 1, fp);
//    fclose(fp);
//}
//
//int loadSaveData() {
//    FILE* fp = fopen("save.dat", "rb");
//    if (!fp) return 0; // 저장 파일 없음
//    fread(&saveData, sizeof(SaveData), 1, fp);
//    fclose(fp);
//    return 1;
//}

void printMenu();
void startGame();
void loadGame();

void menu() {
    while (1) {
        printMenu();
        printf("\n 숫자를 눌러 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            system("cls"); // 메뉴 화면 지우고 게임 시작
            startStory();
            return;
        case 2:
            loadGame();
            return;
        case 3:
            printf("게임을 종료합니다...\n");
            Sleep(700);
            exit(1);
        default:
            printf("잘못된 입력입니다.\n");
            Sleep(700);
        }
    }
}

// ---------------------- 메뉴 ----------------------
void printMenu() {
    system("cls");
    fileprint("startmenu.txt");
}


// ---------------------- 게임 시작 ----------------------
void startStory() {
    fileprint("howtoplay.txt");
    slowPrintChar("넘어가려면 [Enter]를 입력하세요",18);

    int s = _getch();
    while (1) {
        if (s == '\r') {
            system("cls"); break;
        }
    }
    fileprint("startgame1.txt");
    Sleep(1000);
    system("cls");

    scene(
        "(좁은 원룸, 책상 위에는 노트북과 이력서가 어지럽게 놓여 있다.)\n"
        "(올해로 29살인 최종훈은 00대학교 컴퓨터공학과를 졸업한 뒤 3년째 취업에 실패하고 있다.)\n"
        "최종훈 : ...... 또 떨어졌네.\n"
        "벌써 몇 번째인지도 모르겠는 불합격 통보… 이제는 그냥 무덤덤하다.\n"
    );

    scene(
        "(무기력하게 노트북 화면을 바라보던 최종훈, 갑자기 메일 알람이 울린다.)\n"
        "뭐야... 취업 홍보 메일..? \n"
        "\"월 천만원 보장!!\" \"주 3일 근무!\"...?\n"
        "터무니 없이 파격적인 조건이네...  요즘같은 불경기에 정말 이런 조건으로\n"
        " 사람을 뽑는 회사가 있을까.. ? ?\n "
    );

    scene(
        "(메일 스크롤을 계속해서 내린다.)\n"
        "무경력자 환영...탄력적 근무...임사 시 월급과 별도로 500만원 지급?!\n"
        "조금 의심스럽긴 하지만... \n"
        "이런 파격적인 조건을 제시하는 곳에서\n"
        "제대로 시작해보는게 나을지도..."
    );

    scene(
        "(취업홍보메일을 보낸 회사와 연락하여 면접약속을 잡은 최종훈은 안내받은 장소를 향했다.)\n"
        "(면접 장소로 지정된 외곽의 산업단지. 최종훈이 버스에서 내려 주변을 둘러본다)\n"
        "여기가 맞나? 왜 이렇게 사람이 없지...\n"
    );
    fileprint("blackcar.txt");
    Sleep(1500);
    system("cls");
    scene(
        "(골목 안쪽에서 검은색 벤이 서 있다. 차량 주위에 온몸이 문신으로 뒤덮인 덩치 큰 남자들이 서 있는 모습이 위화감을 준다)\n"
        "(위화감을 느낀 최종훈이었지만 일단은 차량에 탑승해서 면접장소로 향하기로 한다.)\n"
    );

    scene(
        "최종훈 :  저기... 회사가 어디쯤에...\n"
        "(퍽!!!)\n"
        "(최종훈의 말이 끝나기도 전에 둔기가 그의 머리에 강하게 내리꽂혔다.)\n"
        "이게... 무슨......\n"
        "(최종훈은 시야가 점점 흐려지며 의식을 잃게 되었다.)"
    );

    scene("으... 머리가...\n"
        "여긴 어디지? 왜...\n"
        "그래... 차 안에서... 그 사람들이...\n"
        "\n보스 : 잠에서 깬 모양이군.\n");
    scene("최종훈 : 왜... 왜이러시는거에요..\n"

        "보스 : 간단히 말하자면,,, 넌 이제 우리의 식구다. \n"
        "앞으로 우리가 시키는 일만 잘~ 해내면 되는거야.\n"

        "보스 : 만약 반항하거나, 할당받은 업무를 제대로 처리하지못한다면,,,\n"
    );
    scene("좋은꼴은 보지못할거다.");
    scene("....................................");
    scene("나를 납치해온 범죄집단은 체계적인 보이스피싱과 불법도박사이트 운영으로 범죄수익을 창출하는 조직이다.\n"
        "나 이외에도 납치를 당해서\n"
        "강제로 불법적인 업무를 강요당하는 사람들이 여럿 존재하는것 같다.\n"

        "나를 포함한 납치피해자들은 강제노동을 강요당하고, \n"
        "성과를 내지못하면 가혹한 구타 및 가혹행위가 이루어졌다.\n"

        "\n\n이런 생활.... 지긋지긋해......");
    scene("더는... 더는 이렇게 살 수 없어...\n\n"

        "탈출해야 해...\n"
        "무슨 일이 있어도...\n"

    );
}


// ---------------------- LOAD ----------------------
void loadGame() {
    system("cls");

    if (loadSaveData()) {
        slowPrintChar("저장된 데이터를 불러왔습니다.\n", 30);

        if (saveData.checkpoint == 1)
            slowPrintChar(" 저장된 위치: 이야기 시작 이후 구간입니다.\n", 30);

        slowPrintChar("\n곧 이어서 게임이 진행됩니다...\n", 30);
        Sleep(1500);
        system("cls");
        resumeGame();
    }
    else {
        slowPrintChar(" 저장 데이터가 없습니다.\n", 30);
        slowPrintChar("새 게임을 시작해주세요.\n", 30);
        Sleep(1200);
    }
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_ITEMS 10

void room3();
void room3_plus();

char inventory[MAX_ITEMS][50];
int itemCount = 0;

void addItem(const char* item) {
    // 이미 있는 아이템인지 확인
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i], item) == 0) {
            return; // 이미 있으므로 추가 X
        }
    }

    // 새 아이템 추가
    if (itemCount < MAX_ITEMS) {
        strcpy(inventory[itemCount], item);
        itemCount++;
    }
}

int hasItem(const char* item) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i], item) == 0) return 1;
    }
    return 0;
}

void showInventory() {
    system("cls");
    printf("==== 인벤토리 ====\n\n");

    if (itemCount == 0) {
        printf("인벤토리가 비어 있습니다.\n");
    }
    else {
        for (int i = 0; i < itemCount; i++) {
            printf("%d) %s\n", i + 1, inventory[i]);
        }
    }

    printf("\n[ESC 키를 누르면 돌아갑니다]");

    while (_getch() != 27); // ESC
}


void slowPrintChar(const char* text, int delay) {
    while (*text) {
        if (_kbhit()) {
            _getch();
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
    printf("\n\n[Enter 키를 누르면 다음 장면으로 넘어갑니다]");
    while (_getch() != '\r');
    system("cls");
}

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

int room1() {
    system("cls");
    showAsciiArtFull("room1.txt");

    slowPrintChar("\n=== 4층 방 1 ===\n", 28);
    slowPrintChar("문제를 풀어야 복도로 나갈 수 있습니다.\n\n", 28);
    slowPrintChar("[Enter 키를 누르면 문제를 풉니다]", 28);

    // --- Enter 대기 + i(인벤토리) 처리 ---
    while (1) {
        int key = _getch();

        if (key == 'i' || key == 'I') {
            // 인벤토리 열기
            showInventory();

            // 원래 화면 복구
            system("cls");
            showAsciiArtFull("room1.txt");
            printf("\n=== 4층 방 1 ===\n문제를 풀어야 복도로 나갈 수 있습니다.");
            printf("\n\n[Enter 키를 누르면 문제를 풉니다]");
        }
        else if (key == '\r') {
            break;  // Enter → 문제 화면으로 이동
        }
    }

    // --- 문제 시작 화면 ---
    system("cls");
    showAsciiArtFull("room1.txt");
    slowPrintChar("\n=== 4층 방 1 ===\n", 28);

    int ans;

    while (1) {

        slowPrintChar("Q1. 다음 중 C 언어에서 반복문이 아닌 것은?\n"
            "1) for\n2) while\n3) switch\n4) do-while\n정답 입력: ", 20);

        // 입력 버퍼 비우기
        while (_kbhit()) _getch();

        scanf("%d", &ans);

        if (ans == 3) {
            slowPrintChar("\n정답입니다. 복도로 나갑니다.\n", 20);
            printf("\n[Enter 키를 눌러 복도로 이동]\n");
            while (_getch() != '\r');
            system("cls");
            break;
        }

        slowPrintChar("\n틀렸습니다. 다시 시도하세요.\n", 20);
        Sleep(400);

        system("cls");
        showAsciiArtFull("room1.txt");
        slowPrintChar("\n=== 4층 방 1 ===\n다시 문제를 풉니다.\n", 28);
    }
}

void room3() {
    system("cls");
    showAsciiArtFull("room3.txt");

    while (1) {
        int key = _getch();

        if (key == 'i' || key == 'I') {
            showInventory();
            system("cls");
            showAsciiArtFull("room3.txt");
        }
        else if (key == 'R' || key == 'r') {
            room3_plus();
            system("cls");
            showAsciiArtFull("room3.txt");
        }
        else if (key == 'L' || key == 'l') {    // ★ 히든 기능 추가
            system("cls");

            if (hasItem("밧줄")) {   // ‼ 밧줄 체크
                slowPrintChar("밧줄을 이용해 아래층으로 내려갑니다...\n", 20);
                Sleep(400);

                slowPrintChar("하지만 1층은 아직 구현 중입니다.\n", 20);
                slowPrintChar("곧 업데이트될 예정입니다.\n", 20);

                printf("\n[Enter 키를 누르면 돌아갑니다]");
                while (_getch() != '\r');

                system("cls");
                showAsciiArtFull("room3.txt");
            }
            else {
                slowPrintChar("사용할 수 없습니다.\n", 20);
                slowPrintChar("다음에 다시 시도해주세요.\n", 20);

                printf("\n[Enter 키를 누르면 돌아갑니다]");
                while (_getch() != '\r');

                system("cls");
                showAsciiArtFull("room3.txt");
            }
        }
        else if (key == 27) {
            break;
        }
    }
}



void room3_plus() {
    system("cls");
    showAsciiArtFull("room3 plus.txt");

    while (1) {
        int key = _getch();

        if (key == '1') {
            addItem("망치");
            Sleep(200);
        }
        else if (key == '2') {
            addItem("담요");
            Sleep(200);
        }
        else if (key == '3') {
            addItem("밧줄");
            Sleep(200);
        }
        else if (key == 'i' || key == 'I') {
            showInventory();
            system("cls");
            showAsciiArtFull("room3 plus.txt");
        }
        else if (key == 27) {
            break;
        }
    }
}



void corridor() {
    system("cls");
    showAsciiArtFull("room2.txt");

    while (1) {
        int key = _getch();

        if (key == 'i' || key == 'I') {
            showInventory();
            system("cls");
            showAsciiArtFull("room2.txt");
        }

        else if (key == 'L' || key == 'l') {
            system("cls");
            showAsciiArtFull("room1.txt");

            while (1) {
                int subKey = _getch();

                if (subKey == 'i' || subKey == 'I') {
                    showInventory();
                    system("cls");
                    showAsciiArtFull("data.txt");
                }
                else if (subKey == 27) {
                    system("cls");
                    showAsciiArtFull("room2.txt");
                    break;
                }
            }
        }

        else if (key == 'R' || key == 'r') {
            system("cls");
            room3();    // <- 새 방 진입
            system("cls");
            showAsciiArtFull("room2.txt");
        }


        else if (key == 'D' || key == 'd') {
            system("cls");
            slowPrintChar("3층은 아직 구현되지 않았습니다.\n", 20);
            printf("\n[Enter 키를 누르면 종료합니다]\n");
            while (_getch() != '\r');
            break;
        }
    }
}



int main() {
    room1();
    corridor();
    return 0;
}

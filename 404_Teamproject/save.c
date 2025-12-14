#include "save.h"
#include <stdio.h>

// 전역 변수 정의
SaveData saveData = { 0 };

void saveGame() {
    FILE* fp = fopen("save.dat", "wb");
    if (!fp) return;

    fwrite(&saveData, sizeof(SaveData), 1, fp);
    fclose(fp);
}

int loadSaveData() {
    FILE* fp = fopen("save.dat", "rb");
    if (!fp) return 0;

    fread(&saveData, sizeof(SaveData), 1, fp);
    fclose(fp);
    return 1;
}

// LOAD 선택 시 호출
void resumeGame() {
    switch (saveData.checkpoint) {
    case 1:
        choice1F();
        break;
    case 2:
        choice2F();
        break;
    case 3:
        floor3();
        break;
    case 4:
        corridor();   // 또는 room1()
        break;
    default:
        startGame();  // 저장 없으면 새 게임
        break;
    }
}

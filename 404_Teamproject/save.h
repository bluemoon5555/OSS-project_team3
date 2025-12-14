#pragma once

// 저장 데이터 구조체
#define MAX_ITEMS 20

typedef struct {
    int checkpoint;          // 현재 층 (1~4)

    int itemCount;           // 인벤토리 개수
    char inventory[MAX_ITEMS][50]; // 아이템 이름들
} SaveData;

// 전역 저장 데이터
extern SaveData saveData;

// 저장 / 불러오기 함수
void saveGame();
int loadSaveData();
void resumeGame();
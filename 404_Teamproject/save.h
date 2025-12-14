#pragma once

// 저장 데이터 구조체
typedef struct {
    int checkpoint;   // 현재 층 (1~4)
} SaveData;

// 전역 저장 데이터
extern SaveData saveData;

// 저장 / 불러오기 함수
void saveGame();
int loadSaveData();
void resumeGame();

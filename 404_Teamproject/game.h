#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void SetConsoleView();


// 커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y);


// 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown();

// 사람을 그리는 함수
void DrawHuman(int humanY);


// 나무를 그리는 함수
void DrawTree(int treeX);

// 충돌 했을때 게임오버
void DrawGameOver(const int score);


// 충돌했으면 1아니면 0반환
int isCollision(const int treeX, const int humanY);

void startGame();

#endif

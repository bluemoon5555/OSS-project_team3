#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include "game.h"
#include "badending.h"

#define BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define GOAL_SCORE 5

// 콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
}

// 커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

// 사람을 그리는 함수
void DrawHuman(int humanY)
{
	GotoXY(0, humanY);
	// bool 대신 int 사용 (1: true, 0: false)
	static int legFlag = 1;

	printf("       $$$   \n");
	printf("      $$$$$ \n");
	printf("       $$$  \n");
	printf("        $   \n");
	printf("       $$$$$     \n");
	printf("     $ $$$$ $   \n");
	printf("   $   $$$$   $\n");
	printf("       $$$$    \n");
	printf("       $$$    \n");
	printf("      $$  $$    \n");
	printf("      $$  $$     \n");
	if (legFlag)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		legFlag = 0;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = 1;
	}
}

// 나무를 그리는 함수
void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

// 충돌 했을때 게임오버
void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	GotoXY(x, y);
	printf("===========================");
	GotoXY(x, y + 1);
	printf("======G A M E O V E R======");
	GotoXY(x, y + 2);
	printf("===========================");
	/*GotoXY(x, y + 5);
	printf("SCORE : %d", score);*/

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}

// 충돌했으면 1(아니면 0(반환
int isCollision(const int treeX, const int humanY)
{
	//트리의 X가 사람의 몸체쪽에 있을때,
	//사람의 높이가 충분하지 않다면 충돌로 처리
	GotoXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, humanY); //이런식으로 적절한 X, Y를 찾습니다.
	if (treeX <= 8 && treeX >= 4 &&
		humanY > 8)
	{
		return 1; // 충돌 (true)
	}
	return 0; // 비충돌 (false)
}

void startGame() {
	while (1)		//(v2.0) 게임 루프 (1은 true)
	{
		//게임 시작시 초기화
		// bool 대신 int 사용 (0: false, 1: true)
		int isJumping = 0; // false
		int isBottom = 1; // true
		const int gravity = 3;

		int humanY = BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr;	//점수 변수 초기화
		start = clock();		//시작시간 초기화

		while (1)	//한 판에 대한 루프 (1은 true)
		{
			//충돌체크
			if (isCollision(treeX, humanY))
				break;

			//z키가 눌렸고, 바닥(isBottom이 1)일 때 점프
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = 1; // true
				isBottom = 0;  // false
			}

			//점프중(isJumping이 1)이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
			if (isJumping)
			{
				humanY -= gravity;
			}
			else
			{
				humanY += gravity;
			}

			//Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
			if (humanY >= BOTTOM_Y)
			{
				humanY = BOTTOM_Y;
				isBottom = 1; // true
			}

			//나무가 왼쪽으로 (x음수) 가도록하고
			//나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			//점프의 맨위를 찍으면 점프가 끝난 상황.
			if (humanY <= 3)
			{
				isJumping = 0; // false
			}

			DrawHuman(humanY);		//draw dino
			DrawTree(treeX);		//draw Tree

			//(v2.0)
			curr = clock();			//현재시간 받아오기
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)	// 1초가 넘었을때
			{
				score++;	//스코어 UP
				start = clock();	//시작시간 초기화
			}
			Sleep(60);
			system("cls");	//clear

			//(v2.0) 점수출력
			GotoXY(22, 0);
			printf("Score : %d ", score);
			if (score >= GOAL_SCORE) {
				system("cls");
				printf("성공!");
				// 목표 점수 달성하면 다음 상황으로 넘어가기. 못하면 게임오버, 다시 재도전
				Sleep(1000);
				return;
			}
		}

		//
		if (score < GOAL_SCORE) { badending(); return; }   //점수 충족하지 못했으면 배드 엔딩으로 넘어가기
		else break;
	}
}

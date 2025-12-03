#include "game.h"
#include "1F.h"
#include "2F.h"
#include "3F.h"
#include "4F.h"
#include<stdio.h>

int main()
{
	//1층
	choice1F();

	//2층
	system("cls");
	choice2F();
	
	// 4층 관련 시작 함수 호출 제거. 바로 3층 루프 실행.
    floor3();

	//4층
	room1();
    corridor();

	//미니게임 
	SetConsoleView();
	startGame();
	//미니게임

	return 0;
}

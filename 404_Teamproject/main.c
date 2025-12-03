#include "game.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "1F.h"
#include "2F.h"
#include "3F.h"
#include "4F.h"
#include<stdio.h>
#include<windows.h>

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

	//미니게임 1
	SetConsoleView();
	startGame();

	//미니게임2
	number_Game();

	//미니게임3
	

	//미니게임4
	Guess_number();

	return 0;
}

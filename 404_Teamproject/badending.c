#include "game.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "1F.h"
#include "2F.h"
#include "3F.h"
#include "4F.h"
#include "story.h"
#include<stdio.h>
#include<windows.h>
#include<time.h>
void badending() {
	system("cls");
	scene("최종훈은 필사적으로 저항했지만 조직원에게 제압당했다.\n");
	scene("..........................");
	scene("다시 작은 독방에 감금된 그는 하루하루를 무기력하게 보냈다.\n\n\n"
		"그는 더이상 어떤 희망도 가지지 않았다.\n"
		"그저 이 방이 자신의 무덤이 될 것이라는 사실을 체념할 뿐이었다.\n");
	printf("--BAD END--");
	Sleep(3000);
	system("cls");
	menu();
}
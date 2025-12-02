#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
void keyroom();
void choice1F();
void door();
void happyending();
int keyhave=0;//열쇠 소유 여부
void slowPrintChar(const char* text, int delay) {
    while (*text) {
        // 키 눌렀는지 체크
        if (_kbhit()) {
            _getch(); // 눌린 키 입력 제거

            // 남은 텍스트 한 번에 출력
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

    printf("\n\n[Enter 입력]");

    while (1) {
        int key = _getch();
        if (key == '\r') break;  
    }

    system("cls");
}

void fileprint(char *f){  //텍스트 화면 출력하는 함수
    FILE *p=fopen(f,"r");
    if(!p)return;
    char line[500];
    while(fgets(line,sizeof(line),p))printf("%s",line);
    fclose(p);
}

void choice1F() { // 1층
    while(1) {   
        system("cls");
        fileprint("floor1.txt");

        int s = _getch();
        if(s=='L' || s=='l') {
            system("cls");
            keyroom();     
        }
        else if(s=='G' || s=='g') {
            system("cls");
            door();        
        }
        else continue;
    }
}

void door() {  //1층 현관문
    fileprint("door.txt");

    while(1){
        int s = _getch();

        if(s=='1'){
            if(keyhave){
                system("cls");
                happyending();
            } else {
                printf("\n열쇠를 먼저 획득하세요.\n");
            }
        }
        else if(s == 27) return; 
    }
}

void happyending(){ // 해피엔딩
    scene("최종훈은 건물로부터 탈출하는 데 성공했다.");
    system("cls");
    fileprint("happyending1.txt");
    Sleep(1500);
    system("cls");
    scene("최종훈의 눈앞에는 숲길이 펼쳐져 있었다.\n"
        "그는 이틀동안 쉬지 않고 걸었고,\n" 
        "기적처럼 지나가던 차량의 도움을 받았다.\n");
 system("cls");
  scene("최종훈은 깨달았다.\n"
"세상에 아무조건 없이 많은 보수를 주는 일은 없으며, \n"
"단번에 큰 성공을 얻으려는 욕심은 오히려 위험을 불러온다는 사실을.");
system("cls");
  scene("그는 현실적인 조건의 IT 회사에 취업했다.\n"
"작은 회사였지만, 성실하게 일하며 경력을 쌓아갔다.\n");
fileprint("happyending2.txt");
Sleep(1500);
system("cls");
scene("--HAPPY END--");

}

void keyroom() {
    fileprint("keyroom.txt");
    while(1){
        int s = _getch();

        if(s=='1'){       // 열쇠 얻기
            if(!keyhave){
                keyhave = 1;
                printf("\n열쇠 획득!\n");
                
            } else {
                printf("\n이미 소유한 아이템\n");

            }
                Sleep(1000);
                system("cls");
                fileprint("keyroom.txt");
        }
        else if(s == 27) return;
    }
}





int main(){
 choice1F();
}
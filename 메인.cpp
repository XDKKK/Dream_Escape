#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "dream.h"

SceneID field1, field2, field3, field4, field5, gameroom1, gameroom2, maze[7];

ObjectID NPC1, mover1, mover2, mover3, mover4, mover5, mover6, mover7, mover8, mazemover[28], pt1, pt2, keypad;

char buf[50];
int mazemoveX1 = 80, maemoveX2 = 550, mazemoveX3 = 1020;

ObjectID createObject(const char* Image, SceneID Scene, int x, int y, bool shown = true) {
	ObjectID Object = createObject(Image);
	locateObject(Object, Scene, x, y);
	if (shown) showObject(Object);

	return Object;
}




void MouseCallback1(ObjectID Object, int x, int y, MouseAction action) {
	if (Object == NPC1) { 
		showMessage("여긴 어디지??\n화살표를 눌러 주위를 둘러보자");
		setObjectImage(NPC1, "Images1/npc_2.png");
		locateObject(NPC1, field1, 400, 200);
		showObject(mover1);
		}
	else if (Object == mover1) {
		enterScene(field2);
		showMessage("앞의 문을 클릭해보자!");
	}
	else if (Object == pt1) {
		enterScene(field3);
		showMessage("꿈에서 빠져나오고 싶어?\n모든 거울에 들어가보는게 어때?\n거울은 마우스클릭으로 들어갈 수 있을거야");
	}
	else if (Object == mover2) {
		enterScene(field4);
	    showMessage("들어갈 수 있는 거울이 보인다.\n클릭해서 들어가볼까?");
    }
	else if (Object == mover3) {
		enterScene(field5);
		showMessage("들어갈 수 있는 거울이 보인다.\n클릭해서 들어가볼까?");
		PlaySound(TEXT("bgm2.wav"), NULL, SND_ASYNC | SND_LOOP);
	}
	else if (Object == mover4) {
		enterScene(field3);
	}
	
	else if (Object == mover5) {
		enterScene(field3);
	}
	else if (Object == pt2) {
		enterScene(gameroom1);

	}
	else if (Object == mover7) {
		enterScene(maze[0]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	} 
	// 미로 게임 마우스 콜백 설정 (아직 미완성!!), 4k = 왼쪽(서쪽), 4k + 1 = 아래(남쪽), 4k + 2 = 오른쪽(동쪽), 4k + 3 = 위쪽(북쪽)
	else if (Object == mazemover[0]) {
		enterScene(maze[1]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[4]) {
		enterScene(maze[2]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[8]) {
		enterScene(maze[3]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[12]) {
		enterScene(maze[4]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[16]) {
		enterScene(maze[5]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[20]) {
		enterScene(maze[6]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
}





int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	setMouseCallback(MouseCallback1);
	

	
	

	// 필드1 설정시작
	field1 = createScene("필드1", "Images1/Back1.jpg");
	PlaySound(TEXT("bgm1.wav"), NULL, SND_ASYNC | SND_LOOP);

	showMessage("자고 있는 푸앙을 클릭해 깨우자");

	NPC1 = createObject("Images1/npc_1.png", field1, 400,280);
    scaleObject(NPC1, 0.5f);
	

	mover1 = createObject("Images1/goto_right.png", field1, 1000, 300, false);
	scaleObject(mover1, 1.5f);
	//필드1 설정끝
    //필드2 설정시작
	field2 = createScene("필드2", "Images1/Back2.webp");

    pt1 = createObject("Images1/portal1.png", field2, 733, 392);
	scaleObject(pt1, 0.47f);
	//필드2 설정끝
    //필드3 설정시작(메인방)
	field3 = createScene("필드3", "Images1/Back3.jpg");

	mover2 = createObject("Images1/goto_left.png", field3, 130, 130);
	scaleObject(mover2, 1.5f);
	
    mover3 = createObject("Images1/goto_right.png", field3, 1040, 130);
	scaleObject(mover3, 1.5f);

	mover7 = createObject("Images1/goto_maze.png", field3, 530, 370);
	scaleObject(mover7, 1.5f);
	//필드3 끝
	//필드4 설정시작(메인 왼쪽방)
	field4 = createScene("필드4", "Images1/Back4.jpg");

	mover4= createObject("Images1/goto_right.png", field4, 1100, 160);
	scaleObject(mover4, 1.5f);
	

	pt2 = createObject("Images1/portal2.png", field4, 570, 270);
	scaleObject(pt2, 0.7f);
	//필드4 끝
    //필드5 설정시작(메인 오른쪽방)
	field5 = createScene("필드5", "Images1/Back5.webp");

	mover5 = createObject("Images1/goto_left.png", field5, 130, 160);
	scaleObject(mover5, 1.5f);
    //게임룸1 설정시작
	gameroom1 = createScene("게임룸1", "Images1/Back6.jpg");

	mover6 = createObject("Images1/goto_right.png", gameroom1, 1000, 160);
	scaleObject(mover6, 1.5f);
	//미로 설정 시작
	//미로의 좌측 이동버튼들
	maze[0] = createScene("미로", "Images1/Back7_1.jpg");
	maze[1] = createScene("미로", "Images1/Back7_2.jpg");
	maze[2] = createScene("미로", "Images1/Back7_3.jpg");
	maze[3] = createScene("미로", "Images1/Back7_4.jpg");
	maze[4] = createScene("미로", "Images1/Back7_5.jpg");
	maze[5] = createScene("미로", "Images1/Back7_6.jpg");
	maze[6] = createScene("미로", "Images1/Back7_7.jpg");
	

	for (int i = 0; i < 7; i++) {
		mazemover[4 * i] = createObject("Images1/goto_left.png", maze[i], mazemoveX1, 160);
	}
	
	
	
    startGame(field1);
}
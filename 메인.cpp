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
		showMessage("���� �����??\nȭ��ǥ�� ���� ������ �ѷ�����");
		setObjectImage(NPC1, "Images1/npc_2.png");
		locateObject(NPC1, field1, 400, 200);
		showObject(mover1);
		}
	else if (Object == mover1) {
		enterScene(field2);
		showMessage("���� ���� Ŭ���غ���!");
	}
	else if (Object == pt1) {
		enterScene(field3);
		showMessage("�޿��� ���������� �;�?\n��� �ſ￡ �����°� �?\n�ſ��� ���콺Ŭ������ �� �� �����ž�");
	}
	else if (Object == mover2) {
		enterScene(field4);
	    showMessage("�� �� �ִ� �ſ��� ���δ�.\nŬ���ؼ� ������?");
    }
	else if (Object == mover3) {
		enterScene(field5);
		showMessage("�� �� �ִ� �ſ��� ���δ�.\nŬ���ؼ� ������?");
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
	// �̷� ���� ���콺 �ݹ� ���� (���� �̿ϼ�!!), 4k = ����(����), 4k + 1 = �Ʒ�(����), 4k + 2 = ������(����), 4k + 3 = ����(����)
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
	

	
	

	// �ʵ�1 ��������
	field1 = createScene("�ʵ�1", "Images1/Back1.jpg");
	PlaySound(TEXT("bgm1.wav"), NULL, SND_ASYNC | SND_LOOP);

	showMessage("�ڰ� �ִ� Ǫ���� Ŭ���� ������");

	NPC1 = createObject("Images1/npc_1.png", field1, 400,280);
    scaleObject(NPC1, 0.5f);
	

	mover1 = createObject("Images1/goto_right.png", field1, 1000, 300, false);
	scaleObject(mover1, 1.5f);
	//�ʵ�1 ������
    //�ʵ�2 ��������
	field2 = createScene("�ʵ�2", "Images1/Back2.webp");

    pt1 = createObject("Images1/portal1.png", field2, 733, 392);
	scaleObject(pt1, 0.47f);
	//�ʵ�2 ������
    //�ʵ�3 ��������(���ι�)
	field3 = createScene("�ʵ�3", "Images1/Back3.jpg");

	mover2 = createObject("Images1/goto_left.png", field3, 130, 130);
	scaleObject(mover2, 1.5f);
	
    mover3 = createObject("Images1/goto_right.png", field3, 1040, 130);
	scaleObject(mover3, 1.5f);

	mover7 = createObject("Images1/goto_maze.png", field3, 530, 370);
	scaleObject(mover7, 1.5f);
	//�ʵ�3 ��
	//�ʵ�4 ��������(���� ���ʹ�)
	field4 = createScene("�ʵ�4", "Images1/Back4.jpg");

	mover4= createObject("Images1/goto_right.png", field4, 1100, 160);
	scaleObject(mover4, 1.5f);
	

	pt2 = createObject("Images1/portal2.png", field4, 570, 270);
	scaleObject(pt2, 0.7f);
	//�ʵ�4 ��
    //�ʵ�5 ��������(���� �����ʹ�)
	field5 = createScene("�ʵ�5", "Images1/Back5.webp");

	mover5 = createObject("Images1/goto_left.png", field5, 130, 160);
	scaleObject(mover5, 1.5f);
    //���ӷ�1 ��������
	gameroom1 = createScene("���ӷ�1", "Images1/Back6.jpg");

	mover6 = createObject("Images1/goto_right.png", gameroom1, 1000, 160);
	scaleObject(mover6, 1.5f);
	//�̷� ���� ����
	//�̷��� ���� �̵���ư��
	maze[0] = createScene("�̷�", "Images1/Back7_1.jpg");
	maze[1] = createScene("�̷�", "Images1/Back7_2.jpg");
	maze[2] = createScene("�̷�", "Images1/Back7_3.jpg");
	maze[3] = createScene("�̷�", "Images1/Back7_4.jpg");
	maze[4] = createScene("�̷�", "Images1/Back7_5.jpg");
	maze[5] = createScene("�̷�", "Images1/Back7_6.jpg");
	maze[6] = createScene("�̷�", "Images1/Back7_7.jpg");
	

	for (int i = 0; i < 7; i++) {
		mazemover[4 * i] = createObject("Images1/goto_left.png", maze[i], mazemoveX1, 160);
	}
	
	
	
    startGame(field1);
}
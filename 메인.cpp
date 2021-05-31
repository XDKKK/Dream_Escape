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

ObjectID NPC1, NPC2, checkNPC1; //상호작용을 위한 캐릭터 오브젝트
ObjectID mover1, mover2, mover3, mover4, mover5, mover6, mover7, mover8, mazemover[24], pt1, pt2, pt3; //이동 관련 오브젝트
ObjectID bk[22], notion, hiddenroad[4], block[9];
char buf[50];

int bkX1 = 296, bkX2 = 356, bkX3 = 416, bkX4 = 476, bkX5 = 536, bkX6 = 596, bkX7 = 656, bkX8 = 716, bkX9 = 776, bkX10 = 836, bkX11 = 896, bkX12 = 956,
bkY1 = 400, bkY2 = 460, bkY3 = 520, bkY4 = 580, bkY5 = 640, bkY6 = 700, bkY7 = 760, bkY8 = 820,
G1X = 356, G1Y = 460; //게임1 내의 xy좌표
bool hide = false; //게임1 진행시 불타입
int bX0 = 200, bX1 = 350, bX2 = 500, bY0 = 100, bY1 = 250, bY2 = 400;	
bool stb0 = true, stb1 = false, stb2 = true, stb3 = false, stb4 = true, stb5 = false, stb6 = true, stb7 = false, stb8 = true; //게임2 진행시 블록의 불타입
bool ptshown1 = true, ptshown2 = true;//룸4,5에서 포탈 보이기 불타입
int Key = 0; //Key변수가 2가 되면 메인룸에 미로로 가는 입구 생성
int mazemoveX1 = 80, mazemoveX2 = 520, mazemoveX3 = 970, mazemoveY1 = 160, mazemoveY2 = 40, mazemoveY3 = 250; //미로 내의 이동버튼의 xy좌표

ObjectID createObject(const char* Image, SceneID Scene, int x, int y, bool shown = true) {
	ObjectID Object = createObject(Image);
	locateObject(Object, Scene, x, y);
	if (shown) showObject(Object);

	return Object;
} //물체 생성, 위치, 보이기/숨기기 설정 함수

bool collidedDown() {  // gameroom1에서 위 -> 아래 충돌 판단 함수!!
	if (G1X == bkX1 && G1Y - 10 < bkY2) return false; 
	if (G1X == bkX2 && G1Y - 10 < bkY2) return false;  
	if (G1X == bkX7 && G1Y - 10 < bkY2) return false;
	if (G1X == bkX8 && G1Y - 10 < bkY2) return false; 
	if (G1X == bkX2 && G1Y - 10 < bkY4 && G1Y - 10 > bkY3) return false;  
	if (G1X == bkX3 && G1Y - 10 < bkY4) return false;
	if (G1X == bkX5 && G1Y - 10 < bkY4 && G1Y - 10 > bkY3) return false; 
	if (G1X == bkX6 && G1Y - 10 < bkY4 && G1Y - 10 > bkY3) return false;  
	if (G1X == bkX10 && G1Y - 10 < bkY4 && G1Y - 10 > bkY3) return false;
	if (G1X == bkX8 && G1Y - 10 < bkY6 && G1Y - 10 > bkY5) return false; 
	if (G1X == bkX9 && G1Y - 10 < bkY6 && G1Y - 10 > bkY5) return false;  
	if (G1X == bkX2 && G1Y - 10 < bkY7 && G1Y - 10 > bkY6) return false;
	if (G1X == bkX3 && G1Y - 10 < bkY7 && G1Y - 10 > bkY6) return false; 
	if (G1X == bkX4 && G1Y - 10 < bkY7 && G1Y - 10 > bkY6) return false;  
	if (G1X == bkX6 && G1Y - 10 < bkY7 && G1Y - 10 > bkY6) return false;
	//밑의 코드는 벗어나기 방지
	if (G1Y == bkY1) {
		if (hide) {
			if (G1X == bkX5) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	if (G1Y == bkY1 - 180) return false;
	if (G1X == bkX12 + 120 && G1Y == bkY7) return false;
	if (G1X == bkX12 + 60 && G1Y == bkY7) return false;
	if (G1X == bkX12 && G1Y == bkY7) return false;
}

bool collidedUp() {    //gameroom1에서 아래 -> 위 충돌 판단 함수!!
	if (G1X == bkX2 && G1Y + 70 > bkY3 && G1Y + 70 < bkY4) return false;
	if (G1X == bkX2 && G1Y + 70 > bkY6 && G1Y + 70 < bkY7) return false;
	if (G1X == bkX3 && G1Y + 70 > bkY6 && G1Y + 70 < bkY7) return false;
	if (G1X == bkX4 && G1Y + 70 > bkY5 && G1Y + 70 < bkY6) return false;
	if (G1X == bkX5 && G1Y + 70 > bkY3 && G1Y + 70 < bkY4) return false;
	if (G1X == bkX6 && G1Y + 70 > bkY3 && G1Y + 70 < bkY4) return false;
	if (G1X == bkX6 && G1Y + 70 > bkY6 && G1Y + 70 < bkY7) return false;
	if (G1X == bkX8 && G1Y + 70 > bkY5 && G1Y + 70 < bkY6) return false;
	if (G1X == bkX9 && G1Y + 70 > bkY4 && G1Y + 70 < bkY5) return false;
	if (G1X == bkX9 && G1Y + 70 > bkY7 && G1Y + 70 < bkY8) return false;
	if (G1X == bkX10 && G1Y + 70 > bkY3 && G1Y + 70 < bkY4) return false;
	if (G1X == bkX10 && G1Y + 70 > bkY7 && G1Y + 70 < bkY8) return false;
	if (G1X == bkX11 && G1Y + 70 > bkY7 && G1Y + 70 < bkY8) return false;
	//밑의 코드는 벗어나기 방지
	if (G1X == bkX5 && G1Y == bkY1 - 180) return false;
	if (G1Y == bkY7) return false;
	if (G1X == bkX12 + 60 && G1Y == bkY7) return false;
}

bool collidedRight() {   //gameroom1에서 왼쪽 -> 오른쪽 충돌 판단 함수!!
	if (G1Y == bkY1 && G1X + 70 > bkX7 && G1X + 70 < bkX8) return false;
	if (G1Y == bkY2 && G1X + 70 > bkX3 && G1X + 70 < bkX4) return false;
	if (G1Y == bkY3 && G1X + 70 > bkX2 && G1X + 70 < bkX3) return false;
	if (G1Y == bkY3 && G1X + 70 > bkX5 && G1X + 70 < bkX6) return false;
	if (G1Y == bkY3 && G1X + 70 > bkX10 && G1X + 70 < bkX11) return false;
	if (G1Y == bkY4 && G1X + 70 > bkX9 && G1X + 70 < bkX10) return false;
	if (G1Y == bkY5 && G1X + 70 > bkX4 && G1X + 70 < bkX5) return false;
	if (G1Y == bkY5 && G1X + 70 > bkX8 && G1X + 70 < bkX9) return false;
	if (G1Y == bkY6 && G1X + 70 > bkX2 && G1X + 70 < bkX3) return false;
	if (G1Y == bkY6 && G1X + 70 > bkX6 && G1X + 70 < bkX7) return false;
	if (G1Y == bkY7 && G1X + 70 > bkX9 && G1X + 70 < bkX10) return false;
	//밑의 코드는 벗어나기 방지
	if (G1X == bkX12 + 120 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX12) return false;
	if (G1X == bkX12 + 120 && G1Y == bkY7) return false;
}

bool collidedLeft() {     //gameroom1에서 오른쪽 -> 왼쪽 충돌 판단 함수!!
	if (G1Y == bkY1 && G1X - 10 > bkX3 && G1X - 10 < bkX4) return false;
	if (G1Y == bkY1 && G1X - 10 > bkX8 && G1X - 10 < bkX9) return false;
	if (G1Y == bkY2 && G1X - 10 > bkX3 && G1X - 10 < bkX4) return false;
	if (G1Y == bkY3 && G1X - 10 > bkX3 && G1X - 10 < bkX4) return false;
	if (G1Y == bkY3 && G1X - 10 > bkX6 && G1X - 10 < bkX7) return false;
	if (G1Y == bkY3 && G1X - 10 > bkX10 && G1X - 10 < bkX11) return false;
	if (G1Y == bkY4 && G1X - 10 > bkX9 && G1X - 10 < bkX10) return false;
	if (G1Y == bkY5 && G1X - 10 > bkX4 && G1X - 10 < bkX5) return false;
	if (G1Y == bkY5 && G1X - 10 > bkX9 && G1X - 10 < bkX10) return false;
	if (G1Y == bkY6 && G1X - 10 > bkX4 && G1X - 10 < bkX5) return false;
	if (G1Y == bkY6 && G1X - 10 > bkX6 && G1X - 10 < bkX7) return false;
	if (G1Y == bkY7 && G1X - 10 > bkX11 && G1X - 10 < bkX12) return false;
	//밑의 코드는 벗어나기 방지위함
	if (G1X == bkX5 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX12 + 120 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX1) return false;
}

// wasd 이동버튼 충돌 판정




void MouseCallback1(ObjectID Object, int x, int y, MouseAction action) {
	if (Object == NPC1) { 
		showMessage("여긴 어디지??\n화살표를 눌러 주위를 둘러보자\n분홍색 화살표들은 클릭하면 이동할 수 있다!");
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
		showMessage("꿈에서 빠져나오고 싶어?\n모든 거울에 들어가보는게 어때?\n왼쪽 오른쪽 방의 거울은 마우스클릭으로 들어갈 수 있어");
	}
	else if (Object == mover2) {
		enterScene(field4);
	    if (ptshown1) showMessage("들어갈 수 있는 거울이 보인다.\n클릭해서 들어가볼까?");
    }
	else if (Object == mover3) {
		enterScene(field5);
		if (ptshown2) showMessage("들어갈 수 있는 거울이 보인다.\n클릭해서 들어가볼까?");
	}
	else if (Object == mover4) {
		enterScene(field3);
	}
	
	else if (Object == mover5) {
		enterScene(field3);
	}
	else if (Object == mover6) {
		enterScene(field4); hideObject(pt2); Key++;
	}
	else if (Object == pt2) {
		enterScene(gameroom1);
		
	}
	else if (Object == pt3) {
		enterScene(gameroom2);
	}
	else if (Object == block[0]) { //여기서부터 게임룸2의 마우스 콜백
		if (stb0) { hideObject(block[0]); setObjectImage(block[0], "Images1/blockp4.jpg"); showObject(block[0]); stb0 = false; }
		else { hideObject(block[0]); setObjectImage(block[0], "Images1/blockg2.png"); showObject(block[0]); stb0 = true; }
		if (stb1) { hideObject(block[1]); setObjectImage(block[1], "Images1/blockp4.jpg"); showObject(block[1]); stb1 = false; }
		else { hideObject(block[1]); setObjectImage(block[1], "Images1/blockg2.png"); showObject(block[1]); stb1 = true; }
		if (stb3) { hideObject(block[3]); setObjectImage(block[3], "Images1/blockp4.jpg"); showObject(block[3]); stb3 = false; }
		else { hideObject(block[3]); setObjectImage(block[3], "Images1/blockg2.png"); showObject(block[3]); stb3 = true; }
	}
	else if (Object == block[1]) {
		if (stb1) { hideObject(block[1]); setObjectImage(block[1], "Images1/blockp4.jpg"); showObject(block[1]); stb1 = false; }
		else { hideObject(block[1]); setObjectImage(block[1], "Images1/blockg2.png"); showObject(block[1]); stb1 = true; }
		if (stb0) {hideObject(block[0]); setObjectImage(block[0], "Images1/blockp4.jpg"); showObject(block[0]); stb0 = false;}
		else {hideObject(block[0]); setObjectImage(block[0], "Images1/blockg2.png"); showObject(block[0]); stb0 = true;}
		if (stb2) { hideObject(block[2]); setObjectImage(block[2], "Images1/blockp4.jpg"); showObject(block[2]); stb2 = false; }
		else { hideObject(block[2]); setObjectImage(block[2], "Images1/blockg2.png"); showObject(block[2]); stb2 = true; }
		if (stb4) { hideObject(block[4]); setObjectImage(block[4], "Images1/blockp4.jpg"); showObject(block[4]); stb4 = false; }
		else { hideObject(block[4]); setObjectImage(block[4], "Images1/blockg2.png"); showObject(block[4]); stb4 = true; }
	}
	else if (Object == block[2]) {
		if (stb2) { hideObject(block[2]); setObjectImage(block[2], "Images1/blockp4.jpg"); showObject(block[2]); stb2 = false; }
		else { hideObject(block[2]); setObjectImage(block[2], "Images1/blockg2.png"); showObject(block[2]); stb2 = true; }
		if (stb1) { hideObject(block[1]); setObjectImage(block[1], "Images1/blockp4.jpg"); showObject(block[1]); stb1 = false; }
		else { hideObject(block[1]); setObjectImage(block[1], "Images1/blockg2.png"); showObject(block[1]); stb1 = true; }
		if (stb2) { hideObject(block[5]); setObjectImage(block[5], "Images1/blockp4.jpg"); showObject(block[5]); stb5 = false; }
		else { hideObject(block[5]); setObjectImage(block[5], "Images1/blockg2.png"); showObject(block[5]); stb5 = true; }
	}
	else if (Object == block[3]) {
		if (stb3) { hideObject(block[3]); setObjectImage(block[3], "Images1/blockp4.jpg"); showObject(block[3]); stb3 = false; }
		else { hideObject(block[3]); setObjectImage(block[3], "Images1/blockg2.png"); showObject(block[3]); stb3 = true; }
		if (stb0) { hideObject(block[0]); setObjectImage(block[0], "Images1/blockp4.jpg"); showObject(block[0]); stb0 = false; }
		else { hideObject(block[0]); setObjectImage(block[0], "Images1/blockg2.png"); showObject(block[0]); stb0 = true; }
		if (stb4) { hideObject(block[4]); setObjectImage(block[4], "Images1/blockp4.jpg"); showObject(block[4]); stb4 = false; }
		else { hideObject(block[4]); setObjectImage(block[4], "Images1/blockg2.png"); showObject(block[4]); stb4 = true; }
		if (stb6) { hideObject(block[6]); setObjectImage(block[6], "Images1/blockp4.jpg"); showObject(block[6]); stb6 = false; }
		else { hideObject(block[6]); setObjectImage(block[6], "Images1/blockg2.png"); showObject(block[6]); stb6 = true; }
	}
	else if (Object == block[4]) {
		if (stb4) { hideObject(block[4]); setObjectImage(block[4], "Images1/blockp4.jpg"); showObject(block[4]); stb4 = false; }
		else { hideObject(block[4]); setObjectImage(block[4], "Images1/blockg2.png"); showObject(block[4]); stb4 = true; }
		if (stb1) { hideObject(block[1]); setObjectImage(block[1], "Images1/blockp4.jpg"); showObject(block[1]); stb1 = false; }
		else { hideObject(block[1]); setObjectImage(block[1], "Images1/blockg2.png"); showObject(block[1]); stb1 = true; }
		if (stb3) { hideObject(block[3]); setObjectImage(block[3], "Images1/blockp4.jpg"); showObject(block[3]); stb3 = false; }
		else { hideObject(block[3]); setObjectImage(block[3], "Images1/blockg2.png"); showObject(block[3]); stb3 = true; }
		if (stb5) { hideObject(block[5]); setObjectImage(block[5], "Images1/blockp4.jpg"); showObject(block[5]); stb5 = false; }
		else { hideObject(block[5]); setObjectImage(block[5], "Images1/blockg2.png"); showObject(block[5]); stb5 = true; }
		if (stb7) { hideObject(block[7]); setObjectImage(block[7], "Images1/blockp4.jpg"); showObject(block[7]); stb7 = false; }
		else { hideObject(block[7]); setObjectImage(block[7], "Images1/blockg2.png"); showObject(block[7]); stb7 = true; }
	}
	else if (Object == block[5]) {
		if (stb5) { hideObject(block[5]); setObjectImage(block[5], "Images1/blockp4.jpg"); showObject(block[5]); stb5 = false; }
		else { hideObject(block[5]); setObjectImage(block[5], "Images1/blockg2.png"); showObject(block[5]); stb5 = true; }
		if (stb2) { hideObject(block[2]); setObjectImage(block[2], "Images1/blockp4.jpg"); showObject(block[2]); stb2 = false; }
		else { hideObject(block[2]); setObjectImage(block[2], "Images1/blockg2.png"); showObject(block[2]); stb2 = true; }
		if (stb4) { hideObject(block[4]); setObjectImage(block[4], "Images1/blockp4.jpg"); showObject(block[4]); stb4 = false; }
		else { hideObject(block[4]); setObjectImage(block[4], "Images1/blockg2.png"); showObject(block[4]); stb4 = true; }
		if (stb8) { hideObject(block[8]); setObjectImage(block[8], "Images1/blockp4.jpg"); showObject(block[8]); stb8 = false; }
		else { hideObject(block[8]); setObjectImage(block[8], "Images1/blockg2.png"); showObject(block[8]); stb8 = true; }
	}
	else if (Object == block[6]) {
		if (stb6) { hideObject(block[6]); setObjectImage(block[6], "Images1/blockp4.jpg"); showObject(block[6]); stb6 = false; }
		else { hideObject(block[6]); setObjectImage(block[6], "Images1/blockg2.png"); showObject(block[6]); stb6 = true; }
		if (stb3) { hideObject(block[3]); setObjectImage(block[3], "Images1/blockp4.jpg"); showObject(block[3]); stb3= false; }
		else { hideObject(block[3]); setObjectImage(block[3], "Images1/blockg2.png"); showObject(block[3]); stb3 = true; }
		if (stb7) { hideObject(block[7]); setObjectImage(block[7], "Images1/blockp4.jpg"); showObject(block[7]); stb7 = false; }
		else { hideObject(block[7]); setObjectImage(block[7], "Images1/blockg2.png"); showObject(block[7]); stb7 = true; }
	}
	else if (Object == block[7]) {
		if (stb7) { hideObject(block[7]); setObjectImage(block[7], "Images1/blockp4.jpg"); showObject(block[7]); stb7 = false; }
		else { hideObject(block[7]); setObjectImage(block[7], "Images1/blockg2.png"); showObject(block[7]); stb7 = true; }
		if (stb4) { hideObject(block[4]); setObjectImage(block[4], "Images1/blockp4.jpg"); showObject(block[4]); stb4 = false; }
		else { hideObject(block[4]); setObjectImage(block[4], "Images1/blockg2.png"); showObject(block[4]); stb4 = true; }
		if (stb6) { hideObject(block[6]); setObjectImage(block[6], "Images1/blockp4.jpg"); showObject(block[6]); stb6 = false; }
		else { hideObject(block[6]); setObjectImage(block[6], "Images1/blockg2.png"); showObject(block[6]); stb6 = true; }
		if (stb8) { hideObject(block[8]); setObjectImage(block[8], "Images1/blockp4.jpg"); showObject(block[8]); stb8 = false; }
		else { hideObject(block[8]); setObjectImage(block[8], "Images1/blockg2.png"); showObject(block[8]); stb8 = true; }
	}
	else if (Object == block[8]) {
		if (stb8) { hideObject(block[8]); setObjectImage(block[8], "Images1/blockp4.jpg"); showObject(block[8]); stb8 = false; }
		else { hideObject(block[8]); setObjectImage(block[8], "Images1/blockg2.png"); showObject(block[8]); stb8 = true; }
		if (stb5) { hideObject(block[5]); setObjectImage(block[5], "Images1/blockp4.jpg"); showObject(block[5]); stb5 = false; }
		else { hideObject(block[5]); setObjectImage(block[5], "Images1/blockg2.png"); showObject(block[5]); stb5 = true; }
		if (stb7) { hideObject(block[7]); setObjectImage(block[7], "Images1/blockp4.jpg"); showObject(block[7]); stb7 = false; }
		else { hideObject(block[7]); setObjectImage(block[7], "Images1/blockg2.png"); showObject(block[7]); stb7 = true; }
	}
	else if (Object == checkNPC1) {
	if (stb0 && stb1 && stb2 && stb3 && stb4 && stb5 && stb6 && stb7 && stb8) {
		showObject(mover7);
		showMessage("전부 녹색으로 맞췄다!\n화살표를 눌러 원래 있던 곳으로 돌아가자.");
		}
	}
	else if (Object == mover7) {
	enterScene(field5); hideObject(pt3); Key++;
}
	else if (Object == mover8) {
		enterScene(maze[0]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	} 
	// 미로 게임 마우스 콜백 설정, 4k = 왼쪽(서쪽), 4k + 1 = 아래(남쪽), 4k + 2 = 오른쪽(동쪽), 4k + 3 = 위쪽(북쪽), 해답은 WSNNES(서남북북동남)
	else if (Object == mazemover[0]) {
		enterScene(maze[1]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[5]) {
		enterScene(maze[2]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[11]) {
		enterScene(maze[3]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[15]) {
		enterScene(maze[4]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[18]) {
		enterScene(maze[5]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[21]) {
		enterScene(maze[6]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
	else if (Object == mazemover[1] || Object == mazemover[2] || Object == mazemover[3] || Object == mazemover[4] || Object == mazemover[6] || Object == mazemover[7] 
		  || Object == mazemover[8] || Object == mazemover[9] || Object == mazemover[10] || Object == mazemover[12] || Object == mazemover[13] || Object == mazemover[14]
		  || Object == mazemover[16] || Object == mazemover[17] || Object == mazemover[19] || Object == mazemover[20] || Object == mazemover[22] || Object == mazemover[23]) {
		enterScene(maze[0]); //힌트에 적힌 이동 순서를 지키지 않을 때, 미로의 첫번째 방으로 다시 돌아오게 함, 이동버튼 클릭 시마다 이동소리 bgm 재생
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
}

void keyboardCallback(KeyCode code, KeyState state) { //키보드 입력에 따라 오브젝트 위치 설정. gameroom1과 gameroom3에서 사용.
	if (state == KeyState::KEY_PRESSED) {
		if (code == KeyCode::KEY_A) {
			if (G1X == bkX10 && G1Y == bkY1) {
				G1X += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX8 && G1Y == bkY2) {
				G1X -= 60; G1Y += 300; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX12 && G1Y == bkY2) {
				G1X -= 300; G1Y += 300; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX2 && G1Y == bkY4) {
				G1X -= 60; G1Y += 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX7 && G1Y == bkY4) {
				G1X += 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX12 && G1Y == bkY4) {
				G1X -= 300; G1Y += 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX3 && G1Y == bkY5) {
				locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX12 && G1Y == bkY5) {
				G1X -= 300; G1Y += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX9 && G1Y == bkY6) {
				G1X += 60; G1Y -= 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX11 && G1Y == bkY6) {
				G1X -= 60; G1Y -= 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX7 && G1Y == bkY7) {
				G1X += 180; G1Y -= 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (collidedLeft()) {
				if (G1X == bkX6 && G1Y == bkY1) {
					if (hide) {
						showMessage("아까 보이지 않던 길이 보인다!");
						G1X = G1X - 60;
						locateObject(NPC2, gameroom1, G1X, G1Y);
						for (int i = 0; i < 4; i++) {
							showObject(hiddenroad[i]);
						}
					}
					else G1X = G1X - 60;
						locateObject(NPC2, gameroom1, G1X, G1Y);
					}
				else if (G1X == bkX12 + 60 && G1Y == bkY7) {
					G1X -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
					showObject(mover6); showMessage("도착!\n화살표를 눌러 원래 있던 곳으로 돌아가자."); ptshown1 = false;
				}
				else {
					G1X = G1X - 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				
			}  // gameroom1에서 a입력->화살표 마주치면 진행방향 이동, 아니라면 오브젝트 x위치 -
		}
		else if (code == KeyCode::KEY_D) {
			if (G1X == bkX6 && G1Y == bkY2) {
				G1X += 60; G1Y += 300; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX10 && G1Y == bkY2) {
				G1X -= 180; G1Y += 300; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX8 && G1Y == bkY3) {
				G1X += 240; G1Y -= 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX4 && G1Y == bkY4) {
				G1X -= 180; G1Y += 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX10 && G1Y == bkY4) {
				G1X -= 180; G1Y += 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX1 && G1Y == bkY5) {
				G1X += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX10 && G1Y == bkY5) {
				G1X -= 180; G1Y += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX7 && G1Y == bkY6) {
				G1X += 180; G1Y -= 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX9 && G1Y == bkY6) {
				G1X += 60; G1Y -= 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX4 && G1Y == bkY7) {
				G1X -= 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX7 && G1Y == bkY7) {
				G1X += 180; G1Y -= 180; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (collidedRight()) {
				if (G1X == bkX4 && G1Y == bkY1) {
					if (hide) {
						showMessage("아까 보이지 않던 길이 보인다!");
						G1X = G1X + 60;
						locateObject(NPC2, gameroom1, G1X, G1Y);
						for (int i = 0; i < 4; i++) {
							showObject(hiddenroad[i]);
						}
					}
					else G1X = G1X + 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				else if (G1X == bkX5 && G1Y == bkY1 - 180) {
					G1X += 540; locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				else {
					G1X = G1X + 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
			} //gameroom1에서 d입력 -> 화살표 마주치면 진행방향 이동, 아니라면 오브젝트 x위치 +
		}
		else if (code == KeyCode::KEY_S) {
			if (G1X == bkX9 && G1Y == bkY2) {
				G1X += 180; G1Y -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX9 && G1Y == bkY2) {
				G1X += 180; G1Y -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX7 && G1Y == bkY3) {
				G1Y += 240; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX11 && G1Y == bkY3) {
				G1X -= 240; G1Y += 240; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX1 && G1Y == bkY5) {
				G1Y += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX5 && G1Y == bkY5) {
				G1X -= 240; G1Y += 120; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX6 && G1Y == bkY5) {
				G1X += 120; G1Y -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX11 && G1Y == bkY6) {
				G1X -= 240; G1Y += 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (collidedDown()) {
				if (G1X == bkX5 && G1Y == bkY2) {
					if (hide) {
						showMessage("아까 보이지 않던 길이 보인다!");
						G1Y = G1Y - 60;
						locateObject(NPC2, gameroom1, G1X, G1Y);
						for (int i = 0; i < 4; i++) {
							showObject(hiddenroad[i]);
						}
					}
					else G1Y = G1Y - 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				else if (G1X == bkX5 && G1Y == bkY1) {
					G1Y = G1Y - 180;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				else {
					G1Y = G1Y - 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}


			}    //gameroom1에서 s입력 -> 화살표 마주치면 진행방향으로 이동, 아니라면 오브젝트 y위치 -
		}

		else if (code == KeyCode::KEY_W) {
			if (G1X == bkX1 && G1Y == bkY3) {
				G1Y += 240; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX11 && G1Y == bkY1) {
				G1X -= 240; G1Y += 360; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX9 && G1Y == bkY2) {
				G1X += 180; G1Y -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX11 && G1Y == bkY3) {
				G1X -= 240; G1Y += 240; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX2 && G1Y == bkY4) {
				G1X += 60; G1Y += 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX10 && G1Y == bkY5) {
				G1Y -= 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (G1X == bkX5 && G1Y == bkY6) {
				G1X -= 240; G1Y += 60; locateObject(NPC2, gameroom1, G1X, G1Y);
			}
			else if (collidedUp()) {
				if (G1X == bkX12 && G1Y == bkY6) {
					locateObject(NPC2, gameroom1, G1X, G1Y);
					showMessage("보이지 않는 벽에 의해 앞으로 진행할 수 없다!\n 아까 지나쳐온 곳에서 흔들리는 소리가 난다. 다시 되돌아 가보자.");
					showObject(notion);
					hide = true;
				}
				else if (G1X == bkX12 + 120 && G1Y == bkY1 - 180) {
					G1Y += 540; locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				else {
					G1Y += 60; locateObject(NPC2, gameroom1, G1X, G1Y);
				}
			}
			//gameroom1에서 w입력 -> 화살표 마주치면 진행방향으로 이동, 아니라면 오브젝트 y위치 +
		}
	}
}
			




int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	setMouseCallback(MouseCallback1);
	setKeyboardCallback(keyboardCallback);

	
	

	// 필드1 설정시작
	field1 = createScene("필드1", "Images1/Back1.jpg");
	PlaySound(TEXT("bgm1.wav"), NULL, SND_ASYNC | SND_LOOP); //미로에 들어가기 전까지 bgm 재생되도록

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

	mover8 = createObject("Images1/goto_maze.png", field3, 530, 370);
	scaleObject(mover8, 1.2f);
	//필드3 끝
	//필드4 설정시작(메인 왼쪽방)
	field4 = createScene("필드4", "Images1/Back4.jpg");

	mover4= createObject("Images1/goto_right.png", field4, 1100, 160);
	scaleObject(mover4, 1.5f);
	

	pt2 = createObject("Images1/portal2.png", field4, 570, 270);
	scaleObject(pt2, 0.7f);
	//필드4 끝
	//게임룸1 설정시작
	gameroom1 = createScene("게임룸1", "Images1/Back9_1.webp");

	bk[0] = createObject("Images1/black.jpg", gameroom1, bkX1, bkY1);
	bk[1] = createObject("Images1/black.jpg", gameroom1, bkX2, bkY1);
	bk[2] = createObject("Images1/black.jpg", gameroom1, bkX3, bkY1);
	bk[3] = createObject("Images1/black.jpg", gameroom1, bkX7, bkY1);
	bk[4] = createObject("Images1/black.jpg", gameroom1, bkX8, bkY1);
	bk[5] = createObject("Images1/black.jpg", gameroom1, bkX3, bkY2);
	bk[6] = createObject("Images1/black.jpg", gameroom1, bkX2, bkY3);
	bk[7] = createObject("Images1/black.jpg", gameroom1, bkX3, bkY3);
	bk[8] = createObject("Images1/black.jpg", gameroom1, bkX5, bkY3);
	bk[9] = createObject("Images1/black.jpg", gameroom1, bkX6, bkY3);
	bk[10] = createObject("Images1/black.jpg", gameroom1, bkX10, bkY3);
	bk[11] = createObject("Images1/black.jpg", gameroom1, bkX9, bkY4);
	bk[12] = createObject("Images1/black.jpg", gameroom1, bkX4, bkY5);
	bk[13] = createObject("Images1/black.jpg", gameroom1, bkX8, bkY5);
	bk[14] = createObject("Images1/black.jpg", gameroom1, bkX9, bkY5);
	bk[15] = createObject("Images1/black.jpg", gameroom1, bkX2, bkY6);
	bk[16] = createObject("Images1/black.jpg", gameroom1, bkX3, bkY6);
	bk[17] = createObject("Images1/black.jpg", gameroom1, bkX4, bkY6);
	bk[18] = createObject("Images1/black.jpg", gameroom1, bkX6, bkY6);
	bk[19] = createObject("Images1/black.jpg", gameroom1, bkX9, bkY7);
	bk[20] = createObject("Images1/black.jpg", gameroom1, bkX10, bkY7);
	bk[21] = createObject("Images1/black.jpg", gameroom1, bkX11, bkY7); //방향키 눌러도 막히게 되는 장애물 블록 설정

	mover6 = createObject("Images1/goto_right.png", gameroom1, 1000, 160, false);
	scaleObject(mover6, 1.5f);

	notion = createObject("Images1/notion.png", gameroom1, bkX5, bkY1, false);
	hiddenroad[0] = createObject("Images1/b4.jpg", gameroom1, bkX5, bkY1 - 180, false);
	hiddenroad[1] = createObject("Images1/b5.jpg", gameroom1, bkX6, bkY1 - 180, false);
	hiddenroad[2] = createObject("Images1/b6.jpg", gameroom1, bkX12 + 120, bkY1 - 120, false);
	hiddenroad[3] = createObject("Images1/b7.jpg", gameroom1, bkX12 + 60, bkY7, false);

	NPC2 = createObject("Images1/npc_3.png", gameroom1, G1X, G1Y);
	//게임룸1 설정끝
    //필드5 설정시작(메인 오른쪽방)
	field5 = createScene("필드5", "Images1/Back5.webp");

	mover5 = createObject("Images1/goto_left.png", field5, 130, 160);
	scaleObject(mover5, 1.5f);

	pt3 = createObject("Images1/portal2.png", field5, 870, 300);
	scaleObject(pt3, 0.7f);
    //필드5 설정끝
	//게임룸2 설정 시작
	gameroom2 = createScene("게임룸2");

	block[0] = createObject("Images1/blockg2.png", gameroom2, bX0, bY0);
	block[1] = createObject("Images1/blockp4.jpg", gameroom2, bX1, bY0);
	block[2] = createObject("Images1/blockg2.png", gameroom2, bX2, bY0);
	block[3] = createObject("Images1/blockp4.jpg", gameroom2, bX0, bY1); 
	block[4] = createObject("Images1/blockg2.png", gameroom2, bX1, bY1); 
	block[5] = createObject("Images1/blockp4.jpg", gameroom2, bX2, bY1);
	block[6] = createObject("Images1/blockg2.png", gameroom2, bX0, bY2);
	block[7] = createObject("Images1/blockp4.jpg", gameroom2, bX1, bY2);
	block[8] = createObject("Images1/blockg2.png", gameroom2, bX2, bY2);

	mover7 = createObject("Images1/goto_right.png", gameroom2, 400, 100, false);
	checkNPC1 = createObject("Images1/goto_right.png", gameroom2, 1000, 100);
	
	//미로 설정 시작(게임룸1, 2에서 게임을 클리어한 후 메인룸에서 가운데 화살표를 누르면 미로 들어감
	//미로의 장면 설정, 이동 방향버튼 생성
	maze[0] = createScene("미로", "Images1/Back7_1(2).jpg");
	maze[1] = createScene("미로", "Images1/Back7_2.jpg");
	maze[2] = createScene("미로", "Images1/Back7_3.jpg");
	maze[3] = createScene("미로", "Images1/Back7_4.jpg");
	maze[4] = createScene("미로", "Images1/Back7_5.jpg");
	maze[5] = createScene("미로", "Images1/Back7_6.jpg");
	maze[6] = createScene("미로", "Images1/Back7_7.jpg");
	
    for (int i = 0; i < 6; i++) {
		mazemover[4 * i] = createObject("Images1/goto_left.png", maze[i], mazemoveX1, mazemoveY1);
		mazemover[4 * i + 1] = createObject("Images1/maze_down.png", maze[i], mazemoveX2, mazemoveY2);
		mazemover[4 * i + 2] = createObject("Images1/goto_right.png", maze[i], mazemoveX3, mazemoveY1);
		mazemover[4 * i + 3] = createObject("Images1/maze_up.png", maze[i], mazemoveX2, mazemoveY3);
	}
	
	
	
    startGame(field1);
}
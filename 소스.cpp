#include <bangtal.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

SceneID field1, field2, field3, field4, field5;
ObjectID NPC1, mover1, mover2, mover3, mover4, mover5, mover6, mover7, pt1, keypad;



void mouseCallback1(ObjectID Object, int x, int y, MouseAction action) {
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
	

}


void main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	setMouseCallback(mouseCallback1);

	// 필드1 설정시작
	field1 = createScene("필드1", "Images1/Back1.jpg");
	PlaySound(TEXT("bgm1.wav"), NULL, SND_ASYNC | SND_LOOP);

	showMessage("자고 있는 푸앙을 클릭해 깨우자");

	NPC1 = createObject("Images1/npc_1.png");
    locateObject(NPC1, field1, 400, 280);
	scaleObject(NPC1, 0.5f);
	showObject(NPC1);

	mover1 = createObject("Images1/goto_right.png");
	locateObject(mover1, field1, 1000, 300);
	scaleObject(mover1, 1.5f);
	hideObject(mover1);  //필드1 설정끝
    //필드2 설정시작
	field2 = createScene("필드2", "Images1/Back2.webp");
    pt1 = createObject("Images1/portal1.png");
	locateObject(pt1, field2, 733, 392);
	scaleObject(pt1, 0.47f);
	showObject(pt1); //필드2 설정끝
    //필드3 설정시작
	field3 = createScene("필드3", "Images1/Back3.jpg");

	mover2 = createObject("Images1/goto_left.png");
	locateObject(mover2, field3, 0, 130);
	scaleObject(mover2, 0.5f);
	showObject(mover2);

	mover3 = createObject("Images1/goto_right.png");
	locateObject(mover3, field3, 1000, 130);
	scaleObject(mover3, 1.5f);
	showObject(mover3); //필드3 끝
	//필드4 설정시작
	field4 = createScene("필드4", "Images1/Back4.jpg");

	mover4= createObject("Images1/goto_right.png");
	locateObject(mover4, field4, 1100, 160);
	scaleObject(mover4, 1.5f);
	showObject(mover4);


	//필드5 설정시작
	field5 = createScene("필드5", "Images1/Back5.webp");

	mover5 = createObject("Images1/goto_left.png");
	locateObject(mover5, field5, 55, 160);
	scaleObject(mover5, 0.5f);
	showObject(mover5);


	


	startGame(field1);





}
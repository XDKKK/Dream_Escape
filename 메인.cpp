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

ObjectID NPC1, NPC2; //��ȣ�ۿ��� ���� ĳ���� ������Ʈ
ObjectID mover1, mover2, mover3, mover4, mover5, mover6, mover7, mover8, mazemover[24], pt1, pt2; //�̵� ���� ������Ʈ
ObjectID bk[22], notion, hiddenroad[4];
char buf[50];

int bkX1 = 296, bkX2 = 356, bkX3 = 416, bkX4 = 476, bkX5 = 536, bkX6 = 596, bkX7 = 656, bkX8 = 716, bkX9 = 776, bkX10 = 836, bkX11 = 896, bkX12 = 956,
bkY1 = 400, bkY2 = 460, bkY3 = 520, bkY4 = 580, bkY5 = 640, bkY6 = 700, bkY7 = 760, bkY8 = 820,
G1X = 356, G1Y = 460; //����1 ���� xy��ǥ
bool hide = false; //����1 ����� ��Ÿ��
bool ptshown1 = true, ptshown2 = true;//��4,5���� ��Ż ���̱� ��Ÿ��
int Key = 0; //Key������ 2�� �Ǹ� ���η뿡 �̷η� ���� �Ա� ����
int mazemoveX1 = 80, mazemoveX2 = 520, mazemoveX3 = 970, mazemoveY1 = 160, mazemoveY2 = 40, mazemoveY3 = 250; //�̷� ���� �̵���ư�� xy��ǥ

ObjectID createObject(const char* Image, SceneID Scene, int x, int y, bool shown = true) {
	ObjectID Object = createObject(Image);
	locateObject(Object, Scene, x, y);
	if (shown) showObject(Object);

	return Object;
} //��ü ����, ��ġ, ���̱�/����� ���� �Լ�

bool collidedDown() {  // gameroom1���� �� -> �Ʒ� �浹 �Ǵ� �Լ�!!
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
	//���� �ڵ�� ����� ����
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

bool collidedUp() {    //gameroom1���� �Ʒ� -> �� �浹 �Ǵ� �Լ�!!
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
	//���� �ڵ�� ����� ����
	if (G1X == bkX5 && G1Y == bkY1 - 180) return false;
	if (G1Y == bkY7) return false;
	if (G1X == bkX12 + 60 && G1Y == bkY7) return false;
}

bool collidedRight() {   //gameroom1���� ���� -> ������ �浹 �Ǵ� �Լ�!!
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
	//���� �ڵ�� ����� ����
	if (G1X == bkX12 + 120 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX12) return false;
	if (G1X == bkX12 + 120 && G1Y == bkY7) return false;
}

bool collidedLeft() {     //gameroom1���� ������ -> ���� �浹 �Ǵ� �Լ�!!
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
	//���� �ڵ�� ����� ��������
	if (G1X == bkX5 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX12 + 120 && G1Y == bkY1 - 180) return false;
	if (G1X == bkX1) return false;
}

// wasd �̵���ư �浹 ����

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
		showMessage("�޿��� ���������� �;�?\n��� �ſ￡ �����°� �?\n���� ������ ���� �ſ��� ���콺Ŭ������ �� �� �־�");
	}
	else if (Object == mover2) {
		enterScene(field4);
	    if (ptshown1) showMessage("�� �� �ִ� �ſ��� ���δ�.\nŬ���ؼ� ������?");
    }
	else if (Object == mover3) {
		enterScene(field5);
		if (ptshown2) showMessage("�� �� �ִ� �ſ��� ���δ�.\nŬ���ؼ� ������?");
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
	else if (Object == mover7) {
		enterScene(maze[0]);
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	} 
	// �̷� ���� ���콺 �ݹ� ����, 4k = ����(����), 4k + 1 = �Ʒ�(����), 4k + 2 = ������(����), 4k + 3 = ����(����), �ش��� WSNNES(�����Ϻϵ���)
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
		enterScene(maze[0]); //��Ʈ�� ���� �̵� ������ ��Ű�� ���� ��, �̷��� ù��° ������ �ٽ� ���ƿ��� ��, �̵���ư Ŭ�� �ø��� �̵��Ҹ� bgm ���
		PlaySound(TEXT("walksound.wav"), NULL, SND_ASYNC);
	}
}

void keyboardCallback(KeyCode code, KeyState state) { //Ű���� �Է¿� ���� ������Ʈ ��ġ ����. gameroom1�� gameroom3���� ���.
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
						showMessage("�Ʊ� ������ �ʴ� ���� ���δ�!");
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
					showObject(mover6); showMessage("����!!"); ptshown1 = false;
				}
				else {
					G1X = G1X - 60;
					locateObject(NPC2, gameroom1, G1X, G1Y);
				}
				
			}  // gameroom1���� a�Է�->ȭ��ǥ ����ġ�� ������� �̵�, �ƴ϶�� ������Ʈ x��ġ -
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
						showMessage("�Ʊ� ������ �ʴ� ���� ���δ�!");
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
			} //gameroom1���� d�Է� -> ȭ��ǥ ����ġ�� ������� �̵�, �ƴ϶�� ������Ʈ x��ġ +
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
						showMessage("�Ʊ� ������ �ʴ� ���� ���δ�!");
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


			}    //gameroom1���� s�Է� -> ȭ��ǥ ����ġ�� ����������� �̵�, �ƴ϶�� ������Ʈ y��ġ -
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
					showMessage("������ �ʴ� ���� ���� ������ ������ �� ����!\n �Ʊ� �����Ŀ� ���� ��鸮�� �Ҹ��� ����. �ٽ� �ǵ��� ������.");
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
			//gameroom1���� w�Է� -> ȭ��ǥ ����ġ�� ����������� �̵�, �ƴ϶�� ������Ʈ y��ġ +
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

	
	

	// �ʵ�1 ��������
	field1 = createScene("�ʵ�1", "Images1/Back1.jpg");
	PlaySound(TEXT("bgm1.wav"), NULL, SND_ASYNC | SND_LOOP); //�̷ο� ���� ������ bgm ����ǵ���

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
	gameroom1 = createScene("���ӷ�1", "Images1/Back9_1.webp");

	bk[0] = createObject("Images1/black.jpg", gameroom1, bkX1 ,bkY1);
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
	bk[21] = createObject("Images1/black.jpg", gameroom1, bkX11, bkY7); //����Ű ������ ������ �Ǵ� ��ֹ� ��� ����
	
	mover6 = createObject("Images1/goto_right.png", gameroom1, 1000, 160, false);
	scaleObject(mover6, 1.5f);

	notion = createObject("Images1/notion.png", gameroom1, bkX5, bkY1, false);
	hiddenroad[0] = createObject("Images1/b4.jpg", gameroom1, bkX5, bkY1 - 180, false);
	hiddenroad[1] = createObject("Images1/b5.jpg", gameroom1, bkX6, bkY1 - 180, false);
	hiddenroad[2] = createObject("Images1/b6.jpg", gameroom1, bkX12 + 120, bkY1 - 120, false);
	hiddenroad[3] = createObject("Images1/b7.jpg", gameroom1, bkX12 + 60, bkY7, false);

	NPC2 = createObject("Images1/npc_3.png", gameroom1, G1X, G1Y);
	//���ӷ�1 ������
	 
	//�̷� ���� ����(���ӷ�1, 2���� ������ Ŭ������ �� ���η뿡�� ��� ȭ��ǥ�� ������ �̷� ��
	//�̷��� ��� ����, �̵� �����ư ����
	maze[0] = createScene("�̷�", "Images1/Back7_1(2).jpg");
	maze[1] = createScene("�̷�", "Images1/Back7_2.jpg");
	maze[2] = createScene("�̷�", "Images1/Back7_3.jpg");
	maze[3] = createScene("�̷�", "Images1/Back7_4.jpg");
	maze[4] = createScene("�̷�", "Images1/Back7_5.jpg");
	maze[5] = createScene("�̷�", "Images1/Back7_6.jpg");
	maze[6] = createScene("�̷�", "Images1/Back7_7.jpg");
	
    for (int i = 0; i < 6; i++) {
		mazemover[4 * i] = createObject("Images1/goto_left.png", maze[i], mazemoveX1, mazemoveY1);
		mazemover[4 * i + 1] = createObject("Images1/maze_down.png", maze[i], mazemoveX2, mazemoveY2);
		mazemover[4 * i + 2] = createObject("Images1/goto_right.png", maze[i], mazemoveX3, mazemoveY1);
		mazemover[4 * i + 3] = createObject("Images1/maze_up.png", maze[i], mazemoveX2, mazemoveY3);
	}
	
	
	
    startGame(field1);
}
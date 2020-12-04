#include <stdio.h>
#include <string.h>
#include "disp.h"

//====================================================================================================//
//===================�����̊֐��͑S���摜�\��������BGM�ɂ��Ă̊֐������t�@�C���ł�==================//
//====================================================================================================//





//==========�G�t�F�N�g��==========//

void effect(void) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "big_oof.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	closesound(check_effect);
}

//�킢�n�܂����Ƃ���ɗ���BGM

void effect2(void) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "MLG_Horns.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	closesound(check_effect);
}


//����������BGM

void loseBGM(int onOff) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "Mission_Failed.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	if (onOff == 0) {
		closesound(check_effect);
	}
}

//����������BGM

void winBGM(int onOff) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "CRAB_RAVE.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	if (onOff == 0) {
		closesound(check_effect);
	}
}




//======================�摜�\������================================//

//�I���
void chooseArrow(int x, int y) {

	gotoxy(x, y);
	printf("  ��");

	gotoxy(x, y+1);
	printf("������");

	gotoxy(x, y + 2);
	printf("  ��");

	gotoxy(x, y + 3);
	printf("  ��");

}


//�L�����N�^�[�ǎ�̔L

void shock_cat(int x) {

	gotoxy(x, 13);
	printf("�@�@�@�@�@�@/��_��");

	gotoxy(x, 14);
	printf(" /��_,�� �q�i�@߄t߁j");

	gotoxy(x, 15);
	printf(" |�i�@߄t߁j �R ���j)");

	gotoxy(x, 16);
	printf(" �R__��/�P�P�P/ |");

	gotoxy(x, 17);
	printf("�P�_/�Q�Q�Q/");


}

//����
void punch1(void) {
	gotoxy(50, 15);
	printf("�ȁQ��");
	gotoxy(50, 16);
	printf("�E;'.�A(�E��(:;(�������� ");
	gotoxy(50, 17);
	printf("(�������߁���");
	gotoxy(50, 18);
	printf("/   ) �Y�o�o�o");
	gotoxy(50, 19);
	printf("( /�P��");

}

//�L�����N�^�[

void character1(int x,int y) {

	gotoxy(10, y-5);
	printf(" �@�@�@��");

	gotoxy(10, y-4);
	printf("�@�@/�L� `�[�@");

	gotoxy(10, y-3);
	printf("�@�@{�@ �X �l�L");

	gotoxy(10, y-2);
	printf("�@�^�@���@/��");

	gotoxy(10, y-1);
	printf("/�@�@�@ �^");

	gotoxy(10, y);
	printf("���O��");

}

void character2(int x,int y) {

	gotoxy(x, y-5);
	printf("�@�@m9�@�O�@9m");

	gotoxy(x, y-4);
	printf("�@�c�@�@�ȁȁ@�@�~");

	gotoxy(x, y-3);
	printf("m9�@�@(^�D^)�@�@9m�@");

	gotoxy(x, y-2);
	printf("�@�S�R�_�@���@ �j�@�c");

	gotoxy(x, y-1);
	printf("�@�@m9�^�O�@9m");

	gotoxy(x, y);
	printf("�@�@�@���P�P�P�_)");

}

void character3(int x,int y) {

	gotoxy(x, y-4);
	printf("�@�@�@�� ��");

	gotoxy(x, y-3);
	printf(" �@�^(*߁[�)�@�^�_");

	gotoxy(x, y-2);
	printf("�^|�P�����P|�_�^");

	gotoxy(x, y-1);
	printf(" �R__��/�P�P�P/ |");

	gotoxy(x, y);
	printf(" �@|�@ ���� �@ |�^");
}

void character4(int x,int y) {
	gotoxy(x, y-4);
	printf("�@�ȁQ��");

	gotoxy(x, y-3);
	printf(" (�@^�D^)��9m��9m");

	gotoxy(x, y-2);
	printf(" (m9�@��m9��m9");

	gotoxy(x, y-1);
	printf(" /�@�@�@)");

	gotoxy(x, y);
	printf("( /�P��");

}

void character_choice(int x, int y, int choice) {
	
	switch (choice) {
		case 1:
			character1(x, y);
			break;
		case 2:
			character2(x, y);
			break;
		case 3:
			character3(x, y);
			break;
		case 4:
			character4(x, y);
			break;
	}

}



void winScreen(void) {
	gotoxy(10, 15);
	printf("�@�@�@ �@ �^ �L�P �M(�_ ");

	gotoxy(10, 16);
	printf("�@�@�@�@ /�@ �@ �@ �@ �_-'��@�@�@�@�u���G�̐l�͎₵���Ȃ��E�E�E�v ");

	gotoxy(10, 17);
	printf("�@�@�@�@/�@�@�@�@�@�@�@ �R�@�R");

	gotoxy(10, 18);
	printf("�@�@�@ _|�@�@�@�@�@�@�@�@ |�@�@|");

	gotoxy(10, 19);
	printf("�@�@�@ �L!�@�@�@�@�@�@�@ /�@��^ �O ����- �_ ");

	gotoxy(10, 20);
	printf("�@�@�@�@ �_.__ _�@�@�@ /�@//�i �Q�Q�Q__/�@�M�R");

	gotoxy(10, 21);
	printf("�@�@�@�^�@�i�i�i j�� �L�R//�@�@�@�@�@ /�@ �_)�ɁP�M�_�Q�@�@�@�^�O�R ");

	gotoxy(10, 22);
	printf("�@�@ (.�@�@�@ �P�@�@�@�@�l.�@�@�@�@�@i�@�@�@|_�Q�Q_�^ �_|�P�P�@�@ �");

	gotoxy(10, 23);
	printf("�@�@ (�P�P�P�P�@�@�^�@ �M�R��Q�@ |�@�@ �L_|�Q�Q�_�@�@` �� �_.�^ ");

	gotoxy(10, 24);
	printf("�@�@�@�P�P�P�P�P�@�@�@�@�@�@�@ �P �P�P�@�@�@�@ �i�Q�Q�Q�m");


}



void loseScreen(void) {

	gotoxy(10, 14);
	printf("�@�@�@�@�@�@�@�@�@�@�@�@/�R�@�@�@�@�@�@ /�R");

	gotoxy(10, 15);
	printf("�@�@�@�@�@�@�@�@�@�@�@�@/ �@�R�@ �@�@�@ / �@�R");

	gotoxy(10, 16);
	printf("�@�@�Q�Q�Q�Q�Q�Q / �@ �@ �R�Q�Q/�@ �@ �@�R");

	gotoxy(10, 17);
	printf("�@�@|�@�Q�Q�Q�Q�@�^�@�@�@ �@ �@ �@�@�@:::::::::::::::�_");

	gotoxy(10, 18);
	printf("�@�@| |�@�@�@�@�@�@ /�^�@�@�@�@�@�@�@�_�@�@:::::::::::::::|");

	gotoxy(10, 19);
	printf("�@�@| |�@�@�@�@�@�@ |�@ ���@�@�@ �@�@�� �@�@ ::::::::::::::| �ア�l�������ɕ�����");

	gotoxy(10, 20);
	printf("�@�@| |�@�@�@�@�@�@.|�@�@�@�@�@�@�@�@�@�@�@�@�@:::::::::::::|");

	gotoxy(10, 21);
	printf("�@�@| |�@�@�@�@�@�@ |�@ �@�i__�l__�� �@.....:::::::::::::::::::/");

	gotoxy(10, 22);
	printf("�@�@| |�Q�Q�Q�Q�@�R�@�@�@�@�@�@.....:::::::::::::::::::::::<");

	gotoxy(10, 23);
	printf("�@ ���Q�Q�Q�^�P�P�@�@�@�@�@�@�@:::::::::::::::::::::::::|");

	gotoxy(10, 24);
	printf("�@�@|�_�@�@�@ |�@�@�@�@�@�@�@�@�@�@�@�@:::::::::::::::::::::::|");

	gotoxy(10, 25);
	printf("�@�@�_ �_�@�@�_�Q�Q�Q�@�@�@�@�@�@ ::::::::::::::::::::::::|");

}
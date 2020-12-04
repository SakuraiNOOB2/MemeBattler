#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <Windows.h>
#include "conioex.h"
#include "main.h"
#include "disp.h"


//�֐��v���g�^�C�v

void show_menu(void);  //���j���[�\���ƑI��
void read_data(void);  //�v���C���[�f�[�^�̓ǂݍ���
void create_player(void);  //�V�����L�����N�^�[�̍쐬
void load_player(void);  //�쐬�����L�����N�^�[�̓ǎ�

void start_battle(char player[15]);  //�킢�J�n
void battle(int player_location, int enemy_location);  //�킢�̎�
void victory(void);  //���������̃C���^�[�t�F�[�X
void lose(void);  //���������̃C���^�[�t�F�[�X

//���֐��v���g�^�C�v

int search(char find[15]);
int check_name(char check[15]);
int check_HP(float hp, float original_HP);

//�\����

//�L�����N�^�[�̏ڍ�
typedef struct {
	char name[15];
	int HP;
	int ATK;
	int DEF;
	int char_choice;
}STATUS;



//�O���[�o���ϐ�


//�v���C���[�f�[�^
STATUS player_data[PLAYER_NUM];
STATUS *pplayer_data;

//�v���C���[�f�[�^�J�E���^�[
int count;



//���y�t�@�C���ϐ�
int check_music;
char path[100];


//���C���֐�
void main(void) {

	show_menu();     //���j���[�\��
	system("pause");
}



//�֐�



//===============================�L�����N�^�[�̍쐬================================//

void create_player(void) {
	//�ϐ�
	int player_len;
	char player[15];
	int unique;
	int charChoice;

	int char1=11;
	int char2=41;
	int char3=71;
	int char4=101;


	int y_coor;
	y_coor = 21;

	int x, y;
	x = 11;
	y = y_coor;

	bool key_on = FALSE;

	FILE *fpp;

	pplayer_data = player_data;




	//�v���C���[�f�[�^�̓ǂݍ���
	read_data();


	//���y�𗬂�
	strcpy(path, "Uptown Sans.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	//�f�[�^�x�[�X�ɂ̓f�[�^��������Ȃ���
	if (count < 1) {
		//��ʕ\��
		setcursortype(NOCURSOR);

		system("cls");

		gotoxy(50, menu_y);
		printf("���߂Ă��̃Q�[�������邩��A");

		gotoxy(50, menu_y + 2);
		printf("�L�����N�^�[��2��邵���Ȃ�");

		rewind(stdin);
		getchar();
		system("cls");

		bool chooseChara = false;

		for (int s = 0; s < 2; s++) {

			setcursortype(NOCURSOR);

			while (!chooseChara) {

				gotoxy(50, 5);
				printf("�L�����N�^�[��I��ł�������");

				//�L�����N�^�[�\��
				
				character1(5, y_coor);
				character2(35, y_coor);
				character3(65, y_coor);
				character4(95, y_coor);

				//�I���u���b�N
				chooseArrow(x, y + 2);

				//�R���\�[�����͏���
				if (inport(PK_RIGHT)) {
					if (key_on == false) {
						x = x + 30;
						key_on = true;
						system("cls");
					}
				}
				else if (inport(PK_LEFT)) {
					if (key_on == false) {
						x = x - 30;
						key_on = true;
						system("cls");
					}
				}
				else {
					key_on = false;
				}
				if (x > 101) {
					x = 11;
					system("cls");
				}
				if (x < 10) {
					x = 101;
					system("cls");
				}
				if (inport(PK_ENTER)) {
					reinport();
					system("cls");
					switch (x) {
						case 11:
							effect();
							charChoice = 1;
							break;
						case 41:
							effect();
							charChoice = 2;
							break;
						case 71:
							effect();
							charChoice = 3;
							break;
						case 101:
							effect();
							charChoice = 4;
							break;
						
					}
					chooseChara = true;
				}
				

			}

			chooseChara = false;

			system("cls");

			//���̃A�X�L�[�A�[�g
			
			character_choice(15, y_coor, charChoice);

			//���͏���

			setcursortype(NORMALCURSOR);

			gotoxy(50, menu_y);
			printf("�L�����N�^�[%d�̖��O����͂��Ă�������", s + 1);

			gotoxy(50, menu_y + 1);
			printf("(�p�����Ɛ������܂܂��15�����ȓ�)");

			gotoxy(40, menu_y + 3);
			printf("���O�F");

			//���͑҂�
			rewind(stdin);
			scanf("%s", player);


			//���O��郋�[������邩�m�F

			while (check_name(player) == -1 || strlen(player) > 15) {


				system("cls");
				effect();

				//���̃A�X�L�[�A�[�g
				
				shock_cat(15);

				//�G���[���o��

				gotoxy(50, menu_y);
				printf("�����Ɠ��͂��Ă��������I");

				rewind(stdin);
				getchar();
				system("cls");

				gotoxy(50, 15);
				printf("�L�����N�^�[%d�̖��O����͂��Ă�������", s);

				gotoxy(50, 16);
				printf("(�p�����Ɛ������܂܂��15�����ȓ�)");

				gotoxy(40, 18);
				printf("���O�F");

				//���͑҂�
				rewind(stdin);
				scanf("%s", player);
			}

			player_len = strlen(player);
			player[player_len] = '\n';
			player[player_len + 1] = '\0';



			//�L�����N�^�[�쐬
			unique = 0;
			for (int i = 0; i < player_len; i++) {
				unique = unique + player[i];

			}

			//�����_��
			srand(unique);
			strcpy((pplayer_data + count)->name, player);
			srand(unique + 1);
			(pplayer_data + count)->HP = rand() % 1000 + 500;
			srand(unique + 2);
			(pplayer_data + count)->ATK = rand() % 300 + 100;
			srand(unique + 3);
			(pplayer_data + count)->DEF = rand() % 100 + 1;

			(pplayer_data + count)->char_choice = charChoice;


			//�t�@�C���I�[�v��
			fpp = fopen("player_data.db", "wb");

			//�f�[�^�x�[�X��������

			fwrite((pplayer_data + (count + 1)), sizeof(STATUS), 1, fpp);
			fclose(fpp);

			//�������񂾂��m�点
			system("cls");
			setcursortype(NOCURSOR);
			//���̃A�X�L�[�A�[�g
			character_choice(15, y_coor, charChoice);

			//�쐬����

			gotoxy(50, 15);
			printf("�L�����N�^�[%d�쐬�����I", s + 1);

			gotoxy(50, 16);
			printf("���̃L�����N�^�[���");

			gotoxy(50, 18);
			printf("���O�F%s", player);

			gotoxy(50, 19);
			printf("HP�F%d", (pplayer_data + (count))->HP);

			gotoxy(50, 20);
			printf("�U���́F%d", (pplayer_data + (count))->ATK);

			gotoxy(50, 21);
			printf("�h��́F%d", (pplayer_data + (count))->DEF);


			rewind(stdin);
			getchar();


			count++;
			system("cls");
		}
	}
	else {
		
	while (1) {

		setcursortype(NOCURSOR);

		gotoxy(50, 5);
		printf("�L�����N�^�[��I��ł�������");

		//�L�����N�^�[�\��

		character1(5, y_coor);
		character2(35, y_coor);
		character3(65, y_coor);
		character4(95, y_coor);

		//�I���u���b�N
		chooseArrow(x, y + 2);

		//�R���\�[�����͏���
		if (inport(PK_RIGHT)) {
			if (key_on == false) {
				x = x + 30;
				key_on = true;
				system("cls");
			}
		}
		else if (inport(PK_LEFT)) {
			if (key_on == false) {
				x = x - 30;
				key_on = true;
				system("cls");
			}
		}
		else {
			key_on = false;
		}
		if (x > 101) {
			x = 11;
			system("cls");
		}
		if (x < 10) {
			x = 101;
			system("cls");
		}
		if (inport(PK_ENTER)) {
			reinport();
			system("cls");
			switch (x) {
			case 11:
				effect();
				charChoice = 1;
				break;
			case 41:
				effect();
				charChoice = 2;
				break;
			case 71:
				effect();
				charChoice = 3;
				break;
			case 101:
				effect();
				charChoice = 4;
				break;

			}
			break;
		}


	}
		


		//���̃A�X�L�[�A�[�g

		character_choice(15, y_coor, charChoice);

		setcursortype(NORMALCURSOR);

		//��ʕ\��

		gotoxy(50, menu_y);
		printf("���O����͂��Ă�������");

		gotoxy(50, menu_y + 1);
		printf("(�p�����Ɛ������܂܂��15�����ȓ�)");

		gotoxy(40, menu_y + 3);
		printf("���O�F");

		//���͑҂�
		rewind(stdin);
		scanf("%s", player);


		//���O��郋�[������邩�m�F

		while (check_name(player) == -1 || strlen(player) > 15) {

			//�G���[���o��
			system("cls");
			effect();

			gotoxy(50, menu_y);
			printf("�����Ɠ��͂��Ă��������I");

			rewind(stdin);
			getchar();
			system("cls");

			//���̃A�X�L�[�A�[�g

			character_choice(15, y_coor, charChoice);

			//���O���͏���

			gotoxy(50, 15);
			printf("���O����͂��Ă�������");

			gotoxy(50, 16);
			printf("(�p�����Ɛ������܂܂��15�����ȓ�)");

			gotoxy(40, 18);
			printf("���O�F");

			//���͑҂�
			rewind(stdin);
			scanf("%s", player);
		}

		player_len = strlen(player);
		player[player_len] = '\n';
		player[player_len + 1] = '\0';

		//���͏���
		while (search(player) != -1) {
			system("cls");

			gotoxy(50, 15);
			printf("���̖��O�͑��̃v���C���[�Ɏg���Ă���I");

			gotoxy(50, 16);
			printf("�܂��V�������O������Ă��������I");

			rewind(stdin);
			getchar();
			system("cls");

			//���̃A�X�L�[�A�[�g
			character_choice(15, y_coor, charChoice);

			//���͏���

			gotoxy(50, 15);
			printf("���O����͂��Ă�������");

			gotoxy(50, 16);
			printf("(�p�����Ɛ������܂܂��15�����ȓ�)");

			gotoxy(50, 18);
			printf("���O�F");

			rewind(stdin);
			scanf("%s", player);
			player_len = strlen(player);
			player[player_len] = '\n';
			player[player_len + 1] = '\0';

		}


		//�L�����N�^�[�쐬
		unique = 0;
		for (int i = 0; i < player_len; i++) {
			unique = unique + player[i];

		}

		//�����_��
		srand(unique);
		strcpy((pplayer_data + count)->name, player);
		srand(unique + 1);
		(pplayer_data + count)->HP = rand() % 1000 + 500;
		srand(unique + 2);
		(pplayer_data + count)->ATK = rand() % 300 + 100;
		srand(unique + 3);
		(pplayer_data + count)->DEF = rand() % 100 + 1;

		(pplayer_data + count)->char_choice = charChoice;

		//�t�@�C���I�[�v��
		fpp = fopen("player_data.db", "wb");

		//�f�[�^�x�[�X��������
		for (int b = 0; b <= count; b++) {
			fwrite((pplayer_data + b), sizeof(STATUS), 1, fpp);
		}
		fclose(fpp);

		//============�������񂾂��m�点
		system("cls");
		setcursortype(NOCURSOR);
		//���̃A�X�L�[�A�[�g

		character_choice(15, y_coor, charChoice);

		//�쐬����

		gotoxy(50, 15);
		printf("�L�����N�^�[�쐬�����I");

		gotoxy(50, 16);
		printf("���̃L�����N�^�[���");

		gotoxy(50, 18);
		printf("���O�F%s", player);

		gotoxy(50, 19);
		printf("HP�F%d", (pplayer_data + (count))->HP);

		gotoxy(50, 20);
		printf("�U���́F%d", (pplayer_data + (count))->ATK);

		gotoxy(50, 21);
		printf("�h��́F%d", (pplayer_data + (count))->DEF);

		rewind(stdin);
		getchar();

		count++;
	}

	closesound(check_music);
	system("cls");
	start_battle(player);

}


//===============================�L�����N�^�[�̓ǂݍ���================================//

void load_player(void) {
	//�ϐ�

	char look[15];
	int look_len;

	//�f�[�^�ǂݍ���
	read_data();


	//���o����
	system("cls");


	//���y�𗬂�
	strcpy(path, "Uptown Sans.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	//���̃A�X�L�[�A�[�g

	shock_cat(15);

	//��ʕ\��

	gotoxy(50, 15);
	printf("���O����͂��Ă�������");

	gotoxy(45, 18);
	printf("���O�F");

	rewind(stdin);
	scanf("%s", look);
	look_len = strlen(look);
	look[look_len] = '\n';
	look[look_len + 1] = '\0';

	//���͏���
	while (search(look) == -1) {
		system("cls");

		gotoxy(50, 15);
		printf("���̃L�����N�^�[��������Ȃ��I");

		gotoxy(50, 16);
		printf("�܂����O�����Ă��������I");

		rewind(stdin);
		getchar();
		system("cls");

		//���̃A�X�L�[�A�[�g
		shock_cat(15);


		//���͏���

		gotoxy(50, 15);
		printf("���O����͂��Ă�������");

		gotoxy(45, 18);
		printf("���O�F");

		rewind(stdin);
		scanf("%s", look);
		look_len = strlen(look);
		look[look_len] = '\n';
		look[look_len + 1] = '\0';
	}


	system("cls");

	//�L�����N�^�[�̃A�X�L�[�A�[�g
	character_choice(15, 21, (pplayer_data + (search(look)))->char_choice);


	//�L�����N�^�[��ԕ\��
	setcursortype(NOCURSOR);

	gotoxy(50, 15);
	printf("�ǎ搬���I");

	gotoxy(50, 16);
	printf("���̃L�����N�^�[���");

	gotoxy(50, 18);
	printf("���O�F%s", look);

	gotoxy(50, 19);
	printf("HP�F%d", (pplayer_data + (search(look)))->HP);

	gotoxy(50, 20);
	printf("�U���́F%d", (pplayer_data + (search(look)))->ATK);

	gotoxy(50, 21);
	printf("�h��́F%d", (pplayer_data + (search(look)))->DEF);


	rewind(stdin);
	getchar();

	closesound(check_music);
	start_battle(look);

}


//===============================���j���[�\���ƑI���m�F================================//

void show_menu(void) {


	//�ϐ�
	int choice;
	int x, y;
	x = 48;
	y = menu_y;


	char menu[3][50] = { "�V�L�����N�^�[�쐬","�L�����N�^�[�ǎ�","�I��" };

	bool key_on = FALSE;

	strcpy(path, "Depacito_Fortnite.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	setcursortype(NOCURSOR);
	
	//���j���[�I��
	while (1) {

		

		//���j���[�\��


		//==========�Q�[�����O�̕\��==========//

		textcolor(1);

		gotoxy(40, 2);
		printf("���@�@�@���@�������@���@�@�@���@������");
		gotoxy(40, 3);
		printf("�����@�����@���@�@�@�����@�����@��");
		gotoxy(40, 4);
		printf("���@���@���@�������@���@���@���@������");
		gotoxy(40, 5);
		printf("���@�@�@���@���@�@�@���@�@�@���@��");
		gotoxy(40, 6);
		printf("���@�@�@���@�������@���@�@�@���@������");

		textcolor(5);

		gotoxy(31, 8);
		printf("������      ��    ������ ������ ��      ������  ������");
		gotoxy(31, 9);
		printf("��    ��  ��  ��    ��     ��   ��      ��      ��    ��");
		gotoxy(31, 10);
		printf("������    ������    ��     ��   ��      ������  ������");
		gotoxy(31, 11);
		printf("��    ��  ��  ��    ��     ��   ��      ��      ��  ��");
		gotoxy(31, 12);
		printf("������    ��  ��    ��     ��   ������  ������  ��    ��");

		textcolor(7);


		//==========���̉摜�\��==========//

		gotoxy(cat_x - 80, cat_y);
		printf("  ��@��,�Q�ȁ@�@��");

		gotoxy(cat_x - 80, cat_y + 1);
		printf("�@�@ ( �L��֥) ))");

		gotoxy(cat_x - 80, cat_y + 2);
		printf("�@(( (�@�@�R�A�@�@�@��");

		gotoxy(cat_x - 80, cat_y + 3);
		printf("�@�@�@�r �ƃm�@)))");

		gotoxy(cat_x - 80, cat_y + 4);
		printf("�@�@�i__�m^(�Q)");

		//==========�E�̉摜�\��==========//
		gotoxy(cat_x, cat_y);
		printf("�@�@�@�ȁQ,�ȁ@��");

		gotoxy(cat_x, cat_y + 1);
		printf("�@ (( (��֥` )");

		gotoxy(cat_x, cat_y + 2);
		printf("��@ /�@���@) ))�@��");

		gotoxy(cat_x, cat_y + 3);
		printf("�@�@((( �R�� �q");

		gotoxy(cat_x, cat_y + 4);
		printf("�@ (�Q)^�R__�j");

		//==========�Q�[���I��\��==========//
		gotoxy(50, menu_y);
		printf("%s", menu[0]);

		gotoxy(50, menu_y + 2);
		printf("%s", menu[1]);

		gotoxy(50, menu_y + 4);
		printf("%s", menu[2]);

		//�I���u���b�N
		gotoxy(x, y);
		printf("��");


		//�R���\�[�����͏���
		if (inport(PK_DOWN)) {
			if (key_on == false) {
				y = y + 2;
				key_on = true;
				system("cls");
			}
		}
		else if (inport(PK_UP)) {
			if (key_on == false) {
				y = y - 2;
				key_on = true;
				system("cls");
			}
		}
		else {
			key_on = false;
		}
		if (y > (menu_y + 4)) {
			y = menu_y;
			system("cls");
		}
		if (y < menu_y) {
			y = menu_y + 4;
			system("cls");
		}
		if (inport(PK_ENTER)) {
			reinport();
			system("cls");
			switch (y) {
			case menu_y:
				stopsound(check_music);
				effect();
				create_player();
				break;
			case menu_y + 2:
				stopsound(check_music);
				effect();
				load_player();
				break;
			case menu_y + 4:
				effect();
				exit(1);
			}
		}


	}

}



//======================================�f�[�^�ǂݍ��݊֐�==============================================//

void read_data(void) {

	//�ϐ�
	pplayer_data = player_data;

	FILE *fp;

	//�t�@�C���I�[�v��
	fp = fopen("player_data.db", "rb");


	if (fp == NULL) {
		SetCursorPos(50, 8);
		printf("�t�@�C���ǂݍ��݃G���[�I");
	}

	//�f�[�^�x�[�X�ǂݍ���
	count = 0;
	while (fread((pplayer_data + count), sizeof(STATUS), 1, fp) != NULL || count == PLAYER_NUM) {
		count++;
	}

	fclose(fp);
}



//==========�킢�n�܂�==========//

void start_battle(char player[15]) {
	//�ϐ�
	int player_location;
	int enemy_location;

	int playerNum;
	//�킢���n�܂�O

	player_location = search(player);

	system("cls");

	//�v���C���[�̉摜�\��

	character_choice(10, 20, (pplayer_data + player_location)->char_choice);

	//�v���C���[�̖��O�\��

	gotoxy(10, 22);
	printf("%s", (pplayer_data + player_location)->name);

	gotoxy(10, 24);
	printf("HP�F%d", (pplayer_data + player_location)->HP);

	gotoxy(10, 26);
	printf("�U���́F%d", (pplayer_data + player_location)->ATK);

	gotoxy(10, 28);
	printf("�h��́F%d", (pplayer_data + player_location)->DEF);


	//�f�[�^�������ēG�ƂȂ�
	playerNum = count - 1;

	srand(GetTickCount());
	enemy_location = rand() % playerNum + 1;



	//�G�̉摜�\��

	character_choice(95, 20, (pplayer_data + enemy_location)->char_choice);


	//�G�̖��O�\��

	gotoxy(95, 22);
	printf("%s", (pplayer_data + enemy_location)->name);

	gotoxy(95, 24);
	printf("HP�F%d", (pplayer_data + enemy_location)->HP);

	gotoxy(95, 26);
	printf("�U���́F%d", (pplayer_data + enemy_location)->ATK);

	gotoxy(95, 28);
	printf("�h��́F%d", (pplayer_data + enemy_location)->DEF);

	rewind(stdin);
	getchar();


	for (int a = 3; a > 0; a--) {
		system("cls");



		gotoxy(50, 14);
		textcolor(1);
		printf("�o�g���X�^�[�g");

		gotoxy(55, 15);
		textcolor(1);
		printf("����");

		gotoxy(56, 17);
		textcolor(4);
		printf("%d", a);

		Sleep(1000);
		effect();

	}
	effect2();

	system("cls");

	gotoxy(50, 15);
	textcolor(12);
	printf("�o�g���X�^�[�g�I");


	Sleep(2000);
	system("cls");
	textcolor(7);
	battle(player_location, enemy_location);
}

//==========�키���==========//
void battle(int player_location, int enemy_location) {
	//�ϐ�

	int y = 1;

	int player_HP;    //�v���C���[��HP�J�E���^�[
	int player_HP2;


	int enemy_HP;    //�G��HP�J�E���^�[
	int enemy_HP2;

	int round;
	int atk_miss;


	int check_bgm;     //����Ă��鎞��BGM
	char bgm_path[100];

	//������
	round = 0;

	player_HP = (player_data + player_location)->HP;
	player_HP2 = player_HP;
	enemy_HP = (player_data + enemy_location)->HP;
	enemy_HP2 = enemy_HP;

	//==========BGM����==========//
	strcpy(bgm_path, "Harry_Potter.mp3");
	check_bgm = opensound(bgm_path);
	playsound(check_bgm, 1);
	updatesound(check_bgm);


	while (player_HP != 0 && enemy_HP != 0) {



		gotoxy(50, 15);
		printf("�^�[�� %d", round + 1);

		rewind(stdin);
		getchar();
		system("cls");

		//==========�v���C���[�摜�\��==========//

		textcolor(1);

		character_choice(10, 22, (player_data + player_location)->char_choice);


		//==========�v���C���[�ɂ��Ă̕\��==========//


		gotoxy(10, 24);
		printf("%s", (pplayer_data + player_location)->name);    //�v���C���[�̖��O�\��

		gotoxy(10, 26);
		printf("�U���́F%d", (pplayer_data + player_location)->ATK);     //�v���C���[��ATK�\��

		gotoxy(10, 28);
		printf("�h��́F%d", (pplayer_data + player_location)->DEF);     //�v���C���[��DEF�\��


		//�v���C���[�̃w���X�o�[�\��(�u=�v��10�ł���)

		gotoxy(10, 14);
		printf("%d / %d", player_HP2, player_HP);    //�v���C���[��HP�\��

		for (int j = 0; j < check_HP(player_HP,player_HP); j++) {
			gotoxy(10 + j, 15);
			textbackground(4);
			printf(" ");
		}
		for (int j = 0; j < check_HP(player_HP2, player_HP); j++) {
			gotoxy(10 + j, 15);
			textbackground(2);
			printf(" ");
		}

		textbackground(0);




		//==========�G�摜�\��==========//

		textcolor(4);
		character_choice(95, 22, (player_data + enemy_location)->char_choice);
		

		//==========�G�ɂ��Ă̕\��==========//


		gotoxy(95, 24);
		printf("%s", (pplayer_data + enemy_location)->name);    //�G�̖��O�\��

		gotoxy(95, 26);
		printf("�U���́F%d", (pplayer_data + enemy_location)->ATK);     //�G��ATK�\��

		gotoxy(95, 28);
		printf("�h��́F%d", (pplayer_data + enemy_location)->DEF);     //�G��DEF�\��


		//�G�̃w���X�o�[�\��(�u=�v��10�ł���)
		gotoxy(95, 14);
		printf("%d / %d", enemy_HP2, enemy_HP);    //�G��HP�\��

		for (int j = 0; j < check_HP(enemy_HP, enemy_HP); j++) {
			gotoxy(95 + j, 15);
			textbackground(4);
			printf(" ");
		}
		for (int j = 0; j < check_HP(enemy_HP2, enemy_HP); j++) {
			gotoxy(95 + j, 15);
			textbackground(2);
			printf(" ");
		}

		textbackground(0);




		rewind(stdin);
		getchar();

		//==========�v���C���[�̍U��==========//

		textcolor(1);

		system("cls");
		punch1();
		effect();

		rewind(stdin);
		getchar();
		system("cls");

		srand(GetTickCount());


		atk_miss = rand() % 2 + 1;
		if (atk_miss == 1) {
			enemy_HP2 = enemy_HP2 - ((pplayer_data + player_location)->ATK - (pplayer_data + enemy_location)->DEF);


			gotoxy(50, 15);
			printf("�U�������I");

			gotoxy(50, 17);
			printf("�G��HP");

			if (enemy_HP2 <= 0) {
				gotoxy(50, 18);
				printf("%d -> %d", enemy_HP2 + ((pplayer_data + player_location)->ATK - (pplayer_data + enemy_location)->DEF), 0);
			}
			else {
				gotoxy(50, 18);
				printf("%d -> %d", enemy_HP2 + ((pplayer_data + player_location)->ATK - (pplayer_data + enemy_location)->DEF), enemy_HP2);
			}
		}
		if (atk_miss == 2) {

			gotoxy(50, 15);
			printf("�U�����s�I");

			gotoxy(50, 17);
			printf("�G��HP");

			gotoxy(50, 18);
			printf("%d -> %d", enemy_HP2, enemy_HP2);

		}
		rewind(stdin);
		getchar();

		//==========�G�̍U��==========//

		textcolor(4);

		system("cls");
		punch1();
		effect();

		rewind(stdin);
		getchar();
		system("cls");

		srand(GetTickCount());
		atk_miss = rand() % 2 + 1;

		if (atk_miss == 1) {
			player_HP2 = player_HP2 - ((pplayer_data + enemy_location)->ATK - (pplayer_data + player_location)->DEF);


			gotoxy(50, 15);
			printf("�G�U�������I");

			gotoxy(50, 17);
			printf("���Ȃ���HP");
			if (player_HP2 <= 0) {
				gotoxy(50, 18);
				printf("%d -> %d", player_HP2 + ((pplayer_data + enemy_location)->ATK - (pplayer_data + player_location)->DEF), 0);
			}
			else {
				gotoxy(50, 18);
				printf("%d -> %d", player_HP2 + ((pplayer_data + enemy_location)->ATK - (pplayer_data + player_location)->DEF), player_HP2);
			}
			rewind(stdin);
			getchar();
			system("cls");
		}
		if (atk_miss == 2) {

			gotoxy(50, 15);
			printf("�G�U�����s�I");

			gotoxy(50, 17);
			printf("���Ȃ���HP");

			gotoxy(50, 18);
			printf("%d -> %d", player_HP2, player_HP2);

			rewind(stdin);
			getchar();
			system("cls");
		}

		//==========�����m�F==========//
		if (player_HP2 <= 0) {
			stopsound(check_bgm);
			lose();
			break;
		}
		if (enemy_HP2 <= 0) {
			stopsound(check_bgm);
			victory();
			break;
		}

		//==========���̃^�[���ɐi��==========//
		round++;
	}

	rewind(stdin);
	getchar();

}

//==========��������==========//
void victory(void) {
	//�ϐ�


	//������ʕ\��
	system("cls");

	winBGM(1);

	//==========�摜�\��==========//

	textcolor(1);
	//�Q�Ă�̂ё�
	winScreen();


	gotoxy(10, 26);
	printf("�����������ă��j���[�ɖ߂�");

	//==========���j���[�ɖ߂�==========//
	rewind(stdin);
	getch();

	winBGM(1);
	textcolor(7);
	system("cls");
	show_menu();

}

//==========��������==========//

void lose(void) {
	//�ϐ�
	int isPush = 0;;
	


	//BGM�̗���
	loseBGM(1);

	//��ʕ\��
	textcolor(4);

	system("cls");

	loseScreen();

	do{
		gotoxy(10, 27);
		printf("F�������Čh���ă��j���[�ɖ߂�");
		if (inport(PK_F)) {
			isPush = 1;
		}

	}while (isPush==0);
	//==========���j���[�ɖ߂�==========//
	rewind(stdin);


	loseBGM(0);
	textcolor(7);
	system("cls");
	show_menu();
}


//======================���֐�================================//

//�����֐�
int search(char find[20]) {

	//�ϐ�
	int location;

	//���͂��ꂽ�����񏈗�

	//��������
	for (int j = 0; j <= count; j++) {
		if (strcmp(find, (pplayer_data + j)->name) == 0) {
			location = j;
			return location;

		}
	}
	return -1;
}

//���O���̃��[���`�F�b�N

int check_name(char check[15]) {
	//�ϐ�
	int have;
	have = 0;

	//����
	for (int i = 0; i < strlen(check); i++) {
		if ((check[i] > 65 && check[i] < 90) || (check[i] > 97 && check[i] < 122)) {
			have++;
		}
	}
	if (have > 0) {
		return 1;
	}
	else if (have == 0) {
		return -1;
	}


}


//HP�̊m�F

int check_HP(float hp, float original_HP) {

	//�ϐ�

	float gap;


	//����
	gap = original_HP / 10;

	while (hp != 0) {

		if (hp <= gap) {
			return 1;
			break;
		}

		if (hp <= gap * 2 && hp > gap) {
			return 2;
			break;
		}

		if (hp <= gap * 3 && hp > gap * 2) {
			return 3;
			break;
		}

		if (hp <= gap * 4 && hp >= gap * 3) {
			return 4;
			break;
		}

		if (hp <= gap * 5 && hp > gap * 4) {
			return 5;
			break;
		}

		if (hp <= gap * 6 && hp > gap * 5)
		{
			return 6;
			break;
		}

		if (hp <= gap * 7 && hp > gap * 6) {
			return 7;
			break;
		}

		if (hp <= gap * 8 && hp > gap * 7) {
			return 8;
			break;
		}

		if (hp <= gap * 9 && hp > gap * 8) {
			return 9;
			break;
		}

		if (hp <= gap * 10 && hp > gap * 9) {
			return 10;
			break;
		}

	}

	return 0;

}

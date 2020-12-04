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


//関数プロトタイプ

void show_menu(void);  //メニュー表示と選択
void read_data(void);  //プレイヤーデータの読み込み
void create_player(void);  //新しいキャラクターの作成
void load_player(void);  //作成したキャラクターの読取

void start_battle(char player[15]);  //戦い開始
void battle(int player_location, int enemy_location);  //戦いの時
void victory(void);  //勝った時のインターフェース
void lose(void);  //負けた時のインターフェース

//副関数プロトタイプ

int search(char find[15]);
int check_name(char check[15]);
int check_HP(float hp, float original_HP);

//構造体

//キャラクターの詳細
typedef struct {
	char name[15];
	int HP;
	int ATK;
	int DEF;
	int char_choice;
}STATUS;



//グローバル変数


//プレイヤーデータ
STATUS player_data[PLAYER_NUM];
STATUS *pplayer_data;

//プレイヤーデータカウンター
int count;



//音楽ファイル変数
int check_music;
char path[100];


//メイン関数
void main(void) {

	show_menu();     //メニュー表示
	system("pause");
}



//関数



//===============================キャラクターの作成================================//

void create_player(void) {
	//変数
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




	//プレイヤーデータの読み込み
	read_data();


	//音楽を流す
	strcpy(path, "Uptown Sans.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	//データベースにはデータが一つしかない時
	if (count < 1) {
		//画面表示
		setcursortype(NOCURSOR);

		system("cls");

		gotoxy(50, menu_y);
		printf("初めてこのゲームをするから、");

		gotoxy(50, menu_y + 2);
		printf("キャラクターは2つ作るしかない");

		rewind(stdin);
		getchar();
		system("cls");

		bool chooseChara = false;

		for (int s = 0; s < 2; s++) {

			setcursortype(NOCURSOR);

			while (!chooseChara) {

				gotoxy(50, 5);
				printf("キャラクターを選んでください");

				//キャラクター表示
				
				character1(5, y_coor);
				character2(35, y_coor);
				character3(65, y_coor);
				character4(95, y_coor);

				//選択ブロック
				chooseArrow(x, y + 2);

				//コンソール入力処理
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

			//左のアスキーアート
			
			character_choice(15, y_coor, charChoice);

			//入力処理

			setcursortype(NORMALCURSOR);

			gotoxy(50, menu_y);
			printf("キャラクター%dの名前を入力してください", s + 1);

			gotoxy(50, menu_y + 1);
			printf("(英文字と数字を含まれて15文字以内)");

			gotoxy(40, menu_y + 3);
			printf("名前：");

			//入力待ち
			rewind(stdin);
			scanf("%s", player);


			//名前作るルールを守るか確認

			while (check_name(player) == -1 || strlen(player) > 15) {


				system("cls");
				effect();

				//左のアスキーアート
				
				shock_cat(15);

				//エラーが出る

				gotoxy(50, menu_y);
				printf("ちゃんと入力してください！");

				rewind(stdin);
				getchar();
				system("cls");

				gotoxy(50, 15);
				printf("キャラクター%dの名前を入力してください", s);

				gotoxy(50, 16);
				printf("(英文字と数字を含まれて15文字以内)");

				gotoxy(40, 18);
				printf("名前：");

				//入力待ち
				rewind(stdin);
				scanf("%s", player);
			}

			player_len = strlen(player);
			player[player_len] = '\n';
			player[player_len + 1] = '\0';



			//キャラクター作成
			unique = 0;
			for (int i = 0; i < player_len; i++) {
				unique = unique + player[i];

			}

			//ランダム
			srand(unique);
			strcpy((pplayer_data + count)->name, player);
			srand(unique + 1);
			(pplayer_data + count)->HP = rand() % 1000 + 500;
			srand(unique + 2);
			(pplayer_data + count)->ATK = rand() % 300 + 100;
			srand(unique + 3);
			(pplayer_data + count)->DEF = rand() % 100 + 1;

			(pplayer_data + count)->char_choice = charChoice;


			//ファイルオープン
			fpp = fopen("player_data.db", "wb");

			//データベース書き込み

			fwrite((pplayer_data + (count + 1)), sizeof(STATUS), 1, fpp);
			fclose(fpp);

			//書き込んだお知らせ
			system("cls");
			setcursortype(NOCURSOR);
			//左のアスキーアート
			character_choice(15, y_coor, charChoice);

			//作成成功

			gotoxy(50, 15);
			printf("キャラクター%d作成成功！", s + 1);

			gotoxy(50, 16);
			printf("今のキャラクター状態");

			gotoxy(50, 18);
			printf("名前：%s", player);

			gotoxy(50, 19);
			printf("HP：%d", (pplayer_data + (count))->HP);

			gotoxy(50, 20);
			printf("攻撃力：%d", (pplayer_data + (count))->ATK);

			gotoxy(50, 21);
			printf("防御力：%d", (pplayer_data + (count))->DEF);


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
		printf("キャラクターを選んでください");

		//キャラクター表示

		character1(5, y_coor);
		character2(35, y_coor);
		character3(65, y_coor);
		character4(95, y_coor);

		//選択ブロック
		chooseArrow(x, y + 2);

		//コンソール入力処理
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
		


		//左のアスキーアート

		character_choice(15, y_coor, charChoice);

		setcursortype(NORMALCURSOR);

		//画面表示

		gotoxy(50, menu_y);
		printf("名前を入力してください");

		gotoxy(50, menu_y + 1);
		printf("(英文字と数字を含まれて15文字以内)");

		gotoxy(40, menu_y + 3);
		printf("名前：");

		//入力待ち
		rewind(stdin);
		scanf("%s", player);


		//名前作るルールを守るか確認

		while (check_name(player) == -1 || strlen(player) > 15) {

			//エラーが出る
			system("cls");
			effect();

			gotoxy(50, menu_y);
			printf("ちゃんと入力してください！");

			rewind(stdin);
			getchar();
			system("cls");

			//左のアスキーアート

			character_choice(15, y_coor, charChoice);

			//名前入力処理

			gotoxy(50, 15);
			printf("名前を入力してください");

			gotoxy(50, 16);
			printf("(英文字と数字を含まれて15文字以内)");

			gotoxy(40, 18);
			printf("名前：");

			//入力待ち
			rewind(stdin);
			scanf("%s", player);
		}

		player_len = strlen(player);
		player[player_len] = '\n';
		player[player_len + 1] = '\0';

		//入力処理
		while (search(player) != -1) {
			system("cls");

			gotoxy(50, 15);
			printf("この名前は他のプレイヤーに使われている！");

			gotoxy(50, 16);
			printf("また新しい名前を作ってください！");

			rewind(stdin);
			getchar();
			system("cls");

			//左のアスキーアート
			character_choice(15, y_coor, charChoice);

			//入力処理

			gotoxy(50, 15);
			printf("名前を入力してください");

			gotoxy(50, 16);
			printf("(英文字と数字を含まれて15文字以内)");

			gotoxy(50, 18);
			printf("名前：");

			rewind(stdin);
			scanf("%s", player);
			player_len = strlen(player);
			player[player_len] = '\n';
			player[player_len + 1] = '\0';

		}


		//キャラクター作成
		unique = 0;
		for (int i = 0; i < player_len; i++) {
			unique = unique + player[i];

		}

		//ランダム
		srand(unique);
		strcpy((pplayer_data + count)->name, player);
		srand(unique + 1);
		(pplayer_data + count)->HP = rand() % 1000 + 500;
		srand(unique + 2);
		(pplayer_data + count)->ATK = rand() % 300 + 100;
		srand(unique + 3);
		(pplayer_data + count)->DEF = rand() % 100 + 1;

		(pplayer_data + count)->char_choice = charChoice;

		//ファイルオープン
		fpp = fopen("player_data.db", "wb");

		//データベース書き込み
		for (int b = 0; b <= count; b++) {
			fwrite((pplayer_data + b), sizeof(STATUS), 1, fpp);
		}
		fclose(fpp);

		//============書き込んだお知らせ
		system("cls");
		setcursortype(NOCURSOR);
		//左のアスキーアート

		character_choice(15, y_coor, charChoice);

		//作成成功

		gotoxy(50, 15);
		printf("キャラクター作成成功！");

		gotoxy(50, 16);
		printf("今のキャラクター状態");

		gotoxy(50, 18);
		printf("名前：%s", player);

		gotoxy(50, 19);
		printf("HP：%d", (pplayer_data + (count))->HP);

		gotoxy(50, 20);
		printf("攻撃力：%d", (pplayer_data + (count))->ATK);

		gotoxy(50, 21);
		printf("防御力：%d", (pplayer_data + (count))->DEF);

		rewind(stdin);
		getchar();

		count++;
	}

	closesound(check_music);
	system("cls");
	start_battle(player);

}


//===============================キャラクターの読み込み================================//

void load_player(void) {
	//変数

	char look[15];
	int look_len;

	//データ読み込み
	read_data();


	//入出処理
	system("cls");


	//音楽を流す
	strcpy(path, "Uptown Sans.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	//左のアスキーアート

	shock_cat(15);

	//画面表示

	gotoxy(50, 15);
	printf("名前を入力してください");

	gotoxy(45, 18);
	printf("名前：");

	rewind(stdin);
	scanf("%s", look);
	look_len = strlen(look);
	look[look_len] = '\n';
	look[look_len + 1] = '\0';

	//入力処理
	while (search(look) == -1) {
		system("cls");

		gotoxy(50, 15);
		printf("このキャラクターが見つからない！");

		gotoxy(50, 16);
		printf("また名前を入れてください！");

		rewind(stdin);
		getchar();
		system("cls");

		//左のアスキーアート
		shock_cat(15);


		//入力処理

		gotoxy(50, 15);
		printf("名前を入力してください");

		gotoxy(45, 18);
		printf("名前：");

		rewind(stdin);
		scanf("%s", look);
		look_len = strlen(look);
		look[look_len] = '\n';
		look[look_len + 1] = '\0';
	}


	system("cls");

	//キャラクターのアスキーアート
	character_choice(15, 21, (pplayer_data + (search(look)))->char_choice);


	//キャラクター状態表示
	setcursortype(NOCURSOR);

	gotoxy(50, 15);
	printf("読取成功！");

	gotoxy(50, 16);
	printf("今のキャラクター状態");

	gotoxy(50, 18);
	printf("名前：%s", look);

	gotoxy(50, 19);
	printf("HP：%d", (pplayer_data + (search(look)))->HP);

	gotoxy(50, 20);
	printf("攻撃力：%d", (pplayer_data + (search(look)))->ATK);

	gotoxy(50, 21);
	printf("防御力：%d", (pplayer_data + (search(look)))->DEF);


	rewind(stdin);
	getchar();

	closesound(check_music);
	start_battle(look);

}


//===============================メニュー表示と選択確認================================//

void show_menu(void) {


	//変数
	int choice;
	int x, y;
	x = 48;
	y = menu_y;


	char menu[3][50] = { "新キャラクター作成","キャラクター読取","終了" };

	bool key_on = FALSE;

	strcpy(path, "Depacito_Fortnite.mp3");
	check_music = opensound(path);
	playsound(check_music, 1);

	setcursortype(NOCURSOR);
	
	//メニュー選択
	while (1) {

		

		//メニュー表す


		//==========ゲーム名前の表示==========//

		textcolor(1);

		gotoxy(40, 2);
		printf("■　　　■　■■■　■　　　■　■■■");
		gotoxy(40, 3);
		printf("■■　■■　■　　　■■　■■　■");
		gotoxy(40, 4);
		printf("■　■　■　■■■　■　■　■　■■■");
		gotoxy(40, 5);
		printf("■　　　■　■　　　■　　　■　■");
		gotoxy(40, 6);
		printf("■　　　■　■■■　■　　　■　■■■");

		textcolor(5);

		gotoxy(31, 8);
		printf("■■■      ■    ■■■ ■■■ ■      ■■■  ■■■");
		gotoxy(31, 9);
		printf("■    ■  ■  ■    ■     ■   ■      ■      ■    ■");
		gotoxy(31, 10);
		printf("■■■    ■■■    ■     ■   ■      ■■■  ■■■");
		gotoxy(31, 11);
		printf("■    ■  ■  ■    ■     ■   ■      ■      ■  ■");
		gotoxy(31, 12);
		printf("■■■    ■  ■    ■     ■   ■■■  ■■■  ■    ■");

		textcolor(7);


		//==========左の画像表示==========//

		gotoxy(cat_x - 80, cat_y);
		printf("  ♪　∧,＿∧　　♪");

		gotoxy(cat_x - 80, cat_y + 1);
		printf("　　 ( ´･ω･) ))");

		gotoxy(cat_x - 80, cat_y + 2);
		printf("　(( (　つ　ヽ、　　　♪");

		gotoxy(cat_x - 80, cat_y + 3);
		printf("　　　〉 とノ　)))");

		gotoxy(cat_x - 80, cat_y + 4);
		printf("　　（__ノ^(＿)");

		//==========右の画像表示==========//
		gotoxy(cat_x, cat_y);
		printf("　　　∧＿,∧　♪");

		gotoxy(cat_x, cat_y + 1);
		printf("　 (( (･ω･` )");

		gotoxy(cat_x, cat_y + 2);
		printf("♪　 /　⊂　) ))　♪");

		gotoxy(cat_x, cat_y + 3);
		printf("　　((( ヽつ 〈");

		gotoxy(cat_x, cat_y + 4);
		printf("　 (＿)^ヽ__）");

		//==========ゲーム選択表示==========//
		gotoxy(50, menu_y);
		printf("%s", menu[0]);

		gotoxy(50, menu_y + 2);
		printf("%s", menu[1]);

		gotoxy(50, menu_y + 4);
		printf("%s", menu[2]);

		//選択ブロック
		gotoxy(x, y);
		printf("→");


		//コンソール入力処理
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



//======================================データ読み込み関数==============================================//

void read_data(void) {

	//変数
	pplayer_data = player_data;

	FILE *fp;

	//ファイルオープン
	fp = fopen("player_data.db", "rb");


	if (fp == NULL) {
		SetCursorPos(50, 8);
		printf("ファイル読み込みエラー！");
	}

	//データベース読み込み
	count = 0;
	while (fread((pplayer_data + count), sizeof(STATUS), 1, fp) != NULL || count == PLAYER_NUM) {
		count++;
	}

	fclose(fp);
}



//==========戦い始まる==========//

void start_battle(char player[15]) {
	//変数
	int player_location;
	int enemy_location;

	int playerNum;
	//戦いが始まる前

	player_location = search(player);

	system("cls");

	//プレイヤーの画像表示

	character_choice(10, 20, (pplayer_data + player_location)->char_choice);

	//プレイヤーの名前表示

	gotoxy(10, 22);
	printf("%s", (pplayer_data + player_location)->name);

	gotoxy(10, 24);
	printf("HP：%d", (pplayer_data + player_location)->HP);

	gotoxy(10, 26);
	printf("攻撃力：%d", (pplayer_data + player_location)->ATK);

	gotoxy(10, 28);
	printf("防御力：%d", (pplayer_data + player_location)->DEF);


	//データから取って敵となる
	playerNum = count - 1;

	srand(GetTickCount());
	enemy_location = rand() % playerNum + 1;



	//敵の画像表示

	character_choice(95, 20, (pplayer_data + enemy_location)->char_choice);


	//敵の名前表示

	gotoxy(95, 22);
	printf("%s", (pplayer_data + enemy_location)->name);

	gotoxy(95, 24);
	printf("HP：%d", (pplayer_data + enemy_location)->HP);

	gotoxy(95, 26);
	printf("攻撃力：%d", (pplayer_data + enemy_location)->ATK);

	gotoxy(95, 28);
	printf("防御力：%d", (pplayer_data + enemy_location)->DEF);

	rewind(stdin);
	getchar();


	for (int a = 3; a > 0; a--) {
		system("cls");



		gotoxy(50, 14);
		textcolor(1);
		printf("バトルスタート");

		gotoxy(55, 15);
		textcolor(1);
		printf("あと");

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
	printf("バトルスタート！");


	Sleep(2000);
	system("cls");
	textcolor(7);
	battle(player_location, enemy_location);
}

//==========戦う画面==========//
void battle(int player_location, int enemy_location) {
	//変数

	int y = 1;

	int player_HP;    //プレイヤーのHPカウンター
	int player_HP2;


	int enemy_HP;    //敵のHPカウンター
	int enemy_HP2;

	int round;
	int atk_miss;


	int check_bgm;     //戦っている時のBGM
	char bgm_path[100];

	//初期化
	round = 0;

	player_HP = (player_data + player_location)->HP;
	player_HP2 = player_HP;
	enemy_HP = (player_data + enemy_location)->HP;
	enemy_HP2 = enemy_HP;

	//==========BGM流れ==========//
	strcpy(bgm_path, "Harry_Potter.mp3");
	check_bgm = opensound(bgm_path);
	playsound(check_bgm, 1);
	updatesound(check_bgm);


	while (player_HP != 0 && enemy_HP != 0) {



		gotoxy(50, 15);
		printf("ターン %d", round + 1);

		rewind(stdin);
		getchar();
		system("cls");

		//==========プレイヤー画像表示==========//

		textcolor(1);

		character_choice(10, 22, (player_data + player_location)->char_choice);


		//==========プレイヤーについての表示==========//


		gotoxy(10, 24);
		printf("%s", (pplayer_data + player_location)->name);    //プレイヤーの名前表示

		gotoxy(10, 26);
		printf("攻撃力：%d", (pplayer_data + player_location)->ATK);     //プレイヤーのATK表示

		gotoxy(10, 28);
		printf("防御力：%d", (pplayer_data + player_location)->DEF);     //プレイヤーのDEF表示


		//プレイヤーのヘルスバー表示(「=」は10個である)

		gotoxy(10, 14);
		printf("%d / %d", player_HP2, player_HP);    //プレイヤーのHP表示

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




		//==========敵画像表示==========//

		textcolor(4);
		character_choice(95, 22, (player_data + enemy_location)->char_choice);
		

		//==========敵についての表示==========//


		gotoxy(95, 24);
		printf("%s", (pplayer_data + enemy_location)->name);    //敵の名前表示

		gotoxy(95, 26);
		printf("攻撃力：%d", (pplayer_data + enemy_location)->ATK);     //敵のATK表示

		gotoxy(95, 28);
		printf("防御力：%d", (pplayer_data + enemy_location)->DEF);     //敵のDEF表示


		//敵のヘルスバー表示(「=」は10個である)
		gotoxy(95, 14);
		printf("%d / %d", enemy_HP2, enemy_HP);    //敵のHP表示

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

		//==========プレイヤーの攻撃==========//

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
			printf("攻撃成功！");

			gotoxy(50, 17);
			printf("敵のHP");

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
			printf("攻撃失敗！");

			gotoxy(50, 17);
			printf("敵のHP");

			gotoxy(50, 18);
			printf("%d -> %d", enemy_HP2, enemy_HP2);

		}
		rewind(stdin);
		getchar();

		//==========敵の攻撃==========//

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
			printf("敵攻撃成功！");

			gotoxy(50, 17);
			printf("あなたのHP");
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
			printf("敵攻撃失敗！");

			gotoxy(50, 17);
			printf("あなたのHP");

			gotoxy(50, 18);
			printf("%d -> %d", player_HP2, player_HP2);

			rewind(stdin);
			getchar();
			system("cls");
		}

		//==========勝負確認==========//
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

		//==========次のターンに進む==========//
		round++;
	}

	rewind(stdin);
	getchar();

}

//==========勝った時==========//
void victory(void) {
	//変数


	//勝利画面表示
	system("cls");

	winBGM(1);

	//==========画像表示==========//

	textcolor(1);
	//寝てるのび太
	winScreen();


	gotoxy(10, 26);
	printf("何かを押してメニューに戻る");

	//==========メニューに戻る==========//
	rewind(stdin);
	getch();

	winBGM(1);
	textcolor(7);
	system("cls");
	show_menu();

}

//==========負けた時==========//

void lose(void) {
	//変数
	int isPush = 0;;
	


	//BGMの流し
	loseBGM(1);

	//画面表示
	textcolor(4);

	system("cls");

	loseScreen();

	do{
		gotoxy(10, 27);
		printf("Fを押して敬ってメニューに戻る");
		if (inport(PK_F)) {
			isPush = 1;
		}

	}while (isPush==0);
	//==========メニューに戻る==========//
	rewind(stdin);


	loseBGM(0);
	textcolor(7);
	system("cls");
	show_menu();
}


//======================副関数================================//

//検索関数
int search(char find[20]) {

	//変数
	int location;

	//入力された文字列処理

	//検索処理
	for (int j = 0; j <= count; j++) {
		if (strcmp(find, (pplayer_data + j)->name) == 0) {
			location = j;
			return location;

		}
	}
	return -1;
}

//名前作りのルールチェック

int check_name(char check[15]) {
	//変数
	int have;
	have = 0;

	//処理
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


//HPの確認

int check_HP(float hp, float original_HP) {

	//変数

	float gap;


	//処理
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

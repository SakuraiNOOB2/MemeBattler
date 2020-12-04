#include <stdio.h>
#include <string.h>
#include "disp.h"

//====================================================================================================//
//===================ここの関数は全部画像表示処理やBGMについての関数分割ファイルです==================//
//====================================================================================================//





//==========エフェクト音==========//

void effect(void) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "big_oof.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	closesound(check_effect);
}

//戦い始まったところに流すBGM

void effect2(void) {
	int check_effect;
	char effect_path[100];
	strcpy(effect_path, "MLG_Horns.mp3");
	check_effect = opensound(effect_path);
	playsound(check_effect, 0);
	closesound(check_effect);
}


//負けた時のBGM

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

//勝った時のBGM

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




//======================画像表示処理================================//

//選択矢
void chooseArrow(int x, int y) {

	gotoxy(x, y);
	printf("  ●");

	gotoxy(x, y+1);
	printf("●●●");

	gotoxy(x, y + 2);
	printf("  ■");

	gotoxy(x, y + 3);
	printf("  ■");

}


//キャラクター読取の猫

void shock_cat(int x) {

	gotoxy(x, 13);
	printf("　　　　　　/つ_∧");

	gotoxy(x, 14);
	printf(" /つ_,∧ 〈（　ﾟдﾟ）");

	gotoxy(x, 15);
	printf(" |（　ﾟдﾟ） ヽ ⊂ニ)");

	gotoxy(x, 16);
	printf(" ヽ__と/￣￣￣/ |");

	gotoxy(x, 17);
	printf("￣＼/＿＿＿/");


}

//殴る
void punch1(void) {
	gotoxy(50, 15);
	printf("∧＿∧");
	gotoxy(50, 16);
	printf("・;'.、(・ω(:;(⊂＝⊂≡ ");
	gotoxy(50, 17);
	printf("(っΣ⊂≡⊂＝");
	gotoxy(50, 18);
	printf("/   ) ズバババ");
	gotoxy(50, 19);
	printf("( /￣∪");

}

//キャラクター

void character1(int x,int y) {

	gotoxy(10, y-5);
	printf(" 　　　∧");

	gotoxy(10, y-4);
	printf("　　/´｡ `ーァ");

	gotoxy(10, y-3);
	printf("　　{　 々 ﾟl´");

	gotoxy(10, y-2);
	printf("　／　っ　/っ");

	gotoxy(10, y-1);
	printf("/　　　 ／");

	gotoxy(10, y);
	printf("∪＾∪");

}

void character2(int x,int y) {

	gotoxy(x, y-5);
	printf("　　m9　三　9m");

	gotoxy(x, y-4);
	printf("　彡　　∧∧　　ミ");

	gotoxy(x, y-3);
	printf("m9　　(^Д^)　　9m　");

	gotoxy(x, y-2);
	printf("　ヾヽ＼　ｙ　 ）　彡");

	gotoxy(x, y-1);
	printf("　　m9／三　9m");

	gotoxy(x, y);
	printf("　　　∪￣￣￣＼)");

}

void character3(int x,int y) {

	gotoxy(x, y-4);
	printf("　　　∧ ∧");

	gotoxy(x, y-3);
	printf(" 　／(*ﾟーﾟ)　／＼");

	gotoxy(x, y-2);
	printf("／|￣∪∪￣|＼／");

	gotoxy(x, y-1);
	printf(" ヽ__と/￣￣￣/ |");

	gotoxy(x, y);
	printf(" 　|　 しぃ 　 |／");
}

void character4(int x,int y) {
	gotoxy(x, y-4);
	printf("　∧＿∧");

	gotoxy(x, y-3);
	printf(" (　^Д^)＝9m≡9m");

	gotoxy(x, y-2);
	printf(" (m9　≡m9＝m9");

	gotoxy(x, y-1);
	printf(" /　　　)");

	gotoxy(x, y);
	printf("( /￣∪");

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
	printf("　　　 　 ／ ´￣ ｀(＼ ");

	gotoxy(10, 16);
	printf("　　　　 /　 　 　 　 ＼-'､　　　　「無敵の人は寂しいなぁ・・・」 ");

	gotoxy(10, 17);
	printf("　　　　/　　　　　　　 ヽ　ヽ");

	gotoxy(10, 18);
	printf("　　　 _|　　　　　　　　 |　　|");

	gotoxy(10, 19);
	printf("　　　 ´!　　　　　　　 /　､／ ＾ ──- ､_ ");

	gotoxy(10, 20);
	printf("　　　　 ＼.__ _　　　 /　//（ ＿＿＿__/　｀ヽ");

	gotoxy(10, 21);
	printf("　　　／　（（（ j─ ´ヽ//　　　　　 /　 ＼)ﾉﾉ￣｀＼＿　　　／＾ヽ ");

	gotoxy(10, 22);
	printf("　　 (.　　　 ￣　　　　人.　　　　　i　　　|_＿＿_／ ＼|￣￣　　 ﾉ");

	gotoxy(10, 23);
	printf("　　 (￣￣￣￣　　／　 ｀ヽ､＿　 |　　 ´_|＿＿＼　　` ─ ､_.／ ");

	gotoxy(10, 24);
	printf("　　　￣￣￣￣￣　　　　　　　 ￣ ￣￣　　　　 （＿＿＿ノ");


}



void loseScreen(void) {

	gotoxy(10, 14);
	printf("　　　　　　　　　　　　/ヽ　　　　　　 /ヽ");

	gotoxy(10, 15);
	printf("　　　　　　　　　　　　/ 　ヽ　 　　　 / 　ヽ");

	gotoxy(10, 16);
	printf("　　＿＿＿＿＿＿ / 　 　 ヽ＿＿/　 　 　ヽ");

	gotoxy(10, 17);
	printf("　　|　＿＿＿＿　／　　　 　 　 　　　:::::::::::::::＼");

	gotoxy(10, 18);
	printf("　　| |　　　　　　 /／　　　　　　　＼　　:::::::::::::::|");

	gotoxy(10, 19);
	printf("　　| |　　　　　　 |　 ●　　　 　　● 　　 ::::::::::::::| 弱い人こそ俺に負ける");

	gotoxy(10, 20);
	printf("　　| |　　　　　　.|　　　　　　　　　　　　　:::::::::::::|");

	gotoxy(10, 21);
	printf("　　| |　　　　　　 |　 　（__人__丿 　.....:::::::::::::::::::/");

	gotoxy(10, 22);
	printf("　　| |＿＿＿＿　ヽ　　　　　　.....:::::::::::::::::::::::<");

	gotoxy(10, 23);
	printf("　 └＿＿＿／￣￣　　　　　　　:::::::::::::::::::::::::|");

	gotoxy(10, 24);
	printf("　　|＼　　　 |　　　　　　　　　　　　:::::::::::::::::::::::|");

	gotoxy(10, 25);
	printf("　　＼ ＼　　＼＿＿＿　　　　　　 ::::::::::::::::::::::::|");

}
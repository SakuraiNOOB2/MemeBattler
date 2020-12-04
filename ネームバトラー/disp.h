#pragma once
#define _DISP_H_
#define CONIOEX
#include "conioex.h"




//==========選択確認色==========//


//==========画像表示==========//
void punch1(void);
#define cat_x (90)
#define cat_y (18)
void shock_cat(int x);
void chooseArrow(int x, int y);


//キャラクター
void character1(int x,int y);
void character2(int x,int y);
void character3(int x,int y);
void character4(int x,int y);

void character_choice(int x,int y,int choice);


//勝負画像
void winScreen(void);
void loseScreen(void);


//==========サンドエフェクト==========//
void effect(void);
void effect2(void);
void loseBGM(int onOff);
void winBGM(int onOff);







//==========メニュー選択座標==========//
#define menu_x (50)
#define menu_y (18)
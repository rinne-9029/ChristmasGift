#include"GameData.h"

int GameData::Stage = GameData::A_1;		//初期スタートの家
bool GameData::ChengeStage = false;			//マップ移動フラグ
float GameData::BlueSleepSize = 300;
bool GameData::isGift = false;				//プレゼント設置フラグ

bool GameData::GameClearCheck = false;
bool GameData::GameOverCheck = false;
bool GameData::StartFadeIn = false;
bool GameData::StartFadeOut = false;

int GameData::second = 0;					//タイマー
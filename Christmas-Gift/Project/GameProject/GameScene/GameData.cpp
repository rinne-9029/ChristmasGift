#include"GameData.h"

int GameData::Stage = GameData::A_1;		//�����X�^�[�g�̉�
bool GameData::ChengeStage = false;			//�}�b�v�ړ��t���O
float GameData::BlueSleepSize = 300;
bool GameData::isGift = false;				//�v���[���g�ݒu�t���O

bool GameData::GameClearCheck = false;
bool GameData::GameOverCheck = false;
bool GameData::StartFadeIn = false;
bool GameData::StartFadeOut = false;

int GameData::second = 0;					//�^�C�}�[
#pragma once

class GameData
{
public:
	static enum StageId
	{
		A_1,		//A�̉Ƃ̕����P
		A_Child,	//A�̉Ƃ̎q������
		B_1,		//B�̉Ƃ̕����P
		B_2,		//B�̉Ƃ̕����Q
	};

	static int Stage;
	static bool Start;
	static bool ChengeStage;
	static float BlueSleepSize;		//�����Q�[�W�̃��[�^�[
	static bool isGift;				//�v���[���g�ݒu�t���O
	
	//�t���O
	static bool GameClearCheck;			//�Q�[���N���A�t���O
	static bool GameOverCheck;			//�Q�[���I�[�o�t���O

	//����
	static int second;					//�b��

};

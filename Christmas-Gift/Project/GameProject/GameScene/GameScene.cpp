#include"GameScene.h"
#include"Chara/Player/Player.h"
#include"Chara/Enemy/Enemy.h"
#include"Camera/Camera.h"
#include"Field/Field.h"
#include"Field/FieldObject/Closet.h"
#include"Field/FieldObject/Telephone.h"
#include"CollisionHitBox/MidPoint.h"
#include"CollisionHitBox/EndPoint.h"
#include"UI/SleepLife.h"
#include"UI/Timer.h"
#include"Result/GameClear.h"
#include"Result/GameOver.h"
#include"GameData.h"

//�R���X�g���N�^
GameScene::GameScene()
	:Task(ETaskTag::eScene,true)
{
	//�Q�[���󋵂̃��Z�b�g
	GameData::isGift = false;
	GameData::FacePosition = 340;
	GameData::GameClearCheck = false;
	GameData::GameOverCheck = false;
	GameData::second = 300;
	GameData::GameStart = true;

	//�t�F�[�h�C�����s
	GameData::StartFadeIn = true;

	//�X�e�[�W����
	//�e�L�X�g�f�[�^�ɂ���ăX�e�[�W���I�u�W�F�N�g���ω�
	new Field
	(
		"TextData/StageNode1.txt",		//�m�[�h
		"TextData/LightData1.txt",		//���C�g
		"TextData/DoorData1.txt",		//�h�A
		"TextData/SwitchData1.txt"		//�X�C�b�`
	);

	//�v���C���[����
	new Player
	(
		CVector3D(0, 0, 0),
		CVector3D(0, DtoR(180), 0),	
		CVector3D(0, 0, 0)
	);

	//�G�F���e����
	new Enemy
	(
		CVector3D(2.9, 0, 0.351914),
		CVector3D(-1, 0, 0),
		CVector3D(0.01, 0.01, 0.01),
		0
	);

	//�G�F��e����
	new Enemy
	(
		CVector3D(-2.073762, 9.891998, 1.103694),
		CVector3D(-1, 0, 0),
		CVector3D(0.01, 0.01, 0.01),
		1
	);


	new MidPoint
	(
		CVector3D(5.998150, 9.8, -1.6),
		CVector3D(0, 0, 0),
		CVector3D(1, 0.5, 1)
	);

	new EndPoint
	(
		CVector3D(4.555758, 0, 6.188184),
		CVector3D(0, 0, 0),
		CVector3D(1, 1, 1)
	);

	new Closet
	(
		CVector3D(3.261635, 9.053699, 4.970999),			//���W
		CVector3D(0, DtoR(270), 0),		//��]�l
		CVector3D(1, 0.7, 1),				//�I�u�W�F�N�g�̑傫��
		2
	);

	new Closet
	(
		CVector3D(0, 0, 0),			//���W
		CVector3D(0, DtoR(270), 0),		//��]�l
		CVector3D(1, 0.7, 1),				//�I�u�W�F�N�g�̑傫��
		2
	);

	//new Closet
	//(
	//	CVector3D(0.261635, 9.053699, 2.970999),			//���W
	//	CVector3D(0, DtoR(180), 0),		//��]�l
	//	CVector3D(1.2, 1.2, 2),				//�I�u�W�F�N�g�̑傫��
	//	2
	//);

	new SleepLife();			//�����Q�[�W
	new Timer();				//��������	

}

//�f�X�g���N�^
GameScene::~GameScene()
{
	//�Q�[���N���A�t���OOn
	if (GameData::GameClearCheck)
	{
		SOUND("SE_Walk")->Stop();
		SOUND("SE_Run")->Stop();
		//�N���A�V�[���ڍs
		new GameClear();
	}
	//�Q�[���I�[�o�[�t���OOn
	else if (GameData::GameOverCheck)
	{
		SOUND("SE_Walk")->Stop();
		SOUND("SE_Run")->Stop();
		//�Q�[���I�[�o�[�V�[���ڍs
		new GameOver();
	}
}

//�X�V����
void GameScene::Update()
{
	//5���o�߂ŃQ�[���I�[�o�[
	if (GameData::second < 0)
	{
		//�Q�[���I�[�o�[�t���OOn
		GameData::GameOverCheck = true;
		//�t�F�[�h�A�E�g���s
		GameData::StartFadeOut = true;
	}
}
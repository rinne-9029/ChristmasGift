#include"GameScene.h"
#include"Title/Title.h"
#include"Chara/Player/Player.h"
#include"Chara/Enemy/Enemy.h"
#include"Camera/Camera.h"
#include"Field/Field.h"
#include"Field/FieldObject/Closet.h"
#include"Field/FieldObject/Telephone.h"
#include"Field/FieldObject/Switch.h"
#include"Field/FieldObject/Door.h"
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
	GameData::BlueSleepSize = 300;
	GameData::GameClearCheck = false;
	GameData::GameOverCheck = false;
	GameData::second = 300;
	GameData::GameStart = true;

	//�t�F�[�h�C�����s
	GameData::StartFadeIn = true;
	

	FILE* fp = NULL;
	S_STATUS  character[] = { CVector3D(0,0,0) };
	int i;

	//	�Z�[�u�f�[�^���o�C�i���̓ǂݍ��݂ŃI�[�v��
	fopen_s(&fp, "SaveData.bin", "rb");

	//	�L�����N�^�[�̃X�e�[�^�X���t�@�C�����畜��(�L�����N�^�[:3�l)
	fread(character, sizeof(S_STATUS), sizeof(character) / sizeof(character[0]), fp);

	//�Q�[���X�^�[�g����A_1�X�e�[�W
	switch (GameData::Stage)
	{
		//�}�b�vA_1�̃V�[��
	case GameData::A_1:
		//�X�e�[�W
		new Field();

		//���r���O
		new Switch
		(
			CVector3D(1, 1.5, 7),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			0
		);

		//1�K�L���@
		new Switch
		(
			CVector3D(0, 1.5, 8),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			1
		);

		new Switch
		(
			CVector3D(0, 1.5, 14),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			1
		);

		//1�K�L���A
		new Switch
		(
			CVector3D(-3.0, 1.5, 7),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			2
		);

		//���ʏ�
		new Switch
		(
			CVector3D(-10, 1.5, 4.8),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			3
		);


		//1�K�K�i
		new Switch
		(
			CVector3D(-3, 2.4, 14),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			4
		);

		//2�K�K�i
		new Switch
		(
			CVector3D(-7, 10.5, 8.1),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			4
		);

		//2�K�L��
		new Switch
		(
			CVector3D(-6.5, 10.5, 7.7),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			5
		);

		//���e����
		new Switch
		(
			CVector3D(-0.5, 10.5, 5.3),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			6
		);

		//�q������
		new Switch
		(
			CVector3D(5, 10.5, 5.3),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			7
		);

		//�h�A
		//�P�K���u
		new Door
		(
			CVector3D(-2.5, 0, 10.2),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//����
		new Door
		(
			CVector3D(3.2, 0, 16.05),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//�P�K�g�C��
		new Door
		(
			CVector3D(-9.25, 0, 6),
			CVector3D(0, DtoR(90), 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//�Q�K�g�C��
		new Door
		(
			CVector3D(-11.1, 8.8, 14.65),
			CVector3D(0, DtoR(180), 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//�Q�K���u
		new Door
		(
			CVector3D(-8.05, 8.8, 5.3),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//���e����
		new Door
		(
			CVector3D(2, 8.8, 5.3),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//�q������
		new Door
		(
			CVector3D(7., 8.8, 5.3),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1),
			CVector3D(1, 2, 0.3)
		);

		//�J����
		new Camera
		(
			CVector3D(0, 1.5, 0),							//���W
			CVector3D(0, DtoR(180), 0)						//��]�l
		);

		//�T���^
		new Player
		(
			CVector3D(0, 0, 0),
			character[0].size//���f���T�C�Y
		);

		//���e
		new Enemy
		(
			CVector3D(2.9, 0, 0.351914),
			CVector3D(-1,0, 0),
			CVector3D(0.01,0.01,0.01),
			0
		);

		//��e
		/*new Enemy
		(
			CVector3D(-2.073762, 9.891998, 1.103694),
			CVector3D(-1, 0, 0),
			CVector3D(0.01, 0.01, 0.01),
			1
		);*/


		new MidPoint
		(
			CVector3D(5.998150, 9.8, -1.6),
			CVector3D(0, 0, 0),
			CVector3D(1, 0.5, 1)
		);

		//��
		/*new MidPoint
		(
			CVector3D(0, 0, 0),
			CVector3D(0, 0, 0),
			CVector3D(1, 0.5, 1)
		);*/

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

		//new Closet
		//(
		//	CVector3D(0.261635, 9.053699, 2.970999),			//���W
		//	CVector3D(0, DtoR(180), 0),		//��]�l
		//	CVector3D(1.2, 1.2, 2),				//�I�u�W�F�N�g�̑傫��
		//	2
		//);

		new SleepLife();			//�����Q�[�W
		new Timer();				//��������

		break;
	}
	
	fclose(fp);
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
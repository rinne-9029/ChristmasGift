#include"GameScene.h"
#include"Chara/Player/Player.h"
#include"Chara/Enemy/Enemy.h"
//#include"Chara/Enemy/EnemyManager.h"
#include"Camera/Camera.h"
#include"Field/Field.h"
#include"Field/FieldObject/Closet.h"
#include"Field/FieldObject/Telephone.h"
#include"Light/Light.h"
#include"CollisionHitBox/CollisionHitBox.h"
#include"Title/Title.h"
#include"Filta/Filta.h"
#include"CollisionHitBox/MidPoint.h"
#include"CollisionHitBox/EndPoint.h"
#include"Navigation/NavManager.h"
#include"UI/UI.h"
#include"GameData.h"

GameScene::GameScene()
	:Task(ETaskTag::eScene,true)
	,GameCount(0)
	,mp_filta(nullptr)
	,mp_player(nullptr)
{
	GameData::isGift = false;

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

		//�J����
		new Camera
		(
			CVector3D(0, 1.5, 0),							//���W
			CVector3D(0, DtoR(90), 0)						//��]�l
		);

		//�T���^
		new Player
		(
			CVector3D(0, 0, 0),
			character[0].size//���f���T�C�Y
		);

		//���̃v���[���g�ݒu�|�C���g
		/*new MidPoint
		(
			CVector3D(0, 0, 0),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1)
		);*/

		new MidPoint
		(
			CVector3D(5.998150, 10.053699, 0.179571),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1)
		);

		new EndPoint
		(
			CVector3D(4.555758, 0, 6.188184),
			CVector3D(0, 0, 0),
			CVector3D(1, 1, 1)
		);

		new Closet
		(
			CVector3D(-4.702046f, -0.589298f, 6.602628f),			//���W
			CVector3D(0, DtoR(180), 0),		//��]�l
			CVector3D(1.2, 1.2, 2),				//�I�u�W�F�N�g�̑傫��
			2
		);

		new Telephone
		(
			CVector3D(0.342562, 0.231580, 10.509188),	//���W
			CVector3D(0, DtoR(270), 0),					//��]�l
			CVector3D(3, 3, 3),							//�I�u�W�F�N�g�̑傫��
					//obb�̑傫��
			0
		);

		//new GimmickObject
		//(
		//	CVector3D(0.342562, 0.231580, 10.509188),	//���W
		//	CVector3D(0, DtoR(270), 0),					//��]�l
		//	CVector3D(3, 3, 3),							//�I�u�W�F�N�g�̑傫��
		//	//CVector3D(2,2,2),
		//	CVector3D(0.25,0.1,0.25),					//obb�̑傫��
		//	0											//�I�u�W�F�N�g�i���o�[
		//);

		//new GimmickObject
		//(
		//	CVector3D(3.342562, 1.231580, 4.7),	//���W
		//	CVector3D(0, DtoR(270), 0),							//��]�l
		//	CVector3D(0.25,0.25, 0.25),							//�I�u�W�F�N�g�̑傫��
		//	//CVector3D(2,2,2),
		//	CVector3D(0.125, 0.35, 0.25),					//obb�̑傫��
		//	1										//�I�u�W�F�N�g�i���o�[
		//);

		//new GimmickObject
		//(
		//	CVector3D(-4.702046f, -0.589298f, 8.002628f),			//���W
		//	CVector3D(0, DtoR(180), 0),		//��]�l
		//	CVector3D(1.2, 1.2, 2),				//�I�u�W�F�N�g�̑傫��
		//	CVector3D(0.8, 2, 0.8),			//�����蔻��T�C�Y
		//	2
		//);

		//�G�l�~�[
		/*new Enemy
		(
			CVector3D(15.687225, 0.420055, 4.950093),
			CVector3D(0.01,0.01,0.01)
		);*/

		//�N���[�[�b�g
		//new Closet
		//(
		//	CVector3D(-4.702046f, -1.589298f, 8.002628f),			//���W
		//	CVector3D(0, DtoR(180), 0),		//��]�l
		//	CVector3D(0.9, 3, 0.9)			//�����蔻��T�C�Y
		//);

		//new Closet
		//(
		//	CVector3D(0.8, -0.1, 19),
		//	CVector3D(0, DtoR(90), 0),
		//	CVector3D(0.9, 3, 0.9)
		//);

		//new Closet
		//(
		//	CVector3D(-18, -0.1, -19),
		//	CVector3D(0, DtoR(90), 0),
		//	CVector3D(0.9, 3, 0.9)
		//);

		/*new WarpRoomBox
		(
			CVector3D(5,0,0),
			CVector3D(0, 0, 0),
			CVector3D(1, 0.5, 0.5)
		);*/

		/*new WarpChildRoomBox
		(
			CVector3D(10, 0, 10),
			CVector3D(0, 0, 0),
			CVector3D(1, 2, 1)
		);*/

		new SleepLife();			//�����Q�[�W

		break;

	//�}�b�vA_�q�������̃V�[��
	//case GameData::A_Child:
	//			//�X�e�[�W
	//			//new ChildRoom();

	//			//�J����
	//			new Camera
	//			(
	//				CVector3D(0, 1.5, 0),
	//				CVector3D(0,DtoR(180),0)
	//			);

	//			//�T���^
	//			new Player
	//			(
	//				CVector3D(-30, 0, -30),			//���W
	//				CVector3D(0, DtoR(0), 0),		//��]�l
	//				CVector3D(0.01, 0.01, 0.01)		//���f���T�C�Y
	//			);

	//	break;

	//�}�b�vB_1�̃V�[��
	case GameData::B_1:
				//�X�e�[�W
				new Field();

				//�J����
				new Camera
				(
					CVector3D(0, 1.5, 0),
					CVector3D(0,DtoR(-125),0)
				);

				//�T���^
				new Player
				(
					CVector3D(34.5, 0, 30),			//���W
					CVector3D(0.01, 0.01, 0.01)		//���f���T�C�Y
				);

				//�G�l�~�[
				new Enemy
				(
					CVector3D(-30, 0, 30),
					CVector3D(0.01, 0.01, 0.01)
				);

				/*for (int i = 0; i < 4; i++)
				{
					new Closet
					(
						CVector3D(31 - 2 * i, -0.1, 31),
						CVector3D(0, DtoR(180), 0),
						CVector3D(0.9, 3, 0.9)
					);
				}
				

				for (int i = 0; i < 4; i++)
				{
					new Closet
					(
						CVector3D(31 - 2 * i, -0.1, 7),
						CVector3D(0, DtoR(0), 0),
						CVector3D(0.9, 3, 0.9)
					);
				}*/

				//���[�v�p�{�b�N�X
				/*new WarpRoomBox
				(
					CVector3D(34.5, 0, 30),
					CVector3D(0, 0, 0),
					CVector3D(1, 0.5, 0.5)
				);*/

				new SleepLife();			//�����Q�[�W
		break;
	
	//�}�b�vB_�Q�̃V�[��
	case GameData::B_2:
		//�X�e�[�W
		new Field();

		//�J����
		new Camera
		(
			CVector3D(0, 1.5, 0),
			CVector3D(0, DtoR(0), 0)
		);

		//�T���^
		new Player
		(
			CVector3D(34.5, 0, -42),			//���W
			CVector3D(0.01, 0.01, 0.01)		//���f���T�C�Y
		);

		//�G�l�~�[
		new Enemy
		(
			CVector3D(-30, 0, 30),
			CVector3D(0.01, 0.01, 0.01)
		);

		//�N���[�[�b�g
		//new Closet
		//(
		//	CVector3D(19, -0.1, 5.6),			//���W
		//	CVector3D(0, DtoR(180), 0),		//��]�l
		//	CVector3D(0.9, 3, 0.9)			//�����蔻��T�C�Y
		//);

		//new Closet
		//(
		//	CVector3D(-18, -0.1, -19),
		//	CVector3D(0, DtoR(90), 0),
		//	CVector3D(0.9, 3, 0.9)
		//);

		//new Closet
		//(
		//	CVector3D(-18, -0.1, -19),
		//	CVector3D(0, DtoR(90), 0),
		//	CVector3D(0.9, 3, 0.9)
		//);

		//���[�v�p�{�b�N�X
		/*new WarpRoomBox
		(
			CVector3D(34.5, 0, -42),
			CVector3D(0, 0, 0),
			CVector3D(1, 0.5, 0.5)
		);*/

		new SleepLife();			//�����Q�[�W
		break;
	}
	mp_player = dynamic_cast<Player*>(TaskManager::FindObject(ETaskTag::ePlayer));
	mp_filta = dynamic_cast<Filta*>(TaskManager::FindObject(ETaskTag::eFilta));
	//�t�F�[�h�C�����s
	mp_filta->m_FadeinCheck = true;
	
	fclose(fp);
}

GameScene::~GameScene()
{
	//�v���C���[�����Sor������ԂȂ�
	if (mp_player->m_CheckKill == true || GameData::isGift == true)
	{
		new Title();
	}
	else
	{
		new GameScene();
	}
	
}

void GameScene::Update()
{
	GameCount++;
	//�T���o�߂Ń^�C�g����ʂ�
	if (GameCount > 18000)
	{
		TaskManager::KillALL();
	}
}
#include"Player.h"
#include"Chara/Enemy/Enemy.h"
#include"Field/Field.h"
#include"Field/FieldObject/Closet.h"
#include"Filta/Filta.h"
#include"Field/FieldObject/GimmickObjectBase.h"
#include"Camera/Camera.h"
#include"Light/Light.h"
#include"Field/FieldObject/Switch.h"
#include"UI/SleepLife.h"
#include"UI/ToolTips.h"
#include"GameScene/GameScene.h"
#include"Navigation/NavNode.h"
#include"Navigation/NavManager.h"
#include"GameScene/GameData.h"

//�}�N��
#define JUMP 0.20f			//�W�����v��
#define WALK_SPEED 0.04f	//�ʏ�X�s�[�h
#define DOWN_SPEED 0.02f	//���Ⴊ�݃X�s�[�h
#define RUN_SPEED 0.07f		//����X�s�[�h


//�R���X�g���N�^
Player::Player(const CVector3D& pos, const CVector3D& scale)
	:CharaBase(ETaskTag::ePlayer, true)
	, mp_enemy(nullptr)
	, mp_camera(nullptr)
	, mp_filta(nullptr)
	, mp_sleeplife(nullptr)
	, mp_light(nullptr)
	, mp_switch(nullptr)
	, m_tooltips(nullptr)
	, key_ang(0.0f)				
	, m_hide(false)											
	, m_state(eState_Idle)		
{

	FILE* fp = NULL;

	//	�f�[�^���e�L�X�g�̓ǂݍ��݂ŃI�[�v��
	fopen_s(&fp, "PlayerData.txt", "r");
	if (!fp) return;

	char buf[256] = "";

	while (!feof(fp))
	{
		fgets(buf, 256, fp);
		CVector3D Pos(0, 0, 0);
		CVector3D Size(0, 0, 0);

		sscanf_s(buf, "%f %f %f %f %f %f", &Pos.x, &Pos.y, &Pos.z, &Size.x, &Size.y, &Size.z);

		m_pos = Pos;
		m_scale = Size;
	}

	fclose(fp);

	m_tooltips = new ToolTips();

	m_height = 1.9f;			//����
	m_rad = 0.3f;				//���a

	//�f�o�b�O�p
	m_lS = CVector3D(0, 0, 0);	//���C�̎n�_
	m_lE = CVector3D(0, 0, 0);	//���C�̏I�_

	//�v���C���[���f���ǂݍ���
	m_model = COPY_RESOURCE("Player", CModelA3M);

	//�v���C���[�ʒu�Ɍo�H�T���p�̃m�[�h���쐬
	m_navNode = new NavNode
	(
		m_pos + CVector3D(0.0f, 1.5f, 0.0f),
		NavNode::NodeType::Destination
	);
	//�m�[�h�̃J���[�I��(��)
	m_navNode->SetNodeColor(CVector3D(1.0f, 0.25f, 0.25f));
}

//�f�X�g���N�^
Player::~Player()
{
}

//�ʏ���
void Player::StateIdle()
{
	//�������x
	

	//�V�t�g�L�[����&&�ړ����Ă���
	if (HOLD(CInput::eButton6))
	{
		
	}

	//�X�y�[�X�{�^������
	if (PUSH(CInput::eButton5) /*&& m_isGround*/)
	{
		//���n�t���OOFF
		m_isGround = false;
		//�W�����v
		m_vec.y += JUMP;
	}

	//�R���g���[���{�^������
	if (PUSH(CInput::eButton7))
	{
		//���Ⴊ�݃A�j���[�V����
		m_model.ChangeAnimation((int)AnimId::Crouch);
		//���Ⴊ�ݏ�ԂɈڍs
		m_state = eState_Squat;
	}

}

//���Ⴊ�ݏ��
void Player::StateSquat()
{
	//���Ⴊ�݃X�s�[�h����
	m_movespeed = DOWN_SPEED;

	//�B���Ԃ̐؂�ւ�
	//if (m_hide) m_hide = false;

	//�R���g���[���{�^��
	if (PUSH(CInput::eButton7))
	{
		//�����A�j���[�V����
		m_model.ChangeAnimation((int)AnimId::Stand);
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}

//�n�C�h���
void Player::StateHide()
{
	//�{�^�����͂ő��n�C�h���������Ȃ��悤��
	static int count;
	count++;
	//�N���[�[�b�g�̒��S�Ɉړ�
	m_pos = m_Closet_pos;
	if (PUSH(CInput::eMouseL) && count >1)
	{
		//�J�E���g�̏�����
		count = 0;
		//���̈ʒu�֖߂�
		m_pos = m_copy_pos;
		//�n�C�h����
		m_hide = false;
		m_state = eState_Idle;
	}
}

//�X�V����
void Player::Update()
{
	//�G
	if (!mp_enemy) mp_enemy = dynamic_cast<Enemy*>(TaskManager::FindObject(ETaskTag::eEnemy));
	//�J����
	if (!mp_camera) mp_camera = dynamic_cast<Camera*>(TaskManager::FindObject(ETaskTag::eCamera));
	//�t�B���^�[
	if (!mp_filta) mp_filta = dynamic_cast<Filta*>(TaskManager::FindObject(ETaskTag::eFilta));
	//�����Q�[�W
	if (!mp_sleeplife) mp_sleeplife = dynamic_cast<SleepLife*>(TaskManager::FindObject(ETaskTag::eUI));
	//���C�g
	if (!mp_light)mp_light = dynamic_cast<Light*>(TaskManager::FindObject(ETaskTag::eFieldLight));
	//�X�C�b�`
	if (!mp_switch)mp_switch = dynamic_cast<Switch*>(TaskManager::FindObject(ETaskTag::eFieldObject));
	//���g�̌���
	CLight::SetType(1, CLight::eLight_Point);
	CLight::SetRange(1, 1.0f);
	CLight::SetColor(1, CVector3D(0, 0, 0), CVector3D(0.8, 0.8, 0.7));
	CLight::SetPos(1, m_pos + CVector3D(0, 1.0f, 0));

	Shot();

	//�J�������_
	//�����낵���_
	if (mp_camera->m_camera_mode == Camera::LookDownCamera)
	{
		//�L�[�����x�N�g���̊p�x�ŃL�����N�^�[�̊p�x�����܂�
		m_rot.y = Utility::NormalizeAngle(key_ang);
	}
	//��l�̎��_or�O�l�̎��_
	else
	{
		//�L�[���͂���ĂȂ���
		//�J�����̊p�x�ŃL�����N�^�[�̐��ʊp�x�����܂�
		m_rot.y = Utility::NormalizeAngle(mp_camera->m_rot.y + key_ang);
	}


	//�t�F�[�h�C���E�t�F�[�h�A�E�g���̓A�b�v�f�[�g���������Ȃ�
	if (GameData::StartFadeIn)return;
	if (GameData::StartFadeOut)return;

	//�L�[�����x�N�g�������Z�b�g
	CVector3D key_dir = CVector3D(0, 0, 0);

	//�n�C�h���̓L�[���͂��󂯕t���Ȃ�
	if (m_state != eState_Hide)
	{
		//���͂����L�[�����̃x�N�g����ݒ肷��
		if (HOLD(CInput::eUp)) key_dir.z = 1;
		if (HOLD(CInput::eDown))key_dir.z = -1;
		if (HOLD(CInput::eLeft))key_dir.x = 1;
		if (HOLD(CInput::eRight))key_dir.x = -1;
	

		//�L�[���͂��ꂽ��
		if (key_dir.LengthSq() > 0.1)
		{

			//�L�[�̕����x�N�g�����p�x�ɋt�Z����
			key_ang = atan2(key_dir.x, key_dir.z);

			//�����x�N�g��
			CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));

			//�ړ�
			m_pos += dir * m_movespeed;

			//�ʏ��ԂȂ�
			if (m_state == eState_Idle)
			{
				//�ʏ�������[�V����
				m_model.ChangeAnimation((int)AnimId::Walk);

				//�V�t�g�L�[����
				if (HOLD(CInput::eButton6))
				{
					//�_�b�V���ړ�
					m_movespeed = RUN_SPEED;
					//����������ԂȂ�
					if (SleepLife::m_REM) GameData::BlueSleepSize -= 2.0f;
					//�m������������ԂȂ�
					else GameData::BlueSleepSize -= 1.0f;

					//���艹���I������܂�
					if (SOUND("SE_Run")->CheckEnd())
					{
						//��������~
						SOUND("SE_Walk")->Stop();
						//���艹2�{��
						SOUND("SE_Run")->Pitch(2);
						//���艹�Đ�
						SOUND("SE_Run")->Play();
					}
				}
				else
				{
					m_movespeed = WALK_SPEED;

					//�������I������܂�
					if (SOUND("SE_Walk")->CheckEnd())
					{
						//���艹��~
						SOUND("SE_Run")->Stop();
						//������2�{��
						SOUND("SE_Walk")->Pitch(2);
						//�������Đ�
						SOUND("SE_Walk")->Play();
					}
				}
				
			}
			else
			{
				//���Ⴊ�ݕ���
				m_model.ChangeAnimation((int)AnimId::Crouchwalk);
			}
		}
		else
		{
			//�ҋ@�A�j���[�V����
			if (m_state == eState_Idle)
			{
				//�ʏ�ҋ@
				m_model.ChangeAnimation((int)AnimId::Idle);
				//��������~
				SOUND("SE_Walk")->Stop();
				SOUND("SE_Run")->Stop();
			}	
			else
			{
				//���Ⴊ�ݑҋ@
				m_model.ChangeAnimation((int)AnimId::Crouchidle);
				SOUND("SE_Walk")->Stop();
				SOUND("SE_Run")->Stop();
			}

		}
	}
	//�x�[�X�N���X�̍X�V
	CharaBase::Update();

	//�X�e�[�g��Ԃɂ���ԕω�
	switch (m_state) {
		//�ʏ탂�[�h
	case eState_Idle:
		StateIdle();
		break;
		//���Ⴊ�݃��[�h
	case eState_Squat:
		StateSquat();
		break;
		//�n�C�h���[�h
	case eState_Hide:
		StateHide();
		break;
	}

	if (m_state != eState_Squat)
	{
		m_navNode->m_pos = m_pos + CVector3D(0, 1.5, 0);
	}
	else
	{
		m_navNode->m_pos = m_pos + CVector3D(0, 0.5, 0);
	}

	NavNode* node = NavManager::Instance()->GetNearNavNode(m_navNode);

	//�A�j���[�V�����X�V
	m_model.UpdateAnimation();


	//�v���C���[�J�v�Z���̕\��
	//Utility::DrawCapsule(m_lineS, m_lineE, m_rad, CVector4D(1, 0, 0, 1));

	//�f�o�b�O�p:k�{�^���Ńv���C���[�̍��W��\���i�m�[�h�z�u�����p�j
	if (PUSH(CInput::eButton12))
	{
		printf("CVector3D(%f,%f,%f),\n", m_pos.x,m_pos.y+1,m_pos.z);
	}
}

//�`�揈��
void Player::Render()
{
	m_model.SetPos(m_pos);		//���W
	m_model.SetRot(m_rot);		//��]�l
	m_model.SetScale(m_scale);	//�傫��
	//�ȈՓI����
	//��l�̎����f����`�悵�Ȃ�
	if (mp_camera->m_camera_mode != Camera::FirstPersonCamera) {
		m_model.Render();
	}

	//�f�o�b�O�p:���C�̐���\��
	float a = 10000;
	Utility::DrawLine(m_lS, m_lE, CVector4D(1, 0, 0, 1), a);
}

//�Փˏ���
void Player::Collision(Task* t)
{
	CharaBase::Collision(t);

	switch (t->GetTag())
	{
	case ETaskTag::eEnemy:
	{
		//�v���C���[�ƓG�̔���
		CVector3D c1, dir1, c2, dir2;
		float dist;
		if (CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad,
			t->m_lineS, t->m_lineE, t->m_rad,
			&dist, &c1, &dir1, &c2, &dir2))
		{
				//�Q�[���I�[�o
				GameData::GameOverCheck = true;
				//�t�F�[�h�A�E�g���s
				GameData::StartFadeOut = true;
		}
	}
	break;
	case ETaskTag::eFieldObject:
	{
		float dist;
		CVector3D axis;
		if (CCollision::CollisionOBBCapsule(t->m_obb1, m_lineS, m_lineE, m_rad, &axis, &dist))
		{
			if (axis.y > 0.5f)
			{
				//�ʂ������->�n�ʂɓ�������
				//�d�͗������x��0�ɖ߂�
				if (m_vec.y < 0)
					m_vec.y = 0;
			}
			//�n�C�h�ȊO
			if (m_state != eState_Hide)
			{
				//�����߂�
				float s = m_rad - dist;
				m_pos += axis * s;
			}
		}
	}
	break;
	case ETaskTag::eDoor:
	{
		float dist;
		CVector3D axis;
		if (CCollision::CollisionOBBCapsule(t->m_obb1, m_lineS, m_lineE, m_rad, &axis, &dist))
		{
			if (axis.y > 0.5f)
			{
				//�ʂ������->�n�ʂɓ�������
				//�d�͗������x��0�ɖ߂�
				if (m_vec.y < 0)
					m_vec.y = 0;
			}
			//�����߂�
			float s = m_rad - dist;
			m_pos += axis * s;
		}
	}
	break;
	}
}

//���C�̏���
void Player::Shot()
{
	//���肷�郌�C�̋���
	const float range = 1.5f;
	CVector3D dir = CMatrix::MRotation(mp_camera->m_rot).GetFront();
	//���C�̎n�_
	CVector3D lineS = m_pos + mp_camera->m_pos;

	//���C�̏I�_
	CVector3D lineE = m_pos + mp_camera->m_pos + dir * range;

	//�ł��߂��I�u�W�F�N�g�ւ̋���
	float dist = FLT_MAX;
	//���C�Ƃ̏Փ˓_
	CVector3D hit_field_point;
	//�Փ˂����X�e�[�W�I�u�W�F�N�g
	Field* hit_field = nullptr;
	if (Field* f = dynamic_cast<Field*>(TaskManager::FindObject(ETaskTag::eField))) 
	{
		//�ڐG�ʂ̖@���i�g��Ȃ��j
		CVector3D n;
		if (f->GetColModel()->CollisionRay(&hit_field_point, &n, lineS, lineE))
		{
			//���ˈʒu����ڐG�ʂւ̋���
			dist = (hit_field_point - lineS).LengthSq();
			//�ڐG�����X�e�[�W���X�V
			hit_field = f;
		}
	}
	//�Փ˂����I�u�W�F�N�g
	GimmickObjectBase* hit_object = nullptr;
	//�S�I�u�W�F�N�g��T��
	auto list = TaskManager::FindObjects(ETaskTag::eFieldObject);
	for (auto t : list) 
	{
		if (GimmickObjectBase* o = dynamic_cast<GimmickObjectBase*>(t))
		{
			//���C�Ƃ̏Փ˒n�_
			CVector3D c;
			CVector3D n;
			//�e�̐����ŃI�u�W�F�N�g�Ƃ̔�����s��
			if(o->CollisionRay(lineS,lineE,&c,&n))
			{
				//���ˈʒu����ł��߂��I�u�W�F�N�g�𒲂ׂ�
				float l = (c - lineS).LengthSq();
					if (dist > l) 
					{
						dist = l;
							hit_object = o;
					}
			}
		}
		//�ڐG�����I�u�W�F�N�g��������ΒT������߂�
		if (hit_object != nullptr)	break;
			
	}
	//�ł��߂��I�u�W�F�N�g�ɓ�����
	if (hit_object)
	{
		//�c�[���`�b�v��\��
		m_tooltips->isDraw = true;
		
		//�������Ă���I�u�W�F�N�g�̃i���o�[�ɉ����ď�����ύX
		switch (hit_object->m_objectno)
		{
		case 0:
		{
			//���N���b�N�œG���W�߂�
			if (PUSH(CInput::eMouseL))
			{
				
			}
		}
		break;
		case 1:
		{	
			//���N���b�N�œd�C������
			if (PUSH(CInput::eMouseL)) 
			{
				if (mp_switch = dynamic_cast<Switch*>(hit_object))
				{
					auto lightlist = TaskManager::FindObjects(ETaskTag::eFieldLight);
					for (auto t : lightlist)
					{
						if (Light* l = dynamic_cast<Light*>(t))
						{
							if (l->m_islight && mp_switch->m_SwitchNo == l->m_roomNo)
							{
								l->m_islight = false;
							}
							else if (!l->m_islight && mp_switch->m_SwitchNo == l->m_roomNo)
							{
								l->m_islight = true;
							}
						}
					}
				}
			}
			
		}
		break;
		case 2:
		{
			//���N���b�N�ŉB���
			if (PUSH(CInput::eMouseL))
			{
				//�G�ꂽ�N���[�[�b�g�̍��W��ۑ�
				m_Closet_pos = hit_object->m_pos;

				//�G�ꂽ�N���[�[�b�g�̐��ʃx�N�g����ۑ�
				m_Closet_rot = hit_object->m_rot;

				if (PUSH(CInput::eMouseL))
				{
					//���ݒn�ۑ�
					m_copy_pos = m_pos;
					//�n�C�h��Ԃֈڍs
					m_hide = true;
					m_state = eState_Hide;

				}
			}
			
		}
		break;
		}
	}
	else
	{
		m_tooltips->isDraw = false;
	}
	m_lS = lineS;
	m_lE = lineE;
}
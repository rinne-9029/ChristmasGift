#include"Player.h"
#include"Field/Field.h"
#include"Field/FieldObject/Closet.h"
#include"Filta/Filta.h"
#include"Field/FieldObject/GimmickObjectBase.h"
#include"Camera/Camera.h"
#include"Light/Light.h"
#include"UI/UI.h"
#include"GameScene/GameScene.h"
#include"Navigation/NavNode.h"
#include"Navigation/NavManager.h"
#include"GameScene/GameData.h"


#define JUMP 0.30f			//�W�����v��
#define WALK_SPEED 0.10f	//�ʏ�X�s�[�h
#define DOWN_SPEED 0.05f	//���Ⴊ�݃X�s�[�h
#define RUN_SPEED 0.30f		//����X�s�[�h


//�R���X�g���N�^
Player::Player(const CVector3D& pos, const CVector3D& scale)
	:CharaBase(ETaskTag::ePlayer, true)
	, mp_camera(nullptr)
	, mp_filta(nullptr)
	, mp_sleeplife(nullptr)
	, mp_light(nullptr)
	, m_hide(false)
	, m_islegsound(false)
	, m_CheckKill(false)
	, key_ang(0.0f)
	, m_copy_pos(0, 0, 0)
	, m_HideCount(0)
	, m_HideAnim(false)
	, m_state(eState_Idle)
{
	m_pos = pos;				//�v���C���[�������W
	m_scale = scale;			//�v���C���[�傫��
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
		m_pos + CVector3D(0.0f, 1.0f, 0.0f),
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
	
	{
		//���C�g�ݒu�e�X�g
		//0�ԁ@������ 1�Ԏ��g�̌��� 2�`�����̌���
		//static int idx = 2;
		//if (PUSH(CInput::eMouseL) || PUSH(CInput::eMouseR)) {
		//	if (PUSH(CInput::eMouseL)) {
		//		//�X�|�b�g���C�g
		//		CLight::SetType(idx, CLight::eLight_Spot);
		//		//������
		//		CLight::SetDir(idx, CVector3D(0, -1, 0));
		//		//�͈͂�15��
		//		CLight::SetRadiationAngle(idx, DtoR(80.0f));
		//	}else {
		//		//�|�C���g���C�g(�S����)
		//		CLight::SetType(idx, CLight::eLight_Point);
		//	}
		//	//�������i�Ⴂ�ƌ��̓͂��͈͂��L���B�ǂ��ђʂ��Ȃ��悤�ɒ����j
		//	CLight::SetRange(idx, 4.0f);
		//	//�����̐F�i�A���r�G���g�A�f�B�t���[�Y�j
		//	CLight::SetColor(idx, CVector3D(0, 0, 0), CVector3D(1.0, 1.0, 0.9));
		//	//�����̈ʒu
		//	CLight::SetPos(idx, m_pos + CVector3D(0, 3.0f, 0));
		//	idx++;
		//}

		//���g�̌���
		CLight::SetType(1, CLight::eLight_Point);
		CLight::SetRange(1, 1.0f);
		CLight::SetColor(1, CVector3D(0, 0, 0), CVector3D(0.8, 0.8, 0.7));
		CLight::SetPos(1, m_pos + CVector3D(0, 1.0f, 0));
	}

	//�������x
	m_movespeed = WALK_SPEED;

	//�V�t�g�L�[����&&�ړ����Ă���
	if (HOLD(CInput::eButton6) && m_islegsound)
	{
		//�_�b�V���ړ�
		m_movespeed = RUN_SPEED;
		GameData::BlueSleepSize -= 1.0f;
	}

	//�X�y�[�X�{�^������
	if (PUSH(CInput::eButton5) && m_isGround)
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

	//�B���Ԃ̐؂�ւ�
	if (m_hide) m_hide = false;

}

//���Ⴊ�ݏ��
void Player::StateSquat()
{
	//���Ⴊ�݃X�s�[�h����
	m_movespeed = DOWN_SPEED;

	//�B���Ԃ̐؂�ւ�
	if (m_hide) m_hide = false;

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
	//�N���[�[�b�g�̒��S�Ɉړ�
	m_pos = m_Closet_pos;

	if (PUSH(CInput::eMouseL) && m_hide)
	{
		m_state = eState_Idle;
		m_pos = m_copy_pos;
	}
	//�B��Ă���
	m_hide = true;

	
}

//�X�V����
void Player::Update()
{
	//�J����
	if (!mp_camera) mp_camera = dynamic_cast<Camera*>(TaskManager::FindObject(ETaskTag::eCamera));
	//�t�B���^�[
	if (!mp_filta) mp_filta = dynamic_cast<Filta*>(TaskManager::FindObject(ETaskTag::eFilta));
	//�����Q�[�W
	if (!mp_sleeplife) mp_sleeplife = dynamic_cast<SleepLife*>(TaskManager::FindObject(ETaskTag::eUI));
	//���C�g
	if (!mp_light)mp_light = dynamic_cast<Light*>(TaskManager::FindObject(ETaskTag::eFieldLight));
	
	//�����蔻��
	m_lineS = m_pos + CVector3D(0, m_height - m_rad, 0);	//�n�_
	m_lineE = m_pos + CVector3D(0, m_rad, 0);				//�I�_

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
	if (mp_filta->m_FadeinCheck)return;
	if (mp_filta->m_FadeoutCheck)return;

	//���N���b�N�Ń��C���΂�
	if (PUSH(CInput::eMouseL))
	{
		Shot();
	}

	//�������łĂȂ�
	m_islegsound = false;

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
			//�������o�Ă���
			m_islegsound = true;

			//�L�[�̕����x�N�g�����p�x�ɋt�Z����
			key_ang = atan2(key_dir.x, key_dir.z);

			//�����x�N�g��
			CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));

			//�ړ�
			m_pos += dir * m_movespeed;

			//�ړ��A�j���[�V����
			if (m_state == eState_Idle)
			{
				//�ʏ����
				m_model.ChangeAnimation((int)AnimId::Walk);
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
			}	
			else
			{
				//���Ⴊ�ݑҋ@
				m_model.ChangeAnimation((int)AnimId::Crouchidle);
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

			//�t�F�[�h�A�E�g���I���������ɃQ�[���I��
			if (!mp_filta->m_FadeoutCheck && m_CheckKill)
			{
				GameData::BlueSleepSize = 300;
				TaskManager::KillALL();
			}

			//�ڐG������v���C���[���S
			m_CheckKill = true;

			//�t�F�[�h�A�E�g�����s
			mp_filta->m_FadeoutCheck = true;
		}
	}
	break;
	case ETaskTag::eFieldObject:
	{
		float dist;
		CVector3D axis;
		if (CCollision::CollisionOBBCapsule(t->m_obb, m_lineS, m_lineE, m_rad, &axis, &dist))
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
	}
}


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
	}
	//�ł��߂��I�u�W�F�N�g�ɓ�����
	if (hit_object)
	{
		//�������Ă���I�u�W�F�N�g�̃i���o�[�ɉ����ď�����ύX
		switch (hit_object->m_no)
		{
		case 0:
		{
			//����������
			printf("��b��ɓ�������\n");
		}
		break;
		case 1:
		{
			printf("�X�C�b�`�ɓ�������\n");
			//�d�C������
			auto lightlist = TaskManager::FindObjects(ETaskTag::eFieldLight);
			for (auto t : lightlist)
			{
				if (Light* l = dynamic_cast<Light*>(t))
				{
					switch (l->m_roomNo)
					{
					case ERoomNo::eKitchen_Dining_Room:
					{
						if (l->m_lightOn)
						{
							l->m_lightOn = false;
						}
						else
						{
							l->m_lightOn = true;
						}
					}
					break;
					case ERoomNo::eLiving_Room:
					{
						if (l->m_lightOn)
						{
							l->m_lightOn = false;
						}
						else
						{
							l->m_lightOn = true;
						}
					}
					break;
					}
				}
			}
		}
		break;
		case 2:
		{
			printf("�^���X�ɐG����\n");
			//�G�ꂽ�N���[�[�b�g�̍��W��ۑ�
			m_Closet_pos = hit_object->m_pos;

			//�G�ꂽ�N���[�[�b�g�̐��ʃx�N�g����ۑ�
			m_Closet_rot = hit_object->m_rot;

			if (PUSH(CInput::eMouseL) && !m_hide)
			{
				m_copy_pos = m_pos;
				//�n�C�h���
				//m_HideAnim = !m_HideAnim;
				m_state = eState_Hide;
			}
		}
		break;
		}
	}
	else if (hit_field)
	{
		//�������Ȃ�
		printf("�ǂɓ�������\n");
	}
	else
	{
		printf("�����������ĂȂ�\n");
	}
	m_lS = lineS;
	m_lE = lineE;
}
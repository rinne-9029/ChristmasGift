#include"Player.h"
#include"Field/Field.h"
#include"Field/Closet.h"
#include"Filta/Filta.h"
#include"Camera/Camera.h"
#include"UI/UI.h"
#include"GameScene/GameScene.h"
#include"Navigation/NavNode.h"
#include"Navigation/NavManager.h"
#include"GameScene/GameData.h"
#include"Debug/DebugPrint.h"
#include"Debug/DebugProfiler.h"

//�W�����v��
#define JUMP 0.30f

#define DownSpeed 0.20f

Player::Player(const CVector3D& pos, const CVector3D& scale)
	:CharaBase(ETaskTag::ePlayer)
	, mp_camera(nullptr)
	, mp_filta(nullptr)
	, mp_sleeplife(nullptr)
	, m_hide(false)
	, m_isFootFall(false)
	, m_CheckKill(false)
	, m_Speed(0)
	, key_ang(0.0f)
	, m_copy_pos(0, 0, 0)
	, m_HideCount(0)
	, m_HideAnim(false)
	, m_state(eState_Idle)
{
	m_remove = true;
	m_pos = pos;				//�v���C���[�������W
	m_scale = scale;			//�v���C���[�傫��
	m_height = 1.9f;			//����
	m_rad = 0.3f;				//���a

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

Player::~Player()
{
}

void Player::StateIdle()
{
	

	//�������x
	m_Speed = 0.15f;

	//�V�t�g�L�[����&&�ړ����Ă���
	if (HOLD(CInput::eButton6) && m_isFootFall)
	{
		//�_�b�V���ړ�
		m_Speed = 0.3f;
		GameData::BlueSleepSize -= 1.0f;
	}

	//�X�y�[�X�{�^������
	if (PUSH(CInput::eButton5) /*&& m_isGround*/)
	{
		//�W�����v���̃t���O
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

void Player::StateSquat()
{
	//���Ⴊ�݃X�s�[�h����
	m_Speed = 0.02f;

	//�B���Ԃ̐؂�ւ�
	if (m_hide) m_hide = false;

	//�R���g���[���{�^��
	if (PUSH(CInput::eButton7))
	{
		//�ʏ��Ԃֈڍs
		m_model.ChangeAnimation((int)AnimId::Stand);
		m_state = eState_Idle;
	}
}

void Player::StateHide()
{
	//�B��Ă���
	m_hide = true;

	m_pos = m_Closet_pos;

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

	//�����蔻��
	m_lineS = m_pos + CVector3D(0, m_height - m_rad, 0);
	m_lineE = m_pos + CVector3D(0, m_rad, 0);

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

	//�������łĂȂ�
	m_isFootFall = false;

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
			m_isFootFall = true;

			//�L�[�̕����x�N�g�����p�x�ɋt�Z����
			key_ang = atan2(key_dir.x, key_dir.z);

			//�����x�N�g��
			CVector3D dir(sin(m_rot.y), 0, cos(m_rot.y));

			//�ړ�
			m_pos += dir * m_Speed;

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

}

void Player::Collision(Task* t)
{
	//std::string name = "Collision";
	//DebugProfiler::StartTimer(name);
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
	case ETaskTag::eHideBox:
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
			//�G�ꂽ�N���[�[�b�g�̍��W��ۑ�
			m_Closet_pos = t->m_pos;

			//�G�ꂽ�N���[�[�b�g�̐��ʃx�N�g����ۑ�
			m_Closet_rot = t->m_rot;

			if (PUSH(CInput::eMouseL) && !m_hide)
			{
				m_copy_pos = m_pos;
				//�n�C�h���
				m_HideAnim = !m_HideAnim;
				m_state = eState_Hide;
			}
			else if (PUSH(CInput::eMouseL) && m_hide)
			{
				m_pos = m_copy_pos;
				m_state = eState_Idle;
			}
		}
	}
	break;
	}
	//DebugProfiler::EndTimer(name);
}
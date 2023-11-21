#include"Camera.h"
#include"../Chara/Player/Player.h"
#include"Field/Field.h"
#include"Field/Closet.h"

//�R���X�g���N�^
Camera::Camera(const CVector3D& pos, const CVector3D& rot)
	:ObjectBase(ETaskTag::eCamera)
	, mp_player(nullptr)
	, mp_closet(nullptr)
	, m_state(eState_Idle)
	, m_camera_mode(0)
{
	m_remove = true;
	m_pos = pos;
	m_rot = rot;
}

//�ʏ���
void Camera::StateIdle()
{
	if (mp_player->m_hide)
		m_state = eState_Hide;

	//�����낵���_���̓J�����Œ�
	if (m_camera_mode == LookDownCamera) return;

	//�J������]���x
	float cam_speed = 0.002f;

	//�}�E�X����ŉ�]
	CVector2D mouse_vec = CInput::GetMouseVec();

	//��]
	m_rot += CVector3D(mouse_vec.y, -mouse_vec.x, 0) * cam_speed;

	//�㉺�p�x����
	m_rot.x = min(DtoR(40), max(DtoR(-40), m_rot.x));

	
}

//�B�ꂽ���
void Camera::StateHide()
{
	//�J�����̌������N���[�[�b�g�̐��ʕ����ɕύX
	m_rot = mp_player->m_Closet_rot;

	//�ʏ��Ԃ̃J�����ɖ߂�
	if(!mp_player->m_hide)
		m_state = eState_Idle;
	
}

//�X�V����
void Camera::Update()
{
	if (!mp_player)
	{
		mp_player = dynamic_cast<Player*>(TaskManager::FindObject(ETaskTag::ePlayer));
	}
	if (!mp_closet)
	{
		mp_closet = dynamic_cast<Closet*>(TaskManager::FindObject(ETaskTag::eHideBox));
	}

	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Hide:
		StateHide();
		break;
	}

}

//�`�揈��
void Camera::Render()
{
	//�J�����̍��W
	CVector3D camera_pos[2] = {
		CVector3D(0,1.5,0),
		CVector3D(0,0.7,0),
	};

	static int idx;
	//ctrl�{�^�����������炵�Ⴊ�ݎ��_
	if (PUSH(CInput::eButton7)) {
		idx = (idx + 1) % 2;
	}
	//�������
	CVector3D cam_pos_target = camera_pos[idx] + CVector3D(0, 0, 0);
	m_pos = m_pos * 0.90f + cam_pos_target * 0.10f;

	//�J�����̃��[�h�ɉ����Ď��_�ύX

	switch (m_camera_mode)
	{
		//��l��
	case FirstPersonCamera:
	{
		CMatrix cam_matrix = CMatrix::MTranselate(mp_player->m_pos)					//character_matrix
			* CMatrix::MTranselate(m_pos) * CMatrix::MRotation(m_rot)				//branch_matrix
			* CMatrix::MTranselate(CVector3D(0, 0, -0.8));								//camera_matrix
			//�J�����ʒu���s��Őݒ�
		CCamera::GetCurrent()->SetTranseRot(cam_matrix);
		
		if (PUSH(CInput::eButton8))			//F�L�[����
		{
			m_camera_mode = LookDownCamera;	//�����낵�ɕύX
		}
	}
	break;
	//�����낵
	case LookDownCamera:
	{
		CMatrix cam_matrix = CMatrix::MTranselate(mp_player->m_pos)					//character_matrix
			* CMatrix::MTranselate(0, 20, 0) * CMatrix::MRotation(DtoR(90), 0, 0)	//branch_matrix
			* CMatrix::MTranselate(CVector3D(0, 0, 0));								//camera_matrix
			//�J�����ʒu���s��Őݒ�
		CCamera::GetCurrent()->SetTranseRot(cam_matrix);

		if (PUSH(CInput::eButton8))				//F�L�[����
		{
			m_camera_mode = ThirdPersonCamera;	//�O�l�̂ɕύX
		}
	}
	break;
	//�O�l�̎��_
	//�f�o�b�O�p
	case ThirdPersonCamera:
	{
		CMatrix cam_matrix = CMatrix::MTranselate(mp_player->m_pos)
			* CMatrix::MTranselate(CVector3D(0, 1.5, 0)) * CMatrix::MRotation(m_rot)
			* CMatrix::MTranselate(CVector3D(-0.5, 0.2, -2));
		//�J�����ʒu���s��Őݒ�
		CCamera::GetCurrent()->SetTranseRot(cam_matrix);

		if (PUSH(CInput::eButton8))				//F�L�[����
		{
			m_camera_mode = FirstPersonCamera;	//��l�̂ɕύX
		}
	}
	break;
	}


	
		

}
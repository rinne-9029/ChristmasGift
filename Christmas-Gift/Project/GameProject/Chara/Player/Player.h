#pragma once
#include"../CharaBase/CharaBase.h"

class Camera;
class Filta;
class SleepLife;
class Light;

class Player : public CharaBase {
public:
	bool m_hide;			//�X�e���X��ԃt���O
	bool m_islegsound;		//�����̃t���O
	bool m_CheckKill;		//�v���C���[���S�t���O

	CVector3D m_Closet_rot; //�J�����p�̃N���[�[�b�g�̐��ʕ����x�N�g��
	CVector3D m_Closet_pos;	//�N���[�[�b�g�����̍��W
private:
	Camera* mp_camera;		//�J����
	Filta* mp_filta;		//�t�B���^�[
	SleepLife* mp_sleeplife;//�����Q�[�W
	Light* mp_light;		//���C�g

	float key_ang;			//�����x�N�g���̊p�x
	CVector3D m_copy_pos;	//�^���X�ɓ���Ƃ��̃v���C���[�̍��W
	int m_HideCount;
	bool m_HideAnim;

	CModelA3M m_model;		//���f���f�[�^

	
	//�f�o�b�O�p
	CVector3D m_lS;
	CVector3D m_lE;

	//�A�j���[�V����ID
	enum class AnimId
	{
		Idle,				//�ҋ@
		Walk,				//����
		Crouch,				//���Ⴊ��
		Stand,				//����
		Crouchidle,			//���Ⴊ�ݑҋ@
		Crouchwalk,			//���Ⴊ�ݕ���
	};

	//��ԕω�
	enum {
		eState_Idle,		//�ʏ���
		eState_Squat,		//���Ⴊ�ݏ��
		eState_Hide,		//�B�ꂽ���
	};
	int m_state;			//�X�e�[�^�X���

	//�X�e�[�^�X�֐�
	//�ʏ���
	void StateIdle();
	//���Ⴊ�ݏ��
	void StateSquat();
	//�B�ꂽ���
	void StateHide();

public:
	//�R���X�g���N�^
	Player(const CVector3D& pos, const CVector3D& scale);

	//�f�X�g���N�^
	~Player();

	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	//�Փˏ���
	void Collision(Task* t);

	//���e�B�N��
	void Shot();
};
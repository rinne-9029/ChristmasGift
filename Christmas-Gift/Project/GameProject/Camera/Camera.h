#pragma once
#include"ObjectBase/ObjectBase.h"

class Player;
class Closet;

class Camera : public ObjectBase {
private:
	Player* mp_player;		//�v���C���[
	Closet* mp_closet;		//�A�C�e��
	int m_state;			//���݂̏��
	//��ԕω�
	enum {
		eState_Idle,		//�ʏ���
		eState_Hide,		//�B�ꂽ���
	};
public:
	int m_camera_mode;		//���݂̃J�����̃��[�h
	//�J�����̏��
	enum {
		FirstPersonCamera,	//��l��
		LookDownCamera,		//�����낵
		ThirdPersonCamera,	//�O�l��
	};
	//�ʏ���
	void StateIdle();
	//�B�ꂽ���
	void StateHide();		
public:
	//�R���X�g���N�^
	Camera(const CVector3D& pos, const CVector3D& rot);
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};
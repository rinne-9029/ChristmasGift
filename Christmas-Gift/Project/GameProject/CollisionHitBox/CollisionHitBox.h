#pragma once
#include"ObjectBase/ObjectBase.h"
//�����ړ��p�̉�ʂɌ����Ȃ������蔻��

class Filta;

class WarpRoomBox : public ObjectBase {
private:
	Filta* mp_filta;
	CVector3D m_size;		
public:
	//�R���X�g���N�^
	WarpRoomBox(const CVector3D& pos, const CVector3D& rot, const CVector3D& size);

	//�`�揈��
	void Render();

	//�Փˏ���
	void Collision(Task* t);
};

class WarpChildRoomBox : public ObjectBase {
private:
	CVector3D m_size;		//�傫��
public:
	//�R���X�g���N�^
	WarpChildRoomBox(const CVector3D& pos, const CVector3D& rot, const CVector3D& size);

	//�`�揈��
	void Render();

	//�Փˏ���
	void Collision(Task* t);

};



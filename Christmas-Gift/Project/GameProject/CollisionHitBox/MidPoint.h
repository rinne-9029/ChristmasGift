#pragma once
#include"CollisionBoxBase.h"

//�v���[���g�ݒu�p�t���OCollision

class MidPoint : public CollisionBoxBase {
private:
	CVector3D m_size;
public:
	//�R���X�g���N�^
	MidPoint(const CVector3D& pos, const CVector3D& rot, const CVector3D& size);

	//�Փˏ���
	void Collision(Task* t);
};
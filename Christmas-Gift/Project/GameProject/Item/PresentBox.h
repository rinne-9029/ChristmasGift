#pragma once
#include"ObjectBase/ObjectBase.h"

//�v���[���g�Ǘ��N���X

class PresentBox : public ObjectBase {
private:
	CModelObj m_model;
public:
	//�R���X�g���N�^
	PresentBox(const CVector3D& pos, const CVector3D& rot);

	//�`�揈��
	void Render();
};
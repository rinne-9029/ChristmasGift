#pragma once
#include"GimmickObjectBase.h"

//�X�C�b�`�Ǘ��N���X

class Switch : public GimmickObjectBase {
private:

public:
	int m_SwitchNo;
	//�R���X�g���N�^
	Switch(const CVector3D& pos, const CVector3D& rot, const CVector3D& size,int lightno);

	//�X�V����
	void Update();
};
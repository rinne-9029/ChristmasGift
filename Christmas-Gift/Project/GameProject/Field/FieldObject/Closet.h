#pragma once
#include"GimmickObjectBase.h"

//�N���[�[�b�g�Ǘ��N���X

class Closet : public GimmickObjectBase {
private:
	CVector3D m_size;		//���`�̑傫��
public:
	//�R���X�g���N�^
	Closet(const CVector3D& pos, const CVector3D& rot, const CVector3D& size,int no);

	//�X�V����
	void Update();
};
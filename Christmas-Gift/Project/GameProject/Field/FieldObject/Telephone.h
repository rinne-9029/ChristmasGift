#pragma once
#include"GimmickObjectBase.h"

class Telephone : public GimmickObjectBase {
private:

public:
	//�R���X�g���N�^
	Telephone(const CVector3D& pos, const CVector3D& rot, const CVector3D& size);

	//�X�V����
	void Update();
};
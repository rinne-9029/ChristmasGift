#pragma once
#include"ObjectBase/ObjectBase.h"

class GimmickObject : public ObjectBase
{
private:
	CVector3D m_size;		//�I�u�W�F�N�g�̑傫��
	CVector3D m_obbsize;	//obb�̑傫��
public:
	GimmickObject(CVector3D& pos,CVector3D& rot,CVector3D& size,CVector3D& obbsize,int no);
	~GimmickObject();
	void Update();
	void Render();
};
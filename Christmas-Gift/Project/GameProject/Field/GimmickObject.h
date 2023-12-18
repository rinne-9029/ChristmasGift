#pragma once
#include"GLLibrary/CModel.h"
#include"ObjectBase/ObjectBase.h"

class Light;

class GimmickObject : public ObjectBase
{
private:
	Light* mp_light;
	CVector3D m_size;		//�I�u�W�F�N�g�̑傫��
	CVector3D m_obbsize;	//obb�̑傫��
	CModel* m_obj;
public:
	GimmickObject(CVector3D& pos,CVector3D& rot,CVector3D& size,CVector3D& obbsize,int no);
	~GimmickObject();
	void Update();
	void Render();
	//int CollisionLine(const CVector3D& lineS, const CVector3D& const lineE, CVector3D& dir,CVector3D* cross);
	bool CollisionRay(const CVector3D& start, const CVector3D& end, CVector3D* outHitPos, CVector3D* outHitNormal);
};
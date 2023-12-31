#include"Field/FieldObject/GimmickObjectBase.h"

GimmickObjectBase::GimmickObjectBase(const CVector3D& pos,const CVector3D& rot,const CVector3D& size,int no, ETaskTag tag,bool remove)
	:ObjectBase(ETaskTag::eFieldObject,true)
{
	m_pos = pos;	//座標
	m_rot = rot;	//回転値
	m_size = size;	//大きさ
	m_no = no;
}

GimmickObjectBase::~GimmickObjectBase()
{

}

void GimmickObjectBase::Update()
{
	
}

void GimmickObjectBase::Render()
{
	m_model->SetPos(m_pos);
	m_model->SetRot(m_rot);
	m_model->SetScale(m_size);
	m_model->Render();
}

bool GimmickObjectBase::CollisionRay(const CVector3D& start, const CVector3D& end, CVector3D* outHitPos, CVector3D* outHitNormal)
{
	if (m_model == nullptr) return false;

	return m_model->CollisionRay(outHitPos, outHitNormal, start, end);
}
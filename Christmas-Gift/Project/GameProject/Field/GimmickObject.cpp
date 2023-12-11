#include"Field/GimmickObject.h"

GimmickObject::GimmickObject(CVector3D& pos,CVector3D& rot,CVector3D& size,CVector3D& obbsize, int no)
	:ObjectBase(ETaskTag::eField,true)
{
	mp_light = dynamic_cast<Light*>(TaskManager::FindObject(ETaskTag::eFieldLight));
	m_pos = pos;	//���W
	m_rot = rot;	//��]�l
	m_size = size;	//�傫��
	m_obbsize = obbsize;	
	m_obb = COBB
	(
		m_pos,
		m_rot,
		m_obbsize
	);
	//�i���o�[�ɉ����ĕ`�悷��I�u�W�F�N�g�ύX
	switch (no)
	{
	case 0:
		m_model = COPY_RESOURCE("Telephone", CModelObj);
		break;
	}

}

GimmickObject::~GimmickObject()
{

}

void GimmickObject::Update()
{

}

void GimmickObject::Render()
{
	m_model.SetPos(m_pos);
	m_model.SetRot(m_rot);
	m_model.SetScale(m_size);
	m_model.Render();
	Utility::DrawOBB(m_obb, CVector4D(1, 0, 0, 1));
}
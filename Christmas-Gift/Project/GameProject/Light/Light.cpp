#include "Light.h"

//�R���X�g���N�^
Light::Light(CVector3D& pos,int no,ERoomNo roomno)
	:ObjectBase(ETaskTag::eFieldLight,true)
	,m_lightOn(true)
	,m_roomNo(roomno)
	,m_no(no)
{
	m_pos = pos;
}

//�f�X�g���N�^
Light::~Light()
{
	
}

//�X�V����
void Light::Update()
{
	//�|�C���g���C�g(�S����)
	CLight::SetType(m_no, CLight::eLight_Point);
	CLight::SetRange(m_no, 5.0f);
	CLight::SetPos(m_no, m_pos);
	//���C�g�����Ă��鎞
	if (m_lightOn)
	{
		CLight::SetColor(m_no, CVector3D(0, 0, 0), CVector3D(1.0, 1.0, 0.9));
	}
	//���C�g�������Ă��鎞
	else
	{
		CLight::SetColor(m_no, CVector3D(0, 0, 0), CVector3D(0.1, 0.1, 0.1));
	}
	
}
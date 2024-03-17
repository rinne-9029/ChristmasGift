#pragma once
#include"ObjectBase/ObjectBase.h"

//���C�g�Ǘ��N���X

class Light : public ObjectBase
{
private:
	int m_no;			//�d�C���Ƃ̔ԍ�
	float m_range;		//���̋���
	int m_type;			//���̎��
public:
	int m_roomNo;		//�d�C�̂��Ă��镔���ԍ�
	bool m_islight;		//�d�C��On,Off
	Light::Light(CVector3D& pos,int no,int roomno,float range, int light,bool islight);
	Light::~Light();
	void Update();
};


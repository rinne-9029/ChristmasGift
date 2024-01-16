#pragma once
#include"ObjectBase/ObjectBase.h"

class Light : public ObjectBase
{
private:
	int m_no;			//�d�C���Ƃ̔ԍ�
public:
	int m_roomNo;		//�d�C�̂��Ă��镔���ԍ�
	bool m_islight;		//�d�C��On,Off
	Light::Light(CVector3D& pos,int no,int roomno,bool islight);
	Light::~Light();
	void Update();
};


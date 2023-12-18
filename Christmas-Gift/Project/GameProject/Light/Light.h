#pragma once
#include"ObjectBase/ObjectBase.h"

//�����ԍ�
enum class ERoomNo
{
	eKitchen_Dining_Room,
	eLiving_Room
};

class Light : public ObjectBase
{
private:
	int m_no;			//�d�C���Ƃ̔ԍ�
public:
	ERoomNo m_roomNo;		//�d�C�̂��Ă��镔���ԍ�
	bool m_lightOn;		//�d�C��On,Off
	Light::Light(CVector3D& pos,int no,ERoomNo roomno);
	Light::~Light();
	void Update();
};


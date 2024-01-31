#pragma once
#include"ObjectBase/ObjectBase.h"

class Filta : public Task
{
private:
	CImage m_filta;		//�t�B���^�[
	float m_alpha;		//�s�����x
	float m_time;
	
	void Fadein();
	void Fadeout();
public:
	//�R���X�g���N�^
	Filta();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
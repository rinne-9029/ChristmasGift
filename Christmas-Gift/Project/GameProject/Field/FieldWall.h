#pragma once
#include"ObjectBase/ObjectBase.h"

class FieldWall : public ObjectBase
{
private:
	
public:
	///<summary>
	///�R���X�g���N�^
	///</summary>
	FieldWall();
	///<summary>
	///�X�V����
	///</summary>
	void Update();
	///<summary>
	///�`�揈��
	///</summary>
	void Render();

	CModel* GetModel()
	{
		return &m_model;
	}
};
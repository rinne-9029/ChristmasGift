#pragma once
#include"ObjectBase/ObjectBase.h"

//�X�e�[�W�̏��Ǘ��N���X

class FieldFloor : public ObjectBase
{
private:
	CModelObj m_model;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FieldFloor();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	CModel* GetModel() {
		return &m_model;
	}
};
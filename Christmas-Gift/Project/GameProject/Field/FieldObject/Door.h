#pragma once
#include"GimmickObjectBase.h"
#include"UI/ToolTips.h"

class Door : public Task {
private:
	CModelObj m_model;
	bool m_isopen;
	CVector3D m_scale;
	CVector3D m_obbscale;
	ToolTips* m_tooltips;
public:
	//�R���X�g���N�^
	Door(const CVector3D& pos,const CVector3D& rot,const CVector3D& scale,const CVector3D& obbscale);

	//�X�V����
	void Update();

	//�`�揈��
	void Render();

	//�Փˏ���
	void Collision(Task* t);
};
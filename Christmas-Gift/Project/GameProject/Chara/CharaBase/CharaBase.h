#pragma once
#include"ObjectBase/ObjectBase.h"

//�L�����N�^�[�̃x�[�X�N���X

//�d�͉����x
#define GRAVITY (0.02f)

class NavNode;

class CharaBase : public ObjectBase
{
protected:
	NavNode* m_navNode;
	bool m_isGround;		//���n�t���O
	CVector3D m_scale;		//�L�����N�^�[�`��T�C�Y
	float m_movespeed;		//�ړ����x
public:
	
	//�R���X�g���N�^
	CharaBase(ETaskTag tag,bool remove);

	//�f�X�g���N�^
	virtual ~CharaBase();

	//�Փ˔���
	void Collision(Task* t);

	NavNode* GetNavNode() const;

	//�X�V
	void Update();
};

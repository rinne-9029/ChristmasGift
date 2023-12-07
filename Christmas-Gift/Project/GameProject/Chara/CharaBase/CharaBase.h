#pragma once
#include"ObjectBase/ObjectBase.h"
class NavNode;

//�d�͉����x
#define GRAVITY (0.02f)

//�L�����N�^�[�̃x�[�X�N���X
class CharaBase : public ObjectBase
{
protected:
	NavNode* m_navNode;
	bool m_isGround;		//���n�t���O
	CVector3D m_scale;		//�L�����N�^�[�`��T�C�Y
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

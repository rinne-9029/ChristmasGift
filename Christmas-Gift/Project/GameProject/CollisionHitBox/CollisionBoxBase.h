#pragma once

//�A�N�V�����p�����蔻��̃x�[�X

class CollisionBoxBase : public Task
{
public:
	//�R���X�g���N�^
	CollisionBoxBase(ETaskTag tag,bool remove);

	virtual ~CollisionBoxBase();
	//�`�揈��
	void Render();
};
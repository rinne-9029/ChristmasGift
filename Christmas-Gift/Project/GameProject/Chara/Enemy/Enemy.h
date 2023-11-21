#pragma once
#include"../CharaBase/CharaBase.h"

class Player;
class NavNode;
class SearchNode;

//�G����N���X

//�Ƒ�
class Enemy : public CharaBase {
private:
	CModelA3M m_model;
	Player* mp_player;			//�v���C���[
	CVector3D m_moveDir;		//�ړ�����
	CVector3D m_rot_target;		//�v���C���[�����̉�]�l
	CVector3D m_movePos;		//�ړ���̍��W
	NavNode* m_moveNode;		//�ړ��ړI�n�̃m�[�h
	float m_elapsedTime;		//�o�ߎ��Ԍv���p
	
	//��
	float eye_length;			//���싗��
	float eye_ang;				//����p�x

	//��
	float ear_length;			//���o����
	float ear_ang;				//���o�p�x

	bool m_isChasing;			//�ǐՒ��̃t���O
	NavNode* m_nextNode;		//���Ɉړ�����m�[�h�i�[�p
	NavNode* m_lostNode;		//�v���C���[�����������ꏊ�ɔz�u
	SearchNode* m_searchNode;	//�T�����̃m�[�h

	CVector4D color;			//����͈͂̐F

	int m_cnt;					//�^�C�}�[

	//�A�j���[�V�����ԍ�
	enum class AnimId
	{
		Idle,	//�ҋ@
		Walk,	//�ړ�
	};
	
	//��ԕω�
	enum {
		eState_Idle,			//�ҋ@���
		eState_Move,			//�ړ����
		eState_Chase,			//�ǐՏ��
		eState_Lost,			//�v���C���[�������������
	};

	int m_state;	//���݂̏��

	//�ʏ���
	void StateIdle();	
	//�ړ����
	void StateMove();		
	//�ǐՏ��
	void StateChase();	
	//�v���C���[�������������
	void StateLost();

	//��Ԃ��Ƃ̎���͈͂̐F
	void View_Color();

	//�w����W�ւ̈ړ�����
	bool MoveTo(const CVector3D& target);

	//�T�m�t���O
	bool IsEyeFoundPlayer();
	bool IsEarFoundPlayer();

	//���݈ʒu����v���C���[�������邩�ǂ����̃t���O
	bool IsLookPlayer() const;
public:
	//�R���X�g���N�^
	Enemy(const CVector3D& pos, const CVector3D& scale);
	//�f�X�g���N�^
	~Enemy();

	//�T���m�[�h��ݒ�
	void SetSearchNode(SearchNode* node);
	//�T�����̃m�[�h���擾
	SearchNode* GetSearchNode() const;
	
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�ڐG����
	void Collision(Task* t);

};

class Child : public CharaBase
{
private:
public:
	//�R���X�g���N�^
	Child(const CVector3D& pos,const CVector3D& vec);

	//�f�X�g���N�^
	~Child();

	//�X�V����
	void Update();

	//�`�揈��
	void Render();
};
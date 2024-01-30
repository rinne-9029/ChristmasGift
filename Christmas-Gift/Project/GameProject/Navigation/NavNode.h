#pragma once
#include<list>
#include<GLLibrary/CVector.h>
class NavManager;
class Field;

//�o�H�T���p�̃m�[�h�N���X
class NavNode : public Task
{
	friend NavManager;

public:
	//�m�[�h�̎��
	enum class NodeType
	{
		//�o�H�T�����ɒʉ߃m�[�h�Ƃ��Ďg�p�ł���m�[�h
		Navigation,

		//�ړI�n�Ƃ��Ă̂ݎg�p�ł���m�[�h
		Destination,
	};

	//�ڑ����Ă���m�[�h�̏��
	class ConnectData
	{
	public:
		NavNode* node;	//�ڑ��m�[�h
		float cost;		//�ړ��Ɋ|����R�X�g
		ConnectData(NavNode* node, int cost) : node(node), cost(cost){}
	};

private: 
	int m_no;			//�m�[�h�ԍ�
	NodeType m_type;	//�m�[�h�̎��
	//�ڑ����Ă���m�[�h��񃊃X�g
	std::list<ConnectData>m_connects;

	float m_cost;		//�ړ��R�X�g�L���p
	//�ړI�n�܂ňړ����邽�߂ɁA
	//���Ɉړ����ׂ��m�[�h
	NavNode* m_nextNodeToGoal;

	//�f�o�b�O�p:�m�[�h�̐F
	CVector4D m_nodeColor;

public:
	CVector3D m_pos;	//�m�[�h�̍��W
	///<summary>
	///�R���X�g���N�^
	///<summary>
	///<param name = "pos">�m�[�h�̍��W</param>
	///<param name = "type">�m�[�h�̎��</param>
	NavNode(const CVector3D& pos, NodeType type = NodeType::Navigation);
	//�f�X�g���N�^
	~NavNode();
	//�m�[�h���폜
	static void Kill();
	//�m�[�h�̏�Ԃ����Z�b�g
	void Reset();

	//�m�[�h�ԍ����擾
	int GetNodeNo() const;

	//�m�[�h�̍��W���擾
	const CVector3D& GetPos() const;
	// �m�[�h�̍��W��ݒ�
	void SetPos(const CVector3D& pos);

	// �ڑ����Ă���m�[�h��ǉ�
	void AddConnect(NavNode* node);
	// �ڑ����Ă���m�[�h�����X�g�Œǉ�
	void AddConnects(std::list<NavNode*> nodes);
	// �ڑ����Ă���m�[�h����菜��
	void RemoveConnect(NavNode* node);
	// �ڑ��m�[�h���X�g���N���A
	void ClearConnects();

	// �f�o�b�O�p�F�`�悷��m�[�h�̐F��ݒ�
	void SetNodeColor(const CVector3D& color);
	// �f�o�b�O�p�F�m�[�h�̕`�揈��
	void Render();

};
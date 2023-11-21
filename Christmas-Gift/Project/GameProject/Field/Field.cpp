#include"Field.h"
#include"FieldFloor.h"
#include"FieldWall.h"
#include"../Navigation/NavManager.h"
#include"../Navigation/NavNode.h"
#include"../ObjectBase/ObjectBase.h"
#include"GameScene/GameData.h"
#include"Debug/DebugPrint.h"
#include"Debug/DebugProfiler.h"

Field* Field::ms_instance = nullptr;

// �o�H�T���p�m�[�h�̃e�[�u��
std::list<CVector3D> Field::ms_nodes =
{
	CVector3D(-3.136362f, 0.0f, -27.636364f),
	CVector3D(-3.136362f, 0.0f, -15.272726f),
	CVector3D(-3.136362f, 0.0f, -2.909088f),
	CVector3D(-3.136362f, 0.0f, 3.272728f),
	CVector3D(-3.136362f, 0.0f, 9.454548f),
	CVector3D(-3.136362f, 0.0f, 15.636364f),
	CVector3D(-3.136362f, 0.0f, 21.818184f),

	CVector3D(-9.409090f, 0.0f, -33.818180f),
	CVector3D(-9.409090f, 0.0f, -21.454544f),
	CVector3D(-9.409090f, 0.0f, -9.090908f),

	CVector3D(-15.681818f, 0.0f, -40.000000f),
	CVector3D(-15.681818f, 0.0f, -27.636364f),
	CVector3D(-15.681818f, 0.0f, -9.090908f),
	CVector3D(-15.681818f, 0.0f, -2.909088f),
	CVector3D(-15.681818f, 0.0f, 3.272728f),

	CVector3D(-21.954544f, 0.0f, -40.000000f),
	CVector3D(-21.954544f, 0.0f, -27.636364f),
	CVector3D(-21.954544f, 0.0f, -21.454544f),
	CVector3D(-21.954544f, 0.0f, -9.090908f),
	CVector3D(-21.954544f, 0.0f, -2.909088f),
	CVector3D(-21.954544f, 0.0f, 9.454548f),
	CVector3D(-21.954544f, 0.0f, 15.636364f),

	CVector3D(-28.227272f, 0.0f, -33.818180f),
	CVector3D(-28.227272f, 0.0f, -27.636364f),
	CVector3D(-28.227272f, 0.0f, -15.272726f),
	CVector3D(-28.227272f, 0.0f, -9.090908f),
	CVector3D(-28.227272f, 0.0f, 3.272728f),
	CVector3D(-28.227272f, 0.0f, 21.818184f),
	CVector3D(-28.227272f, 0.0f, 28.000000f),

	CVector3D(-34.500000f, 0.0f, -40.000000f),
	CVector3D(-34.500000f, 0.0f, -21.454544f),
	CVector3D(-34.500000f, 0.0f, -9.090908f),
	CVector3D(-34.500000f, 0.0f, -2.909088f),
	CVector3D(-34.500000f, 0.0f, 28.00000f),

	CVector3D(3.136364f, 0.0f, -33.818180f),
	CVector3D(3.136364f, 0.0f, -27.636364f),
	CVector3D(3.136364f, 0.0f, -21.454544f),
	CVector3D(3.136364f, 0.0f, -15.272726f),
	CVector3D(3.136364f, 0.0f, -9.090908f),
	CVector3D(3.136364f, 0.0f, -2.909088f),
	CVector3D(3.136364f, 0.0f, 3.272728f),
	CVector3D(3.136364f, 0.0f, 9.454548f),
	CVector3D(3.136364f, 0.0f, 21.818184f),
	CVector3D(3.136364f, 0.0f, 28.000000f),

	CVector3D(9.409092f, 0.0f, -27.636364f),
	CVector3D(9.409092f, 0.0f, -15.272726f),
	CVector3D(9.409092f, 0.0f, 3.272728f),
	CVector3D(9.409092f, 0.0f, 15.636364f),
	CVector3D(9.409092f, 0.0f, 21.818184f),
	CVector3D(9.409092f, 0.0f, 28.000000f),

	CVector3D(15.681820f, 0.0f, -40.000000f),
	CVector3D(15.681820f, 0.0f, -33.818180f),
	CVector3D(15.681820f, 0.0f, -15.272726f),
	CVector3D(15.681820f, 0.0f, -2.909088f),
	CVector3D(15.681820f, 0.0f, 3.272728f),
	CVector3D(15.681820f, 0.0f, 15.636364f),

	CVector3D(21.954544f, 0.0f, -40.000000f),
	CVector3D(21.954544f, 0.0f, -21.454544f),
	CVector3D(21.954544f, 0.0f, -15.272726f),
	CVector3D(21.954544f, 0.0f, -9.090908f),

	CVector3D(28.227276f, 0.0f, -40.000000f),
	CVector3D(28.227276f, 0.0f, -33.818180f),
	CVector3D(28.227276f, 0.0f, -21.454544f),

	CVector3D(34.500000f, 0.0f, -40.000000f),
	CVector3D(34.500000f, 0.0f, -33.818180f),
	CVector3D(34.500000f, 0.0f, -15.272726f),
	CVector3D(34.500000f, 0.0f, -9.090908f),
	CVector3D(34.500000f, 0.0f, -2.909088f),
	CVector3D(34.500000f, 0.0f, 3.272728f),
};

//�R���X�g���N�^
Field::Field()
	:ObjectBase(ETaskTag::eField)
{
	m_remove = true;
	ms_instance = this;

	//�R���W�������f���̎擾
	switch (GameData::Stage)
	{
	case GameData::A_1:
		m_colModel = GET_RESOURCE("FieldCol", CModel);
		m_colWallModel = GET_RESOURCE("FieldWallCol", CModel);
		break;
	case GameData::B_1:
		m_colModel = GET_RESOURCE("FieldCol", CModel);
		m_colWallModel = GET_RESOURCE("FieldWallCol", CModel);
		break;
	case GameData::B_2:
		m_colModel = GET_RESOURCE("FieldCol", CModel);
		m_colWallModel = GET_RESOURCE("FieldWallCol", CModel);
		break;
	}
	

	//���ƕǂ̃N���X���쐬
	m_floor = new FieldFloor();
	m_wall = new FieldWall();

	//�o�H�T���p�̃m�[�h���쐬
	CreateNavNodes();
}

Field::~Field()
{
	if (ms_instance == this)
	{
		ms_instance = nullptr;
	}
}

//�o�H�T���p�̃m�[�h���쐬
void Field::CreateNavNodes()
{
	//�e�[�u�����̍��W�Ɍo�H�T���p�̃m�[�h���쐬
	for (CVector3D nodePos : ms_nodes)
	{
		new NavNode(nodePos);
	}
}

//�t�B�[���h�̃R���W�������擾
CModel* Field::GetColModel() const
{
	return m_colModel;
}

CModel* Field::GetColWallModel() const
{
	return m_colWallModel;
}

// �w�肵�����C�ƕǂ̃R���W�����Ƃ̃q�b�g����
bool Field::CollisionRay(const CVector3D& start, const CVector3D& end, CVector3D* outHitPos, CVector3D* outHitNormal)
{
	//DebugProfiler::StartTimer("FieldCollision");
	// �t�B�[���h���쐬����Ă��Ȃ���΁A�X���[
	Field* f = ms_instance;
	if (f == nullptr) return false;

	// �R���W�������f�����쐬����Ă��Ȃ���΁A�X���[
	CModel* col = f->GetColWallModel();
	if (col == nullptr) return false;

	//DebugProfiler::EndTimer("FieldCollision");
	// �R���W���������݂���΁A���C�Ƃ̃q�b�g����̌��ʂ�Ԃ�
	return col->CollisionRay(outHitPos, outHitNormal, start, end);
	
}

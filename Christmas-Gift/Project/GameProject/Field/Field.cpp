#include"Field.h"
#include"FieldFloor.h"
#include"FieldWall.h"
#include"Light/Light.h"
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
	CVector3D(14.842143,0.420055,10.135619),	//�g�C��

	CVector3D(14.968518,0.429452,7.185040),
	CVector3D(7.065483,0.420055,7.377606),
	CVector3D(-8.750116,0.410701,6.794860),
	CVector3D(-9.055938,0.410700,3.017577),
	CVector3D(-4.723531,0.410700,3.765090),
	CVector3D(10.534607,0.420055,10.441194),
	CVector3D(3.076858,0.410701,3.808710),
	CVector3D(-2.777906,0.410700,-2.100414),
	CVector3D(2.833257,0.410700,-1.009854),
	CVector3D(-12.562081,0.410701,8.687845),
	CVector3D(-3.432421,0.410702,9.018653),
	CVector3D(-3.443469,0.410702,12.018473),
	CVector3D(4.772832,0.420056,11.757642),
	CVector3D(5.153012,0.420053,-4.993202),
	CVector3D(12.891539,0.420053,-5.032509),
	CVector3D(12.564184,0.420055,4.250151),
	CVector3D(4.980745,0.420055,3.714080),
	CVector3D(15.236543,0.420054,-3.170865),
	CVector3D(15.763614,0.420054,1.320430),
	CVector3D(15.689437,0.420055,4.891421),
	CVector3D(7.000358,3.150262,12.407059),
	CVector3D(9.129925,3.150262,12.287002),
	CVector3D(9.067355,5.773851,7.233985),
};

//���C�g�p�̃e�[�u��
std::list<CVector3D> ms_lights =
{
	//�L�b�`���ƃ_�C�j���O�̕����̃��C�g
	CVector3D(5.5,1.420053,-4.808032),
	CVector3D(8.8,1.420053,-4.808032),
	CVector3D(12.1,1.420053,-4.808032),
	CVector3D(5.5,1.420053,0.808032),
	CVector3D(8.8,1.420053,0.808032),
	CVector3D(12.1,1.420053,0.808032),
	CVector3D(5.5,1.420053,3.808032),
	CVector3D(8.8,1.420053,3.808032),
	CVector3D(12.1,1.420053,3.808032),

	//
	CVector3D(9,0,9),
};

//�R���X�g���N�^
Field::Field()
	:ObjectBase(ETaskTag::eField,true)
{
	ms_instance = this;

	//�R���W�������f���̎擾
	switch (GameData::Stage)
	{
	case GameData::A_1:
		m_colModel = GET_RESOURCE("MapCol", CModel);
		m_colWallModel = GET_RESOURCE("WallMapCol", CModel);
		break;
	case GameData::B_1:
		m_colModel = GET_RESOURCE("MapCol", CModel);
		m_colWallModel = GET_RESOURCE("WallMapCol", CModel);
		break;
	case GameData::B_2:
		m_colModel = GET_RESOURCE("MapCol", CModel);
		m_colWallModel = GET_RESOURCE("WallMapCol", CModel);
		break;
	}
	

	//���ƕǂ̃N���X���쐬
	m_floor = new FieldFloor();
	m_wall = new FieldWall();

	m_lightNo = 2;

	//�o�H�T���p�̃m�[�h���쐬
	CreateNavNodes();
	CreateLights();
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

//�X�e�[�W�Ƀ��C�g���쐬
void Field::CreateLights()
{
	//�e�[�u�����̍��W�Ƀ��C�g���쐬
	for (CVector3D lightsPos : ms_lights)
	{
		if (m_lightNo <= 10)	
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, ERoomNo::eKitchen_Dining_Room);
			m_lightNo++;
		}
		else if(m_lightNo <= 12)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, ERoomNo::eLiving_Room);
			m_lightNo++;
		}
		
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
	// �t�B�[���h���쐬����Ă��Ȃ���΁A�X���[
	Field* f = ms_instance;
	if (f == nullptr) return false;

	// �R���W�������f�����쐬����Ă��Ȃ���΁A�X���[
	CModel* col = f->GetColWallModel();
	if (col == nullptr) return false;

	// �R���W���������݂���΁A���C�Ƃ̃q�b�g����̌��ʂ�Ԃ�
	return col->CollisionRay(outHitPos, outHitNormal, start, end);
	
}

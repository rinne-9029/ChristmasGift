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
	CVector3D(-1.119953,0.1,5.792867),		//1�K�L��
	CVector3D(-7.946468,0.1,6.155985),
	CVector3D(2.369029,0.1,-0.000122),		//�\�t�@�[�O
	CVector3D(5.275981,0.1,1.853063),
	CVector3D(6.315304,0.1,5.931384),
	CVector3D(-0.969914,0.1,16.858345),		//���֑O
	CVector3D(-0.936397,0.1,12.954982),		//1�K�K�i�O
	CVector3D(-7.932617,5.860001,12.954982),//�K�i
	CVector3D(-5.252072,4.460001,12.954982),
	CVector3D(-7.932617,8.660000,9.414995),
	CVector3D(-7.932617,10.053699,6.816346),//2�K�K�i�O
	CVector3D(1.205202,10.053699,7.116930),	//2�K�L��
	CVector3D(6.316210,10.053699,7.119658),	
	CVector3D(-10.846934,10.053699,6.613060),
	CVector3D(-10.756325,10.053700,13.386012),
	CVector3D(0.943921,10.053699,1.877687),	//���e����
};

//���C�g�p�̃e�[�u��
std::list<CVector3D> ms_lights =
{
	CVector3D(2.208868,1.420053,2.165025),		//���r���O
	CVector3D(4.208868,1.420053,2.165025),
	CVector3D(4.208868,1.420053,4.165025),
	CVector3D(4.208868,1.420053,0.165025),
	CVector3D(0.208868,1.420053,2.165025),
	CVector3D(0.208868,1.420053,4.165025),
	CVector3D(0.208868,1.420053,0.165025),
	CVector3D(2.208868,1.420053,4.165025),
	CVector3D(2.208868,1.420053,0.165025),

	CVector3D(-0.973303,1.420053,11.385047),	//1�K�L��
	CVector3D(0.157168,1.420053,17.083790),

	CVector3D(-3.899999,3.360492,13.075190),	//�K�i
	CVector3D(-7.773126,5.860001,13.265531),
	CVector3D(-7.613574,8.594998,9.993688),
	CVector3D(-7.764234,10.053699,6.778700),

	//CVector3D(-5.719062,1.420053,6.061092),		

	//CVector3D(-11.187679,3.110000,6.136277),	//�g�C��

	//CVector3D(1.537720,1.420053,16.998697),		//����

	//CVector3D(-10.713727,1.420053,-1.446610),	//�����C
	//CVector3D(-10.331367,1.420053,1.261683),

	

	//CVector3D(-7.696043,10.053699,0.807639),	//2�K�L��
	//CVector3D(-3.446229,10.053699,6.558009),
	//CVector3D(0.053765,10.053699,6.564985),
	//CVector3D(4.853758,10.053699,6.574552),

	//CVector3D(-10.867166,10.053699,10.145189),	//���u
	//CVector3D(-11.599999,11.485270,16.974661),	//2�K�g�C��
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
			new Light(lightsPos, m_lightNo,0,true);
			m_lightNo++;
		}
		else if(m_lightNo <= 12)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo,1,false);
			m_lightNo++;
		}
		else if(m_lightNo <= 16)
		{
			////2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 2,false);
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

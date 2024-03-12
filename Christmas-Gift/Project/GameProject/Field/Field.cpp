#include"Field.h"
#include"FieldFloor.h"
#include"FieldWall.h"
#include"FieldObject/Door.h"
#include"Light/Light.h"
#include"../Navigation/NavManager.h"
#include"../Navigation/NavNode.h"
#include"../ObjectBase/ObjectBase.h"
#include"GameScene/GameData.h"

Field* Field::ms_instance = nullptr;

// �o�H�T���p�m�[�h�̃e�[�u��
std::list<CVector3D> Field::ms_nodes =
{
	CVector3D(-1.119953,1,5.792867),		//1�K�L��
	CVector3D(-7.946468,1,6.155985),
	CVector3D(-7.979040,1,3.100000),
	CVector3D(-10.848549,1,3.523031),		//���ʏ�
	CVector3D(2.369029,1,-0.000122),		//�\�t�@�[�O
	CVector3D(5.275981,1,1.853063),
	CVector3D(6.315304,1,5.931384),
	CVector3D(-0.969914,1,16.858345),		//���֑O
	CVector3D(-0.936397,1,12.954982),		//1�K�K�i�O
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
	CVector3D(2.8,1.5,2.1),		//���r���O
	CVector3D(1,1.5,12.1),		//1�K�L���@
	CVector3D(-5,1.5,5.3),		//1�K�L���A
	CVector3D(-10.5,1.5,2.5),	//���ʏ�
	CVector3D(-4.6,3.7,12.9),	//�K�i
	CVector3D(-7.0,6.8,13.0),
	CVector3D(-7.0,11.8,13.0),
	CVector3D(-7.9,8.1,10.0),	
	CVector3D(-7.7,9.8,6.6),//2�K�L��
	CVector3D(-4.2,9.8,6.6),
	CVector3D(0.4,9.8,6.7),
	CVector3D(5.0,9.8,6.8),
	CVector3D(-10.6,9.8,12.5),
	CVector3D(-10.6,9.8,8.5),
	CVector3D(-2.0,10.5,0.4),//���e����
	CVector3D(5.8,9.8,0.6),//�q������
	
};

//�R���X�g���N�^
Field::Field(const char* Doorfile)
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
	//���C�g�쐬
	CreateLights();
	//�h�A�쐬
	CreateDoors(Doorfile);
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
		//���r���O
		if (m_lightNo <= 2)	
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 0, 8.0f, CLight::eLight_Point, true);
			m_lightNo++;
		}
		else if (m_lightNo <= 3)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 1, 7.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 4)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 2, 5.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 5)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 3, 3.5f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 9)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 4, 5.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 15)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 5, 4.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 16)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 6, 6.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		else if (m_lightNo <= 17)
		{
			//2�`�Ԃ͕����p���C�g�ԍ�
			new Light(lightsPos, m_lightNo, 7, 5.0f, CLight::eLight_Point, false);
			m_lightNo++;
		}
		
	}
}

//�h�A��������
void Field::CreateDoors(const char* file)
{
	FILE* fp = NULL;

	//�f�[�^���e�L�X�g�ǂݍ��݂ŃI�[�v��
	fopen_s(&fp, file, "r");
	//�J���̂Ɏ��s
	if (!fp)return;
	
	char buf[256] = "";

	//�t�@�C���̖����܂ŌJ��Ԃ�
	while (!feof(fp))
	{
		//��s�Â�buf�Ɋi�[
		fgets(buf, 256, fp);

		//�h�A�̍��W
		CVector3D Pos(0, 0, 0);
		//�h�A�̌���
		float Rot;

		sscanf_s(buf,"%f %f %f %f", &Pos.x, &Pos.y, &Pos.z, &Rot);

		new Door(Pos,CVector3D(0,DtoR(Rot),0), CVector3D(1, 1, 1), CVector3D(1, 2, 0.3));
	}
	fclose(fp);
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

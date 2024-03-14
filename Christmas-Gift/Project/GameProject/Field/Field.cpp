#include"Field.h"
#include"FieldFloor.h"
#include"FieldWall.h"
#include"FieldObject/Door.h"
#include"Field/FieldObject/Switch.h"
#include"Light/Light.h"
#include"../Navigation/NavManager.h"
#include"../Navigation/NavNode.h"
#include"../ObjectBase/ObjectBase.h"
#include"GameScene/GameData.h"

Field* Field::ms_instance = nullptr;

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
Field::Field(const char* Nodefile,const char* Lightfile,const char* Doorfile,const char* Switchfile)
	:ObjectBase(ETaskTag::eField,true)
{
	ms_instance = this;

	//�R���W�������f���̎擾
	m_colModel = GET_RESOURCE("MapCol", CModel);
	m_colWallModel = GET_RESOURCE("WallMapCol", CModel);
	
	//���ƕǂ̃N���X���쐬
	m_floor = new FieldFloor();
	m_wall = new FieldWall();

	m_lightNo = 2;
	//�o�H�T���p�̃m�[�h���쐬
	CreateNavNodes(Nodefile);
	//���C�g�쐬
	CreateLights(Lightfile);
	//�h�A�쐬
	CreateDoors(Doorfile);
	//�X�C�b�`�쐬
	CreateSwitchs(Switchfile);
}

Field::~Field()
{
	if (ms_instance == this)
	{
		ms_instance = nullptr;
	}
}

//�o�H�T���p�̃m�[�h���쐬
void Field::CreateNavNodes(const char* file)
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

		//�m�[�h�̍��W
		CVector3D Pos(0, 0, 0);

		sscanf_s(buf, "%f %f %f", &Pos.x, &Pos.y, &Pos.z);

		//�m�[�h����
		new NavNode(Pos);
	}
	fclose(fp);
}

//�X�e�[�W�Ƀ��C�g���쐬
void Field::CreateLights(const char* file)
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

		CVector3D Pos(0, 0, 0);			//���C�g�̍��W
		int No = 0;						//���C�g�i���o�[
		float Range = 0;				//���̑傫��
		int IsShine = 0;				//�����Ă��邩�̔��f
		bool Shine = true;				

		sscanf_s(buf, "%f %f %f %d %f %d", &Pos.x, &Pos.y, &Pos.z, &No, &Range, &IsShine);

		//�l��0�Ȃ�d�C�͂��Ă��Ȃ�
		if (IsShine == 0) Shine = false;

		//���C�g����
		new Light(Pos,m_lightNo,No,Range, CLight::eLight_Point,Shine);

		m_lightNo++;
	}
	fclose(fp);

}

//�h�A���쐬
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

		//�h�A����
		new Door(Pos,CVector3D(0,DtoR(Rot),0), CVector3D(1, 1, 1), CVector3D(1, 2, 0.3));
	}
	fclose(fp);
}

//�X�C�b�`���쐬
void Field::CreateSwitchs(const char* file)
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

		//�X�C�b�`�̍��W
		CVector3D Pos(0, 0, 0);
		//�X�C�b�`�̌���
		float Rot;
		//�X�C�b�`�̔ԍ�
		float No;

		sscanf_s(buf, "%f %f %f %f %f", &Pos.x, &Pos.y, &Pos.z, &Rot, &No);

		//�X�C�b�`����
		new Switch(Pos, CVector3D(0, DtoR(Rot), 0), CVector3D(1, 1, 1),No);
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

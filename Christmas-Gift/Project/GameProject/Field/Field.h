#pragma once
#include"GLLibrary/CModel.h"
#include"ObjectBase/ObjectBase.h"

class FieldFloor;
class FieldWall;
class NavNode;

//�t�B�[���h����N���X
class Field : public ObjectBase {
private:
	//�t�B�[���h�N���X�̃C���X�^���X
	static Field* ms_instance;
	//�o�H�T���p�m�[�h�̃e�[�u��
	static std::list<CVector3D>ms_nodes;

	CModel* m_colModel;		//�t�B�[���h�̃R���W�������f��
	CModel* m_colWallModel;	//�ǂ̃R���W�������f��
	FieldFloor* m_floor;		//���`��p�̃N���X
	FieldWall* m_wall;			//�Ǖ`��p�̃N���X
	NavNode* m_node;

public:
	//�R���X�g���N�^
	Field();
	//�f�X�g���N�^
	~Field();

	//�o�H�T���p�̃m�[�h���쐬
	void CreateNavNodes();

	//�t�B�[���h�̃R���W�������擾
	CModel* GetColModel() const;

	//�ǂ̃R���W�������擾
	CModel* GetColWallModel() const;

	//�w�肵�����C�ƕǂ̃R���W�����Ƃ̃q�b�g����
	static bool CollisionRay(const CVector3D& start, const CVector3D& end, CVector3D* outHitPos, CVector3D* outHitNormal);
};
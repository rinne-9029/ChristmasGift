#pragma once

class ObjectBase : public Task
{
private:

	//ETaskTag m_tag;			//�I�u�W�F�N�g���Ƃ̎�ޖ�
	

	//CVector3D m_pos;		//�I�u�W�F�N�g���W
	//CVector3D m_rot;		//�I�u�W�F�N�g��]�l
	//CVector3D m_at;			//�I�u�W�F�N�g�����_
	//CVector3D m_vec;		//�I�u�W�F�N�g�ړ��x�N�g��
	//CVector3D m_dir;		//�I�u�W�F�N�g�O�����x�N�g��
	//////int m_kill;

	//////�����蔻��p
	//////���A�J�v�Z���p
	//float m_rad;			//�I�u�W�F�N�g���a
	//float m_height;			//�I�u�W�F�N�g����
	//CVector3D m_lineS;		//�I�u�W�F�N�g�����n�_
	//CVector3D m_lineE;		//�I�u�W�F�N�g�����I�_

	//////���`�p
	CVector3D m_size;		//�傫��
	//COBB m_obb;				//���`

public:
	CModelObj m_model;		//�I�u�W�F�N�g���f��
	//�R���X�g���N�^
	ObjectBase(ETaskTag tag,bool remove);
	//�f�X�g���N�^
	virtual ~ObjectBase();

	/*ETaskTag GetTag() {
		return m_tag;
	}*/
};
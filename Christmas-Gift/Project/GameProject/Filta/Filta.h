#pragma once

//�t�F�[�h�C���E�t�F�[�h�A�E�g�Ǘ��N���X

class Filta : public Task
{
private:
	CImage m_filta;		//�t�B���^�[
	float m_alpha;		//�s�����x
	float m_time;		//����
	void Fadein();		//�t�F�[�h�C������
	void Fadeout();		//�t�F�[�h�A�E�g����
public:
	//�R���X�g���N�^
	Filta();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
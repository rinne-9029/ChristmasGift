#pragma once

//�Q�[���I�[�o��ʊǗ��N���X

class GameOver : public Task {
private:
	CImage m_BuckGraund;		//�w�i
	CImage m_TitleText;			//�^�C�g������
	CImage m_ReStartText;		//���g���C����
	int m_select;				//�Z���N�g�t���O
	float m_High;				//�����\���p����
	void HighLight();			//�����\������
public:
	//�R���X�g���N�^
	GameOver();
	//�f�X�g���N�^
	~GameOver();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
#pragma once

//�^�C�g����ʊǗ��N���X

class Title : public Task {
private:
	CImage m_TitleText;		//�^�C�g�����e�L�X�g
	CImage m_StartText;		//�X�^�[�g�e�L�X�g
	CImage m_ManualText;	//�����e�L�X�g
	CImage m_RankingText;	//�����L���O�e�L�X�g
	int m_select;			//�Z���N�g�t���O
	float m_fuwafuwa;		//�ӂ�ӂ�\���p����
	void FuwaFuwa();		//�ӂ�ӂ�\������
public:
	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
#pragma once

class GameClear : public Task {
private:
	CImage m_BuckGraund;		//�w�i
	CImage m_TitleText;			//�^�C�g������
	CImage m_RankingText;		//�����L���O����
	static const int m_max_size = 256;
	static const int m_max_line = 32;
	//char m_text[m_max_line][m_max_size];
	//char m_text[256];

	int m_Rank[5];
	int m_line_size;
	int m_select;				//�Z���N�g�t���O
	float m_High;				//�����\���p����
	void HighLight();			//�����\������
	void ChengeRanking();		//�����L���O�X�V����
public:
	//�R���X�g���N�^
	GameClear();
	//�f�X�g���N�^
	~GameClear();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};

#pragma once

//�����L���O�Ǘ��N���X

class Ranking : public Task {
private:
	static const int m_max_size = 256;
	static const int m_max_line = 32;
	char m_text[m_max_line][m_max_size];
	int m_line_size;
	int m_select;
	CImage m_TitleText;		//�^�C�g���e�L�X�g
	float m_fuwafuwa;
	void FuwaFuwa();
public:
	//�R���X�g���N�^
	Ranking(const char* file);
	//�f�X�g���N�^
	~Ranking();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
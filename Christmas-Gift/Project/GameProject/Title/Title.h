#pragma once

class Filta;

class Title : public Task {
private:
	Filta* mp_filta;
	CImage m_StartText;
	CImage m_ManualText;
	CImage m_RankingText;
	int m_select;
	float m_fuwafuwa;
	void FuwaFuwa();
	void Erabu();
public:
	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();
	//�X�V����
	void Update();
	//3D�`�揈��
	void Render();
	//2D�`�揈��
	void Draw();
};
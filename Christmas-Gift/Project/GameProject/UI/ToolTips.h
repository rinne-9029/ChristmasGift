#pragma once

class ToolTips : public Task
{
private:
	CImage m_Image;
public:
	bool isDraw;
	//�R���X�g���N�^
	ToolTips();
	//�f�X�g���N�^
	~ToolTips();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
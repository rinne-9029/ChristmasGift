#pragma once

class Timer : public Task
{
private:
	CImage m_Image;
	int count;
	int a;
public:
	//�R���X�g���N�^
	Timer();
	//�f�X�g���N�^
	~Timer();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};
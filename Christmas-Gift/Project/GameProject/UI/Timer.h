#pragma once

class Timer : public Task
{
private:
	CVector2D a[2];
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
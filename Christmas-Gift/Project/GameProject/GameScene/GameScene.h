#pragma once

class  GameScene :public Task {
private:

	typedef struct
	{
		CVector3D		pos;
		CVector3D		size;
	} S_STATUS;
public:
	//�R���X�g���N�^
	GameScene();
	//�f�X�g���N�^
	~GameScene();
	//�X�V����
	void Update();
};

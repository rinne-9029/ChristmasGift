#pragma once

class Player;
class Filta;

//�����Q�[�W�̃N���X
class SleepLife : public Task
{
private:
	Player* mp_player;
	Filta* mp_filta;
public:
	//�R���X�g���N�^
	SleepLife();
	//�f�X�g���N�^
	~SleepLife();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();

};

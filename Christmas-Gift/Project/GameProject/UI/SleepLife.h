#pragma once

//�����Q�[�W�Ǘ��N���X

class SleepLife : public Task
{
private:
	CImage m_REMText;		//������������
	CImage m_NREMText;		//�m��������������
	int m_ChengeSleep;		//������Ԑ؂�ւ�����
public:
	static bool m_REM;
	//�R���X�g���N�^
	SleepLife();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();

};
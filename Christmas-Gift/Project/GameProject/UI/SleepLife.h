#pragma once

//�����Q�[�W�Ǘ��N���X

class SleepLife : public Task
{
private:
	CImage m_SleepMeter;	//�����l
	CImage m_FaceRelief;	//���v
	CImage m_FaceUsually;	//����
	CImage m_FaceWorry;		//��΂�
	CImage m_REMText;		//������������
	CImage m_NREMText;		//�m��������������
	int m_ChengeSleep;		//������Ԑ؂�ւ�����
	int m_ChengeFace;		//��؂�ւ��ϐ�
public:
	static bool m_REM;		//�����̏�ԃt���O
	//�R���X�g���N�^
	SleepLife();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();

};
#include"SleepLife.h"
#include"Chara/Player/Player.h"
#include"Filta/Filta.h"
#include"GameScene/GameData.h"

bool SleepLife::m_REM = true;

SleepLife::SleepLife()
	:Task(ETaskTag::eUI, true)
{
	m_REMText = COPY_RESOURCE("REMsleep", CImage);
	m_NREMText = COPY_RESOURCE("NREMsleep", CImage);

	//0�`100�b�����_��
	m_ChengeSleep = rand() % 100;
}

//�X�V����
void SleepLife::Update()
{
	//�q���̐������o���i�Q�[���I�[�o�[�j
	if (GameData::BlueSleepSize >= 0) return;

	//�Q�[���I�[�o�[
	GameData::GameOverCheck = true;
	//�t�F�[�h�A�E�g���s
	GameData::StartFadeOut = true;
}

//2D�`�揈��
void SleepLife::Draw()
{
	//�Ԃ̐����Q�[�W�`��
	Utility::DrawQuad(CVector2D(20, 250), CVector2D(300, 25), CVector4D(1, 0, 0, 1));
	//�̐����Q�[�W�`��
	Utility::DrawQuad(CVector2D(20, 250), CVector2D(GameData::BlueSleepSize, 25), CVector4D(0, 0, 1, 1));

	//������������
	m_REMText.SetPos(106, 216);
	m_REMText.SetSize(128, 32);

	//�m��������������
	m_NREMText.SetPos(42, 216);
	m_NREMText.SetSize(256, 32);

	if (GameData::second >= m_ChengeSleep)
	{
		m_REM = !m_REM;
		m_ChengeSleep = m_ChengeSleep + rand() % 100;
	}

	//����������ԂȂ�
	if (m_REM)	m_REMText.Draw();
	//�m������������ԂȂ�
	else		m_NREMText.Draw();
}
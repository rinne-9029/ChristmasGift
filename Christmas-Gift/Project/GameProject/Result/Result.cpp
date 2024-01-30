#include "Result.h"
#include"Title/Title.h"

Result::Result()
	:Task(ETaskTag::eResult,true)
	,m_select(0)
	,m_High(0)
{
	m_BuckGrangd = COPY_RESOURCE("ResultBackGround", CImage);
	m_TitleText = COPY_RESOURCE("ResultTitleText", CImage);
	m_RankingText = COPY_RESOURCE("ResultRankingText", CImage);
}

Result::~Result()
{
	switch (m_select)
	{
		//�^�C�g��
	case 0:
		new Title();
		break;
		//�����L���O
	case 1:
		new Title();
		break;
	}
}

void Result::HighLight()
{
	m_High = m_High + 0.1;
	switch (m_select)
	{
		//�^�C�g����������
	case 0:
		m_TitleText.SetPos(674, 540);
		m_TitleText.SetSize(512 + 40 * cos(m_High), 128 + 10 * cos(m_High));
		m_TitleText.Draw();
		m_RankingText.SetPos(674, 720);
		m_RankingText.Draw();
		break;
		//�����L���O��������
	case 1:
		m_TitleText.SetPos(674, 540);
		m_TitleText.Draw();
		m_RankingText.SetPos(674, 720);
		m_RankingText.SetSize(640 + 50 * cos(m_High), 128 + 10 * cos(m_High));
		m_RankingText.Draw();
	}
}

void Result::Update()
{
	//�X�y�[�X�L�[�Ō���
	if (PUSH(CInput::eButton5))
	{
		TaskManager::KillALL();
	}

	//W�L�[����
	if (PUSH(CInput::eUp) && m_select > 0)
	{
		m_select--;	
		m_High = 0;	//�������Z�b�g
	}
	//S�L�[����
	if (PUSH(CInput::eDown) && m_select < 1)
	{
		m_select++;
		m_High = 0;	//�������Z�b�g
	}
	
}

void Result::Draw()
{
	//�w�i�`��
	m_BuckGrangd.Draw();
	HighLight();
}
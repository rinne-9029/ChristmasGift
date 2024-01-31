#include "GameOver.h"
#include"Title/Title.h"
#include"GameScene/GameData.h"
#include"GameScene/GameScene.h"

GameOver::GameOver()
	:Task(ETaskTag::eResult,true)
{
	GameData::StartFadeIn = true;

	m_BuckGraund = COPY_RESOURCE("OverBackGround", CImage);
	m_TitleText = COPY_RESOURCE("TitleText", CImage);
	m_ReStartText = COPY_RESOURCE("ReStartText", CImage);
}

GameOver::~GameOver()
{
	switch (m_select)
	{
		//�^�C�g��
	case 0:
		new Title();
		break;
		//���g���C
	case 1:
		new GameScene();
		break;
	}
}

void GameOver::HighLight()
{
	m_High = m_High + 0.1;
	switch (m_select)
	{
		//�^�C�g����������
	case 0:
		m_TitleText.SetPos(674, 540);
		m_TitleText.SetSize(512 + 40 * cos(m_High), 128 + 10 * cos(m_High));
		m_TitleText.Draw();
		m_ReStartText.SetPos(674, 720);
		m_ReStartText.Draw();
		break;
		//���g���C��������
	case 1:
		m_TitleText.SetPos(674, 540);
		m_TitleText.Draw();
		m_ReStartText.SetPos(674, 720);
		m_ReStartText.SetSize(512 + 40 * cos(m_High), 128 + 10 * cos(m_High));
		m_ReStartText.Draw();
	}
}

void GameOver::Update()
{
	//�X�y�[�X�L�[�Ō���
	if (PUSH(CInput::eButton5))
	{
		GameData::StartFadeOut = true;
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

void GameOver::Draw()
{
	//�w�i�`��
	m_BuckGraund.Draw();
	//�����\���`��
	HighLight();
}

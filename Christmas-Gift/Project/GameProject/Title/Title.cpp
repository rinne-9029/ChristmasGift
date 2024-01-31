#include"Title.h"
#include"Filta/Filta.h"
#include"GameScene/GameScene.h"
#include"GameScene/GameData.h"

//�R���X�g���N�^
Title::Title()
	:Task(ETaskTag::eScene,true)
	,m_select(0)
	,m_fuwafuwa(0.0f)
{
	m_StartText = COPY_RESOURCE("StartText", CImage);
	m_ManualText = COPY_RESOURCE("ManualText", CImage);
	m_RankingText = COPY_RESOURCE("RankingText", CImage);
}

//�f�X�g���N�^
Title::~Title()
{
	switch (m_select)
	{
	case 0:
		//�Q�[���V�[���N��
		new GameScene();
		break;
	case 1:
		//������
		//��
		new GameScene();
		break;
	case 2:
		//�����L���O
		//��
		new GameScene();
		break;
	}
}

//�ӂ�ӂ퓮������
void Title::FuwaFuwa()
{
	m_fuwafuwa += 0.02f;

	//�I�΂ꂽ������sin�J�[�u�łӂ�ӂ퓮��
	switch (m_select)
	{
		//�X�^�[�g
	case 0:
		m_StartText.SetPos(200, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
		//������
	case 1:
		m_StartText.SetPos(200, 750);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
		//�����L���O
	case 2:
		m_StartText.SetPos(200, 750);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_RankingText.Draw();
		break;
	}
}

//�X�V����
void Title::Update()
{
	//�X�y�[�X�{�^��
	if (PUSH(CInput::eButton5))		
	{
		//�t�F�[�h�A�E�g���s
		GameData::StartFadeOut = true;
	}

	//A�L�[����
	if (PUSH(CInput::eLeft) && m_select > 0)
	{
		m_select--;
		m_fuwafuwa = 0;
	}
	//D�L�[����
	if (PUSH(CInput::eRight) && m_select < 2)
	{
		m_select++;
		m_fuwafuwa = 0;
	}
}

//2D�`�揈��
void Title::Draw()
{
	FuwaFuwa();	
}
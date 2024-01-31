#include"Title.h"
#include"GameScene/GameScene.h"
#include"GameScene/GameData.h"

//�R���X�g���N�^
Title::Title()
	:Task(ETaskTag::eScene,true)
	,m_select(0)
	,m_fuwafuwa(0.0f)
{
	//�t�F�[�h�C�����s
	GameData::StartFadeIn = true;

	SOUND("BGM_TitleOP")->Play(true);

	m_TitleText = COPY_RESOURCE("GameTitleText", CImage);
	m_StartText = COPY_RESOURCE("StartText", CImage);
	m_ManualText = COPY_RESOURCE("ManualText", CImage);
	m_RankingText = COPY_RESOURCE("GameRankingText", CImage);
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
		//�X�^�[�g����
	case 0:
		m_StartText.SetPos(200, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
		//����������
	case 1:
		m_StartText.SetPos(200, 750);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
		//�����L���O����
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
	if (GameData::StartFadeIn) return;
	if (GameData::StartFadeOut) return;

	//�X�y�[�X�{�^��
	if (PUSH(CInput::eButton5))		
	{
		SOUND("BGM_TitleOP")->Stop();
		SOUND("SE_Click")->Volume(0.5);
		SOUND("SE_Click")->Play();
		//�t�F�[�h�A�E�g���s
		GameData::StartFadeOut = true;
	}

	//A�L�[����
	if (PUSH(CInput::eLeft) && m_select > 0)
	{
		SOUND("SE_Select")->Volume(0.5);
		SOUND("SE_Select")->Play();
		m_select--;
		//�ӂ�ӂ�\�����Z�b�g
		m_fuwafuwa = 0;
	}
	//D�L�[����
	if (PUSH(CInput::eRight) && m_select < 2)
	{
		SOUND("SE_Select")->Volume(0.5);
		SOUND("SE_Select")->Play();
		m_select++;
		//�ӂ�ӂ�\�����Z�b�g
		m_fuwafuwa = 0;
	}
}

//2D�`�揈��
void Title::Draw()
{
	m_TitleText.SetPos(500, 300);
	m_TitleText.Draw();
	//�ӂ�ӂ�\���`��
	FuwaFuwa();	
}
#include"Title.h"
#include"Filta/Filta.h"
#include"GameScene/GameScene.h"
#include"GameScene/GameData.h"

//�R���X�g���N�^
Title::Title()
	:Task(ETaskTag::eScene,true)
	,mp_filta(nullptr)
	,m_select(0)
	,m_fuwafuwa(0.0f)
{
	m_StartText = COPY_RESOURCE("StartText", CImage);
	m_ManualText = COPY_RESOURCE("ManualText", CImage);
	m_RankingText = COPY_RESOURCE("RankingText", CImage);

	GameData::Start = false;
	mp_filta = dynamic_cast<Filta*>(TaskManager::FindObject(ETaskTag::eFilta));
	mp_filta->m_FadeinCheck = true;
}

//�f�X�g���N�^
Title::~Title()
{
	//�Q�[���V�[���N��
	new GameScene();	
}

//�ӂ�ӂ퓮������
void Title::FuwaFuwa()
{
	m_fuwafuwa += 0.02f;

	//�I�΂ꂽ������sin�J�[�u�łӂ�ӂ퓮��
	switch (m_select)
	{
	case 0:
		m_StartText.SetPos(200, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_StartText.Draw();
		break;
	case 1:
		m_ManualText.SetPos(855, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_ManualText.Draw();
		break;
	case 2:
		m_RankingText.SetPos(1270, 750 - abs(sin(m_fuwafuwa)) * 64);
		m_RankingText.Draw();
		break;
	}
}

//�Z���N�g����Ă��Ȃ�������\��
void Title::Erabu()
{
	switch (m_select)
	{
	case 0:
		m_ManualText.SetPos(855, 750);
		m_ManualText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
	case 1:
		m_StartText.SetPos(200, 750);
		m_StartText.Draw();
		m_RankingText.SetPos(1270, 750);
		m_RankingText.Draw();
		break;
	case 2:
		m_StartText.SetPos(200, 750);
		m_StartText.Draw();
		m_ManualText.SetPos(855, 750);
		m_ManualText.Draw();
		break;
	}
	

}

//�X�V����
void Title::Update()
{
	if (PUSH(CInput::eButton5))		//z�{�^��
	{
		switch (m_select)
		{
		case 0:
			mp_filta->m_FadeoutCheck = true;
			GameData::Start = true;
			break;
		case 1:
			break;
		case 2:
			break;
		}
	}

	if (!mp_filta->m_FadeoutCheck && GameData::Start)
	{
		TaskManager::KillALL();
	}
	
}

//3D�`�揈��
void Title::Render()
{
}

//2D�`�揈��
void Title::Draw()
{
	if (PUSH(CInput::eLeft) && m_select > 0)
	{
		m_select--;
		m_fuwafuwa = 0;
	}
	if (PUSH(CInput::eRight) && m_select < 2)
	{
		m_select++;
		m_fuwafuwa = 0;
	}
	Erabu();
	FuwaFuwa();	
}
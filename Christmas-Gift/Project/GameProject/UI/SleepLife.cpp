#include"SleepLife.h"
#include"Chara/Player/Player.h"
#include"Filta/Filta.h"
#include"GameScene/GameData.h"

bool SleepLife::m_REM = true;

SleepLife::SleepLife()
	:Task(ETaskTag::eUI, true)
	, mp_player(nullptr)
	, mp_filta(nullptr)
{
	mp_player = dynamic_cast<Player*>(TaskManager::FindObject(ETaskTag::ePlayer));
	mp_filta = dynamic_cast<Filta*>(TaskManager::FindObject(ETaskTag::eFilta));
	m_ImageREM = COPY_RESOURCE("REMsleep", CImage);
	m_ImageNREM = COPY_RESOURCE("NREMsleep", CImage);
	m_ChengeSleep = rand() % 100;
}

SleepLife::~SleepLife()
{

}

//�X�V����
void SleepLife::Update()
{
	//�q���̐������o���i�Q�[���I�[�o�[�j
	if (GameData::BlueSleepSize >= 0) return;

	//�Q�[���I�[�o�[
	GameData::GameOverCheck = true;
	TaskManager::KillALL();
}

//2D�`�揈��
void SleepLife::Draw()
{
	//�Ԃ̐����Q�[�W�`��
	Utility::DrawQuad(CVector2D(20, 250), CVector2D(300, 25), CVector4D(1, 0, 0, 1));
	//�̐����Q�[�W�`��
	Utility::DrawQuad(CVector2D(20, 250), CVector2D(GameData::BlueSleepSize, 25), CVector4D(0, 0, 1, 1));

	m_ImageREM.SetPos(106, 216);
	m_ImageREM.SetSize(128, 32);

	m_ImageNREM.SetPos(42, 216);
	m_ImageNREM.SetSize(256, 32);

	if (GameData::second >= m_ChengeSleep)
	{
		m_REM = !m_REM;
		m_ChengeSleep = m_ChengeSleep + rand() % 100;
	}

	//����������ԂȂ�
	if (m_REM)	m_ImageREM.Draw();
	//��������Ȃ��Ȃ�
	else		m_ImageNREM.Draw();
	
	
	

	
	
}
#include "Timer.h"
#include"GameScene/GameData.h"

Timer::Timer()
	:Task(ETaskTag::eUI, true)
{
	m_Image = COPY_RESOURCE("Text", CImage);
	count = 0;
}

Timer::~Timer()
{
}

void Timer::Update()
{
}

void Timer::Draw()
{
	count++;
	//1�b�o�߂ŃJ�E���g�𑝉�
	if (count > 60)
	{
		GameData::second--;	//�P�b���Z
		count = 0;
	}

	int cnt = GameData::second;
	//�^�C�}�[�`��؂�ւ�
	for (int i = 0; i < 3; i++, cnt /= 10) {
		int s = cnt % 10;
		m_Image.SetRect(8 * s, 30, 8 * s + 8, 40);
		m_Image.SetSize(64, 64);
		m_Image.SetPos(1792 - 64 * i, 50);
		m_Image.Draw();
	}
}

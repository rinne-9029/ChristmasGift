#include "Snow.h"

//�R���X�g���N�^
Snow::Snow()
	:Task(ETaskTag::eScene,true)
{
	m_snow = COPY_RESOURCE("Snow", CImage);
	int wide = rand() % 1920;				//�����W�������_��
	m_snowPos = CVector2D(wide, -20);		//���W
	m_snowAng = 0;							//��]�l
}

//�f�X�g���N�^
Snow::~Snow()
{
}

//�X�V����
void Snow::Update()
{
	//���t���[����]
	m_snowAng += 0.1f;
	//��̗���
	m_snowPos.y += 2;
	//�����n�_��1200�𒴂�����폜
	if (m_snowPos.y > 1200) Kill();
}

//�`�揈��
void Snow::Draw()
{
	m_snow.SetSize(64, 64);
	m_snow.SetCenter(32, 32);
	m_snow.SetPos(m_snowPos);
	m_snow.SetAng(m_snowAng);
	m_snow.Draw();
}

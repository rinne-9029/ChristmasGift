#include "ToolTips.h"

//�R���X�g���N�^
ToolTips::ToolTips()
	:Task(ETaskTag::eUI,true)
{
	m_Image = COPY_RESOURCE("MouseL", CImage);
	isDraw = false;
}

//2D�`�揈��
void ToolTips::Draw()
{
	if (!isDraw)return;
	m_Image.SetPos(1060,340);
	m_Image.SetSize(64,128);
	m_Image.Draw();
}

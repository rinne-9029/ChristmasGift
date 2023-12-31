#include"FieldWall.h"
#include"../ObjectBase/ObjectBase.h"
#include"GameScene/GameData.h"

FieldWall::FieldWall()
	:ObjectBase(ETaskTag::eFieldWall,true)
{
	switch (GameData::Stage)
	{
	case GameData::A_1:
		m_model = COPY_RESOURCE("WallMap", CModelObj);
		break;
	case GameData::B_1:
		m_model = COPY_RESOURCE("WallMap", CModelObj);
		break;
	case GameData::B_2:
		m_model = COPY_RESOURCE("WallMap", CModelObj);
		break;
	}
}

void FieldWall::Update()
{

}

void FieldWall::Render()
{
	m_model.Render();
}
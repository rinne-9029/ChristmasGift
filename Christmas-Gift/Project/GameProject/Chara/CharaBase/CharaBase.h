#pragma once
#include"ObjectBase/ObjectBase.h"
class NavNode;

//重力加速度
#define GRAVITY (0.02f)

//キャラクターのベースクラス
class CharaBase : public ObjectBase
{
protected:
	NavNode* m_navNode;
	bool m_isGround;		//着地フラグ
	CVector3D m_scale;		//キャラクター描画サイズ
public:
	//コンストラクタ
	CharaBase(ETaskTag tag);

	//デストラクタ
	virtual ~CharaBase();

	//衝突判定
	void Collision(Task* t);

	NavNode* GetNavNode() const;

	//更新
	void Update();
};

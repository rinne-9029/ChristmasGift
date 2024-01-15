#include"EnemyManager.h"
#include"Enemy.h"

//敵の管理クラスのインスタンス
EnemyManager* EnemyManager::ms_instance = nullptr;
//敵の探索位置ノードのリスト
std::list<SearchNode> EnemyManager::ms_searchNodes =
{
	CVector3D(2.369029,0,-0.000122),
	/*CVector3D(-12.544582,0.410701,8.687490),
	CVector3D(15.687225,0.420055,4.950093),
	CVector3D(14.911342,0.420055,10.190742),
	CVector3D(10.591820,0.420055,10.477141),
	CVector3D(9.257686,5.773851,7.193727),
	CVector3D(9.013831,0.420055,4.341067),*/
};

//コンストラクタ
EnemyManager::EnemyManager()
	:CharaBase(ETaskTag::eEnemyManager,true)
{
	m_remove = true;
}

//デストラクタ
EnemyManager::~EnemyManager()
{
	ms_instance = nullptr;
}

//インスタンスを取得
EnemyManager* EnemyManager::Instance()
{
	//インスタンスがなければ
	if (ms_instance == nullptr)
	{
		//インスタンスを生成する
		ms_instance = new EnemyManager();
	}
	return ms_instance;
}

//敵をリストに追加
void EnemyManager::Add(Enemy* enemy)
{
	m_enemies.push_back(enemy);
}

//敵をリストから取り除く
void EnemyManager::Remove(Enemy* enemy)
{
	m_enemies.remove(enemy);
}

//次に探索するノードを取得
SearchNode* EnemyManager::GetNextSearchNode() const
{
	//□探索ノードの選択条件
	//�@他の敵が探索中のノードは選択しない
	//�A存在確率が一番高いノードを選択する
	
	SearchNode* ret = nullptr;
	//リストの先頭から順番に調べて、
	//一番条件に近い一致するノードを取得する
	for (SearchNode& node : ms_searchNodes)
	{
		//既に他の敵が探索中のノードは対象外
		if (node.enemy != nullptr) continue;
		//戻り値のノードがまだ設定されていないもしくは、
		//存在確率が検索中のノードの法が高いのであれば、
		//検索中のノードを優先する
		if (ret == nullptr || node.prob > ret->prob)
		{
			ret = &node;
		}
	}
	return ret;
}

//更新
void EnemyManager::Update()
{
	for (SearchNode& node : ms_searchNodes)
	{
		node.prob = Utility::Clamp01(node.prob + 0.0005f);
	}
}

//描画
void EnemyManager::Render()
{
	if (!g_isRenderDebug) return;

	for (SearchNode& node : ms_searchNodes)
	{
		float per = node.prob;
		CVector3D color;
		if (per > 0.5f)
		{
			color = CVector3D::Leap
			(
				CVector3D(1.0f, 1.0f, 0.0f),
				CVector3D(1.0f, 0.0f, 0.0f),
				(per - 0.5f) / 0.5f
			);
		}
		else
		{
			color = CVector3D::Leap
			(
				CVector3D(0.0f, 1.0f, 0.0f),
				CVector3D(1.0f, 1.0f, 0.0f),
				per / 0.5f
			);
		}
		Utility::DrawCube(node.pos, 2.0f, CVector4D(color, 1.0f));
	}
}
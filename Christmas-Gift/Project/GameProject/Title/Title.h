#pragma once

//タイトル画面管理クラス

class Title : public Task {
private:
	CImage m_TitleText;		//タイトル名テキスト
	CImage m_StartText;		//スタートテキスト
	CImage m_ManualText;	//説明テキスト
	CImage m_RankingText;	//ランキングテキスト
	CImage m_Manual1;		//説明書１
	CImage m_Manual2;		//説明書２
	int m_select;			//セレクトフラグ
	int m_step;				
	float m_fuwafuwa;		//ふわふわ表示用実数
	CVector2D m_snowPos;	//雪の座標
	void FuwaFuwa();		//ふわふわ表示処理
	void ModeChenge();		//モード変更処理
	void ManualMode();		//説明モード処理
	void ManualDraw();		//説明描画
	void StageSelecte();	//ステージ選択処理
	void StageDraw();		//ステージ選択描画
public:
	//コンストラクタ
	Title();
	//デストラクタ
	~Title();
	//更新処理
	void Update();
	//2D描画処理
	void Draw();
};
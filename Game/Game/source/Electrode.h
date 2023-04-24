#pragma once
class Electrode
{
public:
	Electrode();
	~Electrode();
	//初期化処理
	void Initialize(VECTOR Pos,bool is_san);
	//更新処理
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	//描画処理
	void Render();

	// 3Dモデル描画用
	int handle;				//モデルデータ
	VECTOR vPos;			//位置
	int handleCol;			//モデルの当たり判定用変数
	int handleSANelectrode;	//元モデル１
	int handleLKAelectrode;	//元モデル２
	bool isSan = false;     //trueならサン、falseならルカ
	bool change = false;	//モデル変更通知
};

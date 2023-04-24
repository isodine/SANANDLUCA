#pragma once

class Elevator
{
public:
	Elevator();
	~Elevator();
	//初期化処理
	void Initialize();
	//更新処理
	void Update(Electrode& electr);
	//削除処理
	void Terminate();
	//描画処理
	void Render();
	//移動処理
	void Move();

	// 3Dモデル描画用
	int handle;								//モデルデータ
	int handleCol;							//モデルの当たり判定用変数
	VECTOR vPos;							//位置
	VECTOR vPosfirst;						//初期ベクトル
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//動くスピード
	float upRange = 200.f;					//上昇上限値
	float downRange = 0.f;					//下降下限値
	bool floating = false;					//フラグその１
	bool moving = false;					//フラグその２
};

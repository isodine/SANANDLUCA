#pragma once

class Tube
{
public:
	Tube();
	~Tube();
	//初期化処理
	void Initialize(int Type, VECTOR Pos);
	//更新処理
	void Update(Electrode& electr);
	//描画処理
	void Render();
	//回転処理
	void Spin();
	void TubeTouch();
	void SetSanLka(SAN* _san, LKA* _lka);

	// 3Dモデル描画用
	int handle;								//モデルデータ
	int handleCol;							//モデルの当たり判定用変数
	VECTOR vPos;							//位置
	VECTOR vDir;							//向き
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//動くスピード
	float rightRange = 90.f;				//右回転限界値
	float leftRange = -90.f;				//左回転限界値
	float frontRange = 0.f;					//正面角度
	bool spining = false;

	//今向いている方向
	enum TubeType
	{
		Neutrality,
		San,
		Lka
	};
	TubeType Type;

	//今向いている方向
	enum DirType
	{
		Front,
		Right,
		Left
	};
	DirType Dir;

	SAN* san;
	LKA* lka;
};

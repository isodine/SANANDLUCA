/**
 * @file BossSwamp.h
 * @brief ボスに属性がついた状態で壁にぶつかると出てくる沼のプログラム
 * @author 磯島武尊
 * @date March 2023
 */

#pragma once
class BossSwamp
{
public:
	void ModelInitialize();
	void Initialize(bool IsSan,VECTOR Pos,int handleSan, int handleLka);
	void Update(std::vector<std::unique_ptr<BossSwamp>>& swamps);
	void Render();
	void CollCheck(std::vector<std::unique_ptr<BossSwamp>>& swamps);

	// 3Dモデル描画用
	int handleBaseSan;			//元モデル１
	int handleBaseLka;			//元モデル１
	int handle;					//モデルデータ
	VECTOR vPos;				//位置
	int handleCol;				//モデルの当たり判定用変数
	bool isSan = true;			//trueならサン、falseならルカ
	bool neutralization = false;//trueなら中和した、falseなら中和してない(中和=消える)
	float diameter = 90;		//直径の長さ
};

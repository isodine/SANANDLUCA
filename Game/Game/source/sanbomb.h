#pragma once
#include "PlayerBomb.h"

//サンのボムのクラス
class SanBomb :public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	//初期化処理
	void Initialize(SAN& san);
	//更新処理
	void Update(SAN& san);
	//削除処理
	void Terminate();
	//描画処理
	void Render();
	//球の移動処理
	void Throw(SAN& san);
	//ボムの消去
	void Bombdead();

	void EffectReset();
private:
	int _effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int _playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int _isthrow = 0;
	int IsPlaying = -1;
	int _KeyEf, _TrgEf;
	float _hight, _throw;
	float _position_x, _position_y, _position_z;
	bool Isbombdead;					//消去通知
};
/**
 * @file playerbomb.cpp
 * @brief ボムのベースクラス
 * @author 磯島武尊
 * @date January 2023
 */

PlayerBomb::PlayerBomb() {}

PlayerBomb::~PlayerBomb() {}

void PlayerBomb::SetSan(SAN& San)
{
	san = San;
}

void PlayerBomb::SetLka(LKA& Lka) {
	lka = Lka;
}
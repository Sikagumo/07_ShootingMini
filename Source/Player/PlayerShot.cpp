#include "PlayerShot.h"
#include <DxLib.h>


/// <summary>
/// デフォルトコンストラクタ
/// </summary>
PlayerShot::PlayerShot(void)
{

}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerShot::Init(void)
{
	modelId_ = MV1LoadModel(HANDLE); // プレイヤー弾モデル割り当て

	pos_ = { 0.0f, 0.0f, 0.0f}; // 位置割り当て
	posStart_ = pos_.z; // 発射位置

	isAlive_ = false; // 弾無効化
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerShot::Update(void)
{
	if (isAlive_)
	{
		// モデル位置割り当て
		MV1SetPosition(modelId_, pos_);

		// 移動処理
		pos_.z += MOVE_SPEED;

		// 発射後、ある程度進行したら無効化
		if (pos_.z >= (posStart_ + SHOT_ALIVE_POS))
		{
			isAlive_ = false;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerShot::Draw(void)
{
	if (isAlive_)
	{
		MV1DrawModel(modelId_); // モデル

		// 当たり判定
#ifdef _DEBUG
		DrawSphere3D(pos_, RADIUS, 10, 0xFF00FF, 0x00FF, false);
#endif
	}
}

/// <summary>
/// 解放処理
/// </summary>
void PlayerShot::Release(void)
{
	MV1DeleteModel(modelId_); // プレイヤー弾解放
}

/// <summary>
/// 現在位置取得
/// </summary>
/// <returns>現在位置</returns>
VECTOR PlayerShot::GetPos(void)
{
	return pos_;
}

/// <summary>
/// 有効判定取得
/// </summary>
/// <returns>有効か否か</returns>
bool PlayerShot::GetIsAlive(void)
{
	return isAlive_;
}

/// <summary>
/// 発射有効処理
/// </summary>
/// <param name="pos">発射対象の位置</param>
void PlayerShot::SetShotActive(VECTOR shotTarget)
{
	// 弾有効時は無効化
	if (isAlive_) return;

	pos_	  = shotTarget;	// 発射位置割り当て
	posStart_ = pos_.z;		// 発射位置開始位置

	// モデル位置割り当て
	MV1SetPosition(modelId_, pos_);

	isAlive_ = true; // 弾有効化
}

/// <summary>
/// 弾丸有効フラグ割り当て
/// </summary>
/// <param name="active">有効にするか否か</param>
void PlayerShot::SetIsAlive(bool active)
{
	isAlive_ = active;
}
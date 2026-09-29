#include "../Application.h"
#include "../Common/Camera.h"
#include "PlayerShot.h"
#include "Player.h"
#include <DxLib.h>


/// <summary>
/// デフォルトコンストラクタ
/// </summary>
Player::Player(void)
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Init(Application* app, Camera* camera)
{
	app_	= app;	  // メインクラス割り当て
	camera_ = camera; // カメラクラス割り当て

	modelId_ = MV1LoadModel(MODEL_HANDLE); // プレイヤーモデル

	VECTOR start = START_POS; // 開始位置
	start.x = camera_->GetPos().x; // カメラ位置に調整

	pos_ = start; // 位置割り当て

	isAlive_ = true; // 生存フラグ有効化
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(void)
{
	if (isAlive_)
	{
		// ゲーム中だけ、左右操作有効
		if (app_->GetGameState() == Application::GAME_STATE::GAME_ACTIVE)
		{
			// 左移動
			if (CheckHitKey(KEY_INPUT_A) && pos_.x > (camera_->GetPos().x - MOVE_OFFSET))
			{
				pos_.x -= MOVE_X;
			}

			// 右移動
			if (CheckHitKey(KEY_INPUT_D) && pos_.x < (camera_->GetPos().x + MOVE_OFFSET))
			{
				pos_.x += MOVE_X;
			}
		}
		if (app_->GetGameState() == Application::GAME_STATE::GAME_CLEAR) 
		{
			// クリア時に中央に移動させる
			if (pos_.x < START_POS.x)pos_.x += (MOVE_X / 2);
			if (pos_.x > START_POS.x)pos_.x -= (MOVE_X / 2);
		}

		pos_.z += MOVE_Z;
		MV1SetPosition(modelId_, pos_); // プレイヤー位置割り当て
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw(void)
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
void Player::Release(void)
{
	MV1DeleteModel(modelId_);  // プレイヤーモデル解放
}

/// <summary>
/// プレイヤー座標取得
/// </summary>
/// <returns>プレイヤー座標</returns>
VECTOR Player::GetPos(void)
{
	return pos_;
}

/// <summary>
/// プレイヤー生存フラグ取得
/// </summary>
/// <returns>生存フラグ</returns>
bool Player::GetIsAlive(void)
{
	return isAlive_;
}

/// <summary>
/// プレイヤー生存フラグ割り当て
/// </summary>
/// <param name="alive">生存するか否か</param>
void Player::SetIsAlive(bool alive)
{
	isAlive_ = alive;
}
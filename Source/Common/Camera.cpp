#include "../Player/Player.h"
#include "Camera.h"
#include <DxLib.h>


Camera::Camera(void)
{
	pos_ = START_CAMERA_POS;
}


void Camera::Init(Player* player)
{
	player_ = player; // プレイヤー取得

	pos_ = START_CAMERA_POS; // カメラ位置割り当て

	// カメラの初期化 (SetDrawScreenの後、描画処理の前にカメラを設定する!)[
	// 再設定しないと、初期位置に戻る
	SetCameraPositionAndAngle(pos_, 0.0f, 0.0f, 0.0f);
}

void Camera::Update(void)
{
	// プレイヤー生存時に移動処理
	if (player_->GetIsAlive() == true)
	{
		pos_.z += Player::MOVE_Z;
	}
}

void Camera::SetBeforDraw(void)
{
	// カメラの設定 (SetDrawScreenの後、描画処理の前にカメラを設定する!)
	// 再設定しないと、初期位置に戻る
	SetCameraPositionAndAngle(pos_, 0.0f, 0.0f, 0.0f);
}

VECTOR Camera::GetPos(void)
{
	return pos_;
}

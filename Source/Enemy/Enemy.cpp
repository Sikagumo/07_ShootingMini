#include "../Common/Camera.h"
#include "../Application.h"
#include "Enemy.h"
#include <DxLib.h>


Enemy::Enemy(void)
{

}


void Enemy::Init(Application* app, Camera* camera)
{
	camera_ = camera; // カメラ割り当て
	app_ = app;

	SetSpawnPos();
	MV1SetPosition(modelId_, pos_); // 敵位置割り当て

	modelId_ = MV1LoadModel(HANDLE); // 敵モデル割り当て

	VECTOR size = { SIZE, SIZE, SIZE };
	MV1SetScale(modelId_, size);			// サイズ割り当て
	MV1SetRotationXYZ(modelId_, rotation_);	// 角度割り当て

	isAlive_ = true; // 敵生存化
}


void Enemy::Update(void)
{
	if (app_->GetGameState() == Application::GAME_STATE::GAME_CLEAR) return;

	MV1SetPosition(modelId_, pos_); // モデル位置割り当て

	switch (state_)
	{
		case STATE::MOVE_FORWARD:
		{
			pos_.z -= MOVE_Z;
		}
		break;

		case STATE::MOVE_WID:
		{
			if (isMoveChange_)
			{
				moveForce_.x += MOVE_X;

				pos_.x += MOVE_X;

				if (moveForce_.x > MOVE_X_RANGE)
				{
					isMoveChange_ = false;
				}
			}
			else
			{
				moveForce_.x -= MOVE_X;

				pos_.x -= MOVE_X;

				if (moveForce_.x < -MOVE_X_RANGE)
				{
					isMoveChange_ = true;
				}
			}
		}
		break;
	}

	if (app_->GetGameState() == Application::GAME_STATE::GAME_OVER) return;

	// 敵生成処理
	if (pos_.z < camera_->GetPos().z || !isAlive_)
	{
		SetSpawnPos(); // 生成処理
	}
}

void Enemy::Draw(void)
{
	if (isAlive_)
	{
		MV1DrawModel(modelId_); // モデル描画

		// 当たり判定
#ifdef _DEBUG
		DrawSphere3D(pos_, 40.0f, 10, 0xFFFF, 0xFF, false);
#endif
	}
}

void Enemy::Release(void)
{
	MV1DeleteModel(modelId_);	 // 敵モデル解放
}

VECTOR Enemy::GetPos(void)
{
	return pos_;
}

bool Enemy::GetIsAlive(void)
{
	return isAlive_;
}

void Enemy::SetIsAlive(bool active)
{
	isAlive_ = active;
}


void Enemy::SetSpawnPos(void)
{
	VECTOR pos = START_POS; // 開始位置割り当て

	// 横位置割り当て
	int randX = GetRand(SPAWN_X_RANGE * 2) - SPAWN_X_RANGE;	// 左右均等にランダム割り当て
	float x	  = static_cast<float>(randX - SPAWN_X_OFFSET);
	pos.x = x;

	// 奥生成位置 割り当て
	int randZ = GetRand(SPAWN_Z_RANGE * 2) - SPAWN_X_RANGE + SPAWN_Z_OFFSET;
	float z	  = camera_->GetPos().z + randZ;
	pos.z = z;

	pos_ = pos; // 位置割り当て


	// 状態ランダム割り当て
	int state = GetRand(static_cast<int>(STATE::MAX));
	state_ = static_cast<STATE>(state);

	isMoveChange_ = false;
	moveForce_ = { 0,0,0 };

	isAlive_ = true; // 敵有効化
}
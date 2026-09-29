#include "Camera.h"
#include "Stage.h"
#include <DxLib.h>


/// <summary>
/// デフォルトコンストラクタ
/// </summary>
Stage::Stage(void)
{
	camera_ = nullptr;
}

/// <summary>
/// 初期化処理
/// </summary>
void Stage::Init(Camera* camera)
{
	camera_ = camera; // カメラ割り当て

	pos_ = pos2_ = START_STAGE_POS;
	pos2_.z = STAGE_OFFSET; // 生成位置を変更

	modelId_  = MV1LoadModel(HANDLE); // ステージモデル割り当て
	modelId2_ = MV1LoadModel(HANDLE); // ステージモデル割り当て

	MV1SetPosition(modelId_, pos_);   // ステージ位置割り当て
	MV1SetPosition(modelId2_, pos2_); // ステージ位置割り当て

	VECTOR size = { STAGE_SIZE, STAGE_SIZE, STAGE_SIZE };
	MV1SetScale(modelId_, size);  // ステージサイズ割り当て
	MV1SetScale(modelId2_, size); // ステージサイズ割り当て
}

/// <summary>
/// 更新処理
/// </summary>
void Stage::Update(void)
{
	if (camera_->GetPos().z > stageLoopOffset_)
	{
		stageLoopOffset_ += STAGE_OFFSET;

		VECTOR statePos;
		if (isLoopStage_)
		{
			statePos = { pos_.x, pos_.y, pos_.z = stageLoopOffset_ };
			MV1SetPosition(modelId_, pos_ = statePos); // 位置割り当て
			isLoopStage_ = false; // ステージ２を移動させるようにする
		}
		else
		{
			statePos = { pos2_.x, pos2_.y, pos2_.z = stageLoopOffset_ };
			MV1SetPosition(modelId2_, pos2_ = statePos); // 位置割り当て
			isLoopStage_ = true; // ステージ１を移動させるようにする
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Stage::Draw(void)
{
	MV1DrawModel(modelId_);  // 前方モデル1描画
	MV1DrawModel(modelId2_); // 後方モデル2描画
}

/// <summary>
/// 解放処理
/// </summary>
void Stage::Release(void)
{
	MV1DeleteModel(modelId2_);  // ステージモデル2解放
	MV1DeleteModel(modelId_);   // ステージモデル1解放
}
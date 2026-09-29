#include "Blast.h"
#include <DxLib.h>


Blast::Blast(void)
{

}


void Blast::Init(void)
{
	LoadDivGraph("Data/Image/Blast.png",
		(IMAGE_NUM.x * IMAGE_NUM.y), IMAGE_NUM.x, IMAGE_NUM.y,
		IMAGE_SIZE.x, IMAGE_SIZE.y, images_);

	pos_ = { 0.0f, 0.0f, 0.0f }; // 爆破位置
	animCount_ = 0; // 爆発カウンタ初期化
	isActive_ = false; // 爆発無効化
}

void Blast::Update(void)
{
	if (isActive_)
	{
		animCount_++; // 爆破アニメーション再生
		if (animCount_ >= (IMAGE_NUM.x * IMAGE_NUM.y))
		{
			isActive_  = false; // 爆破フラグ無効化
			animCount_ = 0;		// カウンタ初期化
		}
	}
}

void Blast::Draw(void)
{
	if (isActive_)
	{
		// 爆発遅延値
		int lateAnimCount = (animCount_ / ANIM_LATE);

		// ビルボードで描画
		DrawBillboard3D(pos_, 0.5f, 0.5f, 300.0f, 0.0f,
						images_[lateAnimCount], true);
	}
}

void Blast::Release(void)
{
	int max = (IMAGE_NUM.x * IMAGE_NUM.y);
	for (int i = 0; i < max; i++) 
	{
		DeleteGraph(images_[i]); // 画像解放
	}
}


void Blast::SetBlastActive(VECTOR pos)
{
	pos_ = pos; // 位置割り当て

	isActive_ = true; // 爆破有効化
}

bool Blast::GetIsActive(void) const
{
	return isActive_;
}
#pragma once
#include <DxLib.h>

class Blast
{
public:

	const char* BLAST_HANDLE = "Data/Image/Blast.png"; // 爆発画像ハンドル

	static constexpr VECTOR IMAGE_SIZE = { 96, 96 }; // 1画像サイズ
	static constexpr VECTOR IMAGE_NUM  = { 6,  4 }; // 画像数
	static constexpr int ANIM_LATE = 2; // アニメーション遅延値

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Blast(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~Blast(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(void);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(void);

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release(void);

	/// <summary>
	/// 爆破有効化処理
	/// </summary>
	/// <param name="pos">爆破対象の位置</param>
	void SetBlastActive(VECTOR pos);

	/// <summary>
	/// 爆発有効判定
	/// </summary>
	/// <returns>爆発が有効中か否か</returns>
	bool GetIsActive(void) const;

private:

	int images_[24]; // 画像ハンドル
	int animCount_;	 // 爆発アニメーションカウンタ
	VECTOR pos_;	 // 爆破位置
	bool isActive_;	 // 爆破有効か否か
};
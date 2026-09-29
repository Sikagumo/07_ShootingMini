#pragma once
#include <DxLib.h>
class Player;

class Camera
{
public:

	// カメラ開始位置
	static constexpr VECTOR START_CAMERA_POS = { 0.0f, 200.0f, -550.0f };

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Camera(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~Camera(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Player* player);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void);

	/// <summary>
	/// 描画前のカメラ設定
	/// </summary>
	void SetBeforDraw(void);

	/// <summary>
	/// カメラ位置取得
	/// </summary>
	/// <returns>カメラ位置</returns>
	VECTOR GetPos(void);


private:

	Player* player_; // プレイヤークラス

	VECTOR pos_; // カメラ位置
};
#pragma once
#include <DxLib.h>

class PlayerShot
{
public:

	const char* HANDLE = "Data/Model/Shot.mv1"; // モデルハンドル
	static constexpr float SHOT_ALIVE_POS = 6000.0f; // 弾生存距離
	static constexpr float MOVE_SPEED = 80.0f;	 // 弾速度
	static constexpr float RADIUS = 40.0f;	 // 半径

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	PlayerShot(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~PlayerShot(void) = default;

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
	/// 現在位置取得
	/// </summary>
	/// <returns>現在位置</returns>
	VECTOR GetPos(void);

	/// <summary>
	/// 有効判定取得
	/// </summary>
	/// <returns>有効か否か</returns>
	bool GetIsAlive(void);

	/// <summary>
	/// 発射有効処理
	/// </summary>
	/// <param name="pos">発射対象の位置</param>
	void SetShotActive(VECTOR shotTarget);

	/// <summary>
	/// 弾丸有効フラグ割り当て
	/// </summary>
	/// <param name="active">有効にするか否か</param>
	void SetIsAlive(bool active);


private:

	int modelId_;	 // モデルハンドル
	float posStart_; // 発射開始位置
	VECTOR pos_;	 // 弾位置
	bool isAlive_;	 // 弾の生存判定
};
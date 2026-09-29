#pragma once
#include <DxLib.h>
class Application;
class Camera;
class PlayerShot;

class Player
{
public:
	const char* MODEL_HANDLE = "Data/Model/Player.mv1"; // モデルハンドル

	static constexpr VECTOR START_POS = { 0.0f, 25.0f, -10.0f }; // 開始位置
	static constexpr float RADIUS = 80.0f;  // 当たり判定の半径

	static constexpr float MOVE_X = 15.5f;  // 横移動速度
	static constexpr float MOVE_Z = 22.5f;  // 奥移動速度
	static constexpr float MOVE_OFFSET = 350.0f; // 移動領域


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Player(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~Player(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Application* app, Camera* camera);

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
	/// プレイヤー座標取得
	/// </summary>
	/// <returns>プレイヤー座標</returns>
	VECTOR GetPos(void);

	/// <summary>
	/// プレイヤー生存フラグ取得
	/// </summary>
	/// <returns>生存フラグ</returns>
	bool GetIsAlive(void);

	/// <summary>
	/// プレイヤー生存フラグ割り当て
	/// </summary>
	/// <param name="alive">生存するか否か</param>
	void SetIsAlive(bool alive);


private:

	Application* app_; // アプリクラス
	Camera* camera_; // カメラクラス

	int modelId_;  // モデルハンドル
	VECTOR pos_;   // 座標
	bool isAlive_; // 生存フラグ
};
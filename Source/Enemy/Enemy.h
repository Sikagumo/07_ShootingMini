#pragma once
#include <DxLib.h>
class Camera;
class Application;

class Enemy
{
public:

	enum class STATE
	{
		NONE,		 // 何もなし
		MOVE_FORWARD, // 前進
		MOVE_WID,	  // 左右移動
		MAX,
	};

	const char* HANDLE = "Data/Model/Enemy.mv1"; // 敵モデルハンドル
	static constexpr VECTOR START_POS	 = { 80.0f, 50.0f, 4000.0f }; // 敵開始位置
	static constexpr float RADIUS		 = 40.0f;	// 敵当たり判定の半径
	static constexpr float SIZE			 = 0.1f;	// 敵サイズ

	static constexpr float MOVE_X = 5.0f; // 横移動速度
	static constexpr float MOVE_X_RANGE = (MOVE_X * 40.0f); // 横移動速度
	static constexpr float MOVE_Z = 20.0f; // 前後移動速度

	static constexpr int SPAWN_X_RANGE	= 300;	// 敵横生成範囲
	static constexpr int SPAWN_X_OFFSET	= 100;	// 敵生成位置間隔
	static constexpr int SPAWN_Z_RANGE	= 500; // 敵再出現範囲
	static constexpr int SPAWN_Z_OFFSET = 4000;	// 敵生成位置間隔

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Enemy(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~Enemy(void) = default;

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
	/// 敵位置取得
	/// </summary>
	/// <returns>敵の現在位置</returns>
	VECTOR GetPos(void);

	/// <summary>
	/// 敵生存フラグ判定
	/// </summary>
	/// <returns>敵が生存しているか否か</returns>
	bool GetIsAlive(void);

	/// <summary>
	/// 敵生存フラグ割り当て
	/// </summary>
	/// <param name="active">有効にするか否か</param>
	void SetIsAlive(bool active);


private:

	Camera* camera_; // カメラクラス
	Application* app_;

	STATE state_; // 状態
	int modelId_; // 敵モデルハンドル
	VECTOR pos_; // 敵開始位置
	VECTOR moveForce_; // 移動量
	VECTOR rotation_ = { 0.0f, 180.f * DX_PI_F / 180.0f, 0.f }; // 敵開始角度
	bool isAlive_ = true; // 敵有効化フラグ

	bool isMoveChange_ = false; // 移動変更するか否か


	/// <summary>
	/// 生成位置割り当て処理
	/// </summary>
	void SetSpawnPos(void);
};
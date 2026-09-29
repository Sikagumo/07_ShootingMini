#pragma once
#include <DxLib.h>
class Camera;
class Blast;
class Stage;
class Enemy;
class Player;
class PlayerShot;
class UI;

class Application
{
public:

	enum class GAME_STATE
	{
		NONE,
		GAME_ACTIVE,	   // ゲーム開始
		GAME_CLEAR,	   // ゲームクリア
		GAME_OVER, // ゲームオーバー
	};

	// 画面サイズ
	static constexpr VECTOR SCREEN_SIZE = { 1024, 768 };

	// ゲームクリア位置
	static constexpr float GAME_CLEAR_POS_Z = 10000.0f;

	static constexpr float MAX_SHOT_TIME = 0.1f; // 最大発射間隔
	static constexpr int MAX_SHOT_NUM = 8; // 最大弾数

	static constexpr int MAX_ENEMY = 5; // 最大敵生成数


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Application(void);

	/// <summary>
	/// 通常デストラクタ
	/// </summary>
	~Application(void) = default;

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
	/// ゲーム状態取得
	/// </summary>
	/// <returns>現在のゲーム状態</returns>
	Application::GAME_STATE GetGameState(void) const;


private:

	Application::GAME_STATE gameState_; // ゲーム状態

	Camera* camera_;
	Blast* blasts_[MAX_ENEMY]; // 爆発
	Stage* stage_;
	UI* ui_;

	Enemy* enemys_[MAX_ENEMY];
	Player* player_;
	PlayerShot* playerShot_[MAX_SHOT_NUM];

	float shotTime_; // 発射間隔



	/// <summary>
	/// ゲーム状態遷移処理
	/// </summary>
	/// <param name="stateType">遷移後の状態</param>
	void ChangeGameState(Application::GAME_STATE stateType);

	/// <summary>
	/// 当たり判定処理
	/// </summary>
	void Collision(void);

	/// <summary>
	/// 当たり判定の判定
	/// </summary>
	/// <param name="pos1">対象１の位置</param>
	/// <param name="pos2">対象２の位置</param>
	/// <param name="radius1">対象１の半径</param>
	/// <param name="radius2">対象２の半径</param>
	/// <param name="alive1">対象１の生存判定</param>
	/// <param name="alive2">対象２の生存判定</param>
	/// <returns>衝突しているか否か</returns>
	bool IsCollision(const VECTOR& pos1, const VECTOR& pos2, float radius1, float radius2, bool alive1, bool alive2);

	/// <summary>
	/// 爆発有効化処理
	/// </summary>
	/// <param name="target">対象の位置</param>
	void ActiveBlast(const VECTOR& target);
};
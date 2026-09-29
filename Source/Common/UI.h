#pragma once
#include <DxLib.h>
class Application;

class UI
{
public:

	static constexpr int GAMECLEAR_Y_OFFSET = -85;
	static constexpr int GAMEOVER_Y_OFFSET  = -85;

	const char* GAMEOVER_HANDLE = "Data/Image/GameOver.png";  // ゲームオーバー画像ハンドル
	const char* GAMECLEAR_HANDLE = "Data/Image/GameClear.png"; // ゲームクリア画像ハンドル


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	UI(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~UI(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Application* app);

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

private:

	Application* app_; // アプリクラス

	int gameOverImageId_;  // ゲームオーバー画像ハンドル
	int gameClearImageId_; // ゲームクリア画像ハンドル
};
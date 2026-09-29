#include "../Application.h"
#include "UI.h"
#include <DxLib.h>


/// <summary>
/// デフォルトコンストラクタ
/// </summary>
UI::UI(void)
{

}

/// <summary>
/// 初期化処理
/// </summary>
void UI::Init(Application* app)
{
	app_ = app; // プレイヤークラス割り当て

	// ゲームオーバー画像
	gameOverImageId_ = LoadGraph(GAMEOVER_HANDLE);

	// ゲームクリア画像
	gameClearImageId_ = LoadGraph(GAMECLEAR_HANDLE);
}

/// <summary>
/// 更新処理
/// </summary>
void UI::Update(void)
{

}

/// <summary>
/// 描画処理
/// </summary>
void UI::Draw(void)
{
	if (app_->GetGameState() == Application::GAME_STATE::GAME_CLEAR)
	{
		// ゲームクリア
		DrawRotaGraph((Application::SCREEN_SIZE.x / 2),
					  (Application::SCREEN_SIZE.y / 2) + GAMECLEAR_Y_OFFSET,
					   1.0, 0.0, gameClearImageId_, true);
	}
	else if (app_->GetGameState() == Application::GAME_STATE::GAME_OVER)
	{
		// ゲームオーバー
		DrawRotaGraph((Application::SCREEN_SIZE.x / 2),
					  (Application::SCREEN_SIZE.y / 2) + GAMEOVER_Y_OFFSET,
					  1.0, 0.0, gameOverImageId_, true);
	}
}

/// <summary>
/// 解放処理
/// </summary>
void UI::Release(void)
{
	DeleteGraph(gameClearImageId_);	 // ゲームクリア画像解放
	DeleteGraph(gameOverImageId_);   // ゲームオーバー画像解放
}
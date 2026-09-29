#include "Application.h"
#include "Common/FrameRate.h"
#include <DxLib.h>


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 画面サイズ
	SetWindowText("2416026 中川原諒"); //タイトル
	SetGraphMode(Application::SCREEN_SIZE.x, Application::SCREEN_SIZE.y, 32);
	ChangeWindowMode(true); // フルスクリーンにしないか否か

	// DxLibの3DのDirectX11で動作させるようにする
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	SetWaitVSyncFlag(false); // 垂直同期無効化

	// DxLibの初期化
	if (DxLib_Init() == -1) return -1;

	Application* app = new Application;
	app->Init(); // 初期化処理
	FrameRate::CreateInstance();
	FrameRate& fps = FrameRate::GetInstance();


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Update();

		if (fps.GetLimitFrameRate() == false)
		{
			fps.SetFrameRate();

			app->Update(); // 更新処理
		}

		app->Draw(); // 描画処理
		fps.Draw();

		// 描画スクリーンを切り替える
		ScreenFlip();
	}

	app->Release(); // 解放処理
	fps.Release(); // 解放処理
	
	delete app; // メインクラス削除

	// DxLibを終了
	if (DxLib_End() == -1) return -1;

	return 0;
}
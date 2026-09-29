#include "Common/Blast.h"
#include "Common/Stage.h"
#include "Common/UI.h"

#include "Player/Player.h"
#include "Player/PlayerShot.h"
#include "Enemy/Enemy.h"
#include "Common/Camera.h"
#include "Application.h"
#include <DxLib.h>


Application::Application(void)
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Application::Init(void)
{
	DATEDATA data; // 乱数シード値設定

	GetDateTime(&data); // 現在時刻を取得

	// 乱数初期値設定
	// 設定するランダムで出方が変わる数値
	SRand(data.Year + data.Mon + data.Day + data.Hour + data.Sec);

	gameState_ = GAME_STATE::GAME_ACTIVE;


	camera_ = new Camera;
	player_ = new Player;
	stage_ = new Stage; // ステージ初期化
	ui_	   = new UI;	// UI初期化


	camera_->Init(player_);
	player_->Init(this, camera_);
	stage_->Init(camera_);
	ui_->Init(this);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// 爆発初期化
		blasts_[i] = new Blast;
		blasts_[i]->Init();

		// 敵初期化
		enemys_[i] = new Enemy;
		enemys_[i]->Init(this, camera_);
	}
	for (int i = 0; i < MAX_SHOT_NUM; i++)
	{
		// 弾初期化
		playerShot_[i] = new PlayerShot;
		playerShot_[i]->Init();
	}
	shotTime_ = 0;
}

/// <summary>
/// 描画処理
/// </summary>
void Application::Update(void)
{
	// プレイヤーが一定位置に移動したらゲームクリア
	if (gameState_ == GAME_STATE::GAME_ACTIVE &&
		player_->GetPos().z >= GAME_CLEAR_POS_Z)
	{
		ChangeGameState(GAME_STATE::GAME_CLEAR);
	}

	camera_->Update(); // カメラ更新
	player_->Update(); // プレイヤー更新

	if (gameState_ == Application::GAME_STATE::GAME_ACTIVE)
	{
		for (int i = 0; i < MAX_SHOT_NUM; i++)
		{
			if (playerShot_[i]->GetIsAlive() == true)
			{
				playerShot_[i]->Update(); // 弾丸更新
			}
		}

		if (shotTime_ > 0)
		{
			shotTime_ -= 0.01f;
		}
		else if(CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_J))
		{
			for (int i = 0; i < MAX_SHOT_NUM; i++)
			{
				if (playerShot_[i]->GetIsAlive() == true) continue;

				// 発射有効処理
				playerShot_[i]->SetShotActive(player_->GetPos());
				shotTime_ = MAX_SHOT_TIME;

				break;
			}
		}
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		enemys_[i]->Update(); // 敵更新

		// ゲームクリア時、敵全員爆破
		if (enemys_[i]->GetIsAlive() && gameState_ == GAME_STATE::GAME_CLEAR)
		{
			ActiveBlast(enemys_[i]->GetPos());

			enemys_[i]->SetIsAlive(false);
		}
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		blasts_[i]->Update(); // 爆発更新
	}

	stage_->Update(); // ステージ更新

	Collision(); // 当たり判定処理
}

/// <summary>
/// 当たり判定処理
/// </summary>
void Application::Collision(void)
{
	// ゲーム時にのみ有効
	if (gameState_ != Application::GAME_STATE::GAME_ACTIVE) return;


	for (int e = 0; e < MAX_ENEMY; e++)
	{
		// 敵とプレイヤー弾の当たり判定
		for (int s = 0; s < MAX_SHOT_NUM; s++)
		{
			if (IsCollision(playerShot_[s]->GetPos(), enemys_[e]->GetPos(),
				PlayerShot::RADIUS, Enemy::RADIUS,
				playerShot_[s]->GetIsAlive(), enemys_[e]->GetIsAlive()))
			{

				enemys_[e]->SetIsAlive(false); // 敵無効化
				playerShot_[s]->SetIsAlive(false); // 弾無効化

				ActiveBlast(enemys_[e]->GetPos()); // 爆破有効化
			}
		}

		// プレイヤーと敵の当たり判定
		if (IsCollision(player_->GetPos(), enemys_[e]->GetPos(),
			Player::RADIUS, Enemy::RADIUS,
			player_->GetIsAlive(), enemys_[e]->GetIsAlive()))
		{
			gameState_ = Application::GAME_STATE::GAME_OVER; // ゲームオーバー化

			player_->SetIsAlive(false); // プレイヤー無効化

			ActiveBlast(player_->GetPos());
		}
	}
}


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
bool Application::IsCollision(const VECTOR& pos1, const VECTOR& pos2, float radius1, float radius2, bool alive1, bool alive2)
{
	// どちらかが無効時、処理終了
	if (alive1 == false || alive2 == false) return false;

	VECTOR dis;
	dis.x = (pos1.x - pos2.x);
	dis.y = (pos1.y - pos2.y);
	dis.z = (pos1.z - pos2.z);

	// 中央の距離
	float midPos = ((dis.x * dis.x) + (dis.y * dis.y) + (dis.z * dis.z));
	float rad = (radius1 + radius2); // (両者の半径)

	// 円形衝突処理
	return midPos <= (rad * rad);
}

/// <summary>
/// 描画処理
/// </summary>
void Application::Draw(void)
{
	// 描画スクリーンをバックに設定
	SetDrawScreen(DX_SCREEN_BACK);

	// 描画スクリーンを初期化
	ClearDrawScreen();

	camera_->SetBeforDraw(); // カメラ描画処理

	stage_->Draw(); // ステージ描画

	player_->Draw(); // プレイヤー描画

	if (gameState_ == Application::GAME_STATE::GAME_ACTIVE)
	{
		for (int i = 0; i < MAX_SHOT_NUM; i++)
		{
			if (playerShot_[i]->GetIsAlive() == true)
			{
				playerShot_[i]->Draw();
			}
		}	
	}	

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		enemys_[i]->Draw(); // 敵描画

		blasts_[i]->Draw(); // 爆破描画
	}

	ui_->Draw(); // UI描画


	/* デバッグテキスト */
#ifdef _DEBUG
	int textY = 16;
	int yState = 16;

	DrawString(0, textY, "シューティングゲーム", 0xFF);
	textY += yState;
	DrawString(0, textY, "2416026", 0xFFFFFF);
	textY += yState;
	DrawFormatString(0, textY, 0xFFFFFF, "PlayerPos：(%.1f, %.1f, %.1f, 半径:%.1f)", player_->GetPos().x, player_->GetPos().y, player_->GetPos().z, Player::RADIUS);
#endif
}

/// <summary>
/// 解放処理
/// </summary>
void Application::Release(void)
{
	ui_->Release();			// UI解放
	stage_->Release();		// ステージ解放
	player_->Release();		// プレイヤー解放

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		enemys_[i]->Release();		// 敵解放
		delete enemys_[i];		// 敵削除

		blasts_[i]->Release();		// 爆破解放
		delete blasts_[i];		// 爆破削除
	}

	for (int i = 0; i < MAX_SHOT_NUM; i++)
	{
		playerShot_[i]->Release(); // 弾解放
		delete playerShot_[i];
	}

	delete ui_;			// UI削除
	delete stage_;		// ステージ削除
	delete player_;		// プレイヤー削除
}


/// <summary>
/// ゲーム状態取得
/// </summary>
/// <returns>現在のゲーム状態</returns>
Application::GAME_STATE Application::GetGameState(void) const
{
	return gameState_;
}

/// <summary>
/// ゲーム状態遷移処理
/// </summary>
/// <param name="stateType">遷移後の状態</param>
void Application::ChangeGameState(Application::GAME_STATE stateType)
{
	gameState_ = stateType;
}


void Application::ActiveBlast(const VECTOR& target)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (blasts_[i]->GetIsActive()) continue;

		blasts_[i]->SetBlastActive(target); // 爆破有効化

		break; // 処理終了
	}
}
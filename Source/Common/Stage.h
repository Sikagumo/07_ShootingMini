#pragma once
#include <DxLib.h>
class Camera;

class Stage
{
public:

	const char* HANDLE = "Data/Model/Stage.mv1";

	static constexpr float STAGE_OFFSET = 7500.0f; // ステージ配置座標
	static constexpr float STAGE_SIZE = 10.0f; // ステージサイズ

	static constexpr VECTOR START_STAGE_POS = { 0.0f, -30.0f, -200.0f };


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Stage(void);

	/// <summary>
	/// デストラクタ処理
	/// </summary>
	~Stage(void) = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Camera* camera);

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

	Camera* camera_; // カメラクラス

	int modelId_;  // 前方ステージ1モデルハンドル
	int modelId2_; // 後方ステージ2モデルハンドル

	VECTOR pos_;   // ステージ1位置
	VECTOR pos2_;  // ステージ2位置

	float stageLoopOffset_ = STAGE_OFFSET;	// ループ後の領域
	bool isLoopStage_ = true; // ステージ１の位置を変更するか否か

};
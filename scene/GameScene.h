#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <RailCamera.h>
#include <Skydome.h>
#include <sstream>
#include "TimedCall.h"
#include "PrimitiveDrawer.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	
	/// <summary>
	/// 衝突判定と応答
	/// </summary>

	void CheckAllCollisions();

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void AddEnemy(Enemy* enemy);

	void EnemyIni(Model* model, const Vector3 position);

	void LoadEnemyPopData();

	void UpDateEnemyPopCommands();

	

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデルデータ
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	// スカイドーム
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	// Enemy* enemy_ = nullptr;


	// 次元発動のリスト
	std::list<TimedCall*> timedCalls_;


	std::list<EnemyBullet*> enemyBullets_;
	std::list<Enemy*> enemys_;

	std::stringstream enemyPopCommands;
	bool isWait_ = false;
	int32_t waitTimer_ = 0;


	int32_t scene_ = 0;
	// クリアまでにかかる時間
	int32_t timer_ = 60 * 30;

	// タイトル画像
	Sprite* titleSprite_ = nullptr;
	uint32_t titleTexture_ = 0;

	// クリア画像
	uint32_t clearTexture_ = 0;
	Sprite* clearSprite_ = nullptr;

	// UI画像
	Sprite* UISprite_ = nullptr;
	uint32_t UITexture_ = 0;

	

	PrimitiveDrawer* primitiveDrawer_ = nullptr;


	Sphere sphere1;
	AABB aabb1;

	Vector4 color;

	Matrix4x4 viewprojectionMatrix;
	Matrix4x4 viewportMatrix;

	int enemyKillCount;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
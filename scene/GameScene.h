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
#include "Dust.h"
#include "Beam.h"

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

	void AddDust(Dust* dust);

	void AddBeam(Beam* beam);

	uint32_t GetDustTexture() { return dustTextureHandle_; }

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

	std::list<Dust*> dusts_;
	std::list<Beam*> beams_;

	uint32_t dustTextureHandle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
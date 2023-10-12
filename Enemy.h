#pragma once
#include "EnemyBullet.h"
#include "IEnemyState.h"
#include "EnemyStateEntry.h"
#include "EnemyStateApproach.h"
#include "EnemyStateLeave.h"
#include "MT.h"
#include "Model.h"
#include "Player.h"
#include "TimedCall.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "newMath.h"
#include <list>
#include "Dust.h"
#include "ReFire.h"

#define MAXDUST 200
#define MAXReFire 0

class Player;
class GameScene;

class Enemy;
class IEnemyState;

class Enemy {

public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position,Model* dustModel,uint32_t& dustTexture, Model* reFireModel, uint32_t& reFireTexture);

	void Update();

	void Draw(const ViewProjection& view);

	void ChangeState(IEnemyState* newEnemyState);

	WorldTransform GetWT() { return worldTransform_; }

	void SetPosition(Vector3 speed);

	// 攻撃

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	static const int kShotInterval = 60;

	bool IsDead() const { return isDead_; }

	// 衝突を検証したら呼び出される関数
	void OnCollision();
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void ChangePosition(Vector3 vector);

	bool isFire;

	bool IsLeaveChangeStatePosition();

	bool IsApproachChangeStatePosition();

	bool GetIsAlive() { return isAlive_; }

	void Attack();

	void Fire();

	void SpawnDusts();

	void SpawnReFire();
private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;


	Player* player_ = nullptr;

	IEnemyState* state;

	GameScene* gameScene_ = nullptr;

	// 弾
	std::list<EnemyBullet*> bullets_;

	std::list<TimedCall*> timedCall_;

	int timer = 0;

	bool isDead_ = false;

	bool isAlive_;

	std::list<std::unique_ptr<Dust>> dusts_;

	std::list <std::unique_ptr<ReFire>> ReFires_;

	Model* dustModel_;
	uint32_t dustTextureHandle_;

	uint32_t reFireTextureHandle_ = 0;
	Model* reFireModel_ = 0;
};
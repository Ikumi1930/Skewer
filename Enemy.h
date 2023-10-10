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
#include "Particle.h"

class Player;
class GameScene;

class Enemy;
class IEnemyState;
/**
enum class Phase {
	Approach,
	Leave,
};

class EnemyState {

protected:
	Enemy* enemy_ = nullptr;

public:
	virtual void SetEnemy(Enemy* enemy) { enemy_ = enemy; }
	virtual void Update(){};
};

class EnemyStateApproah : public EnemyState {

public:
	void Update();
};

class EnemyStateLeave : public EnemyState {

public:
	void Update();
};
**/
class Enemy {

public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position);

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

	void SpawnParticles();
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

	std::list <Particle*> particle_;
};
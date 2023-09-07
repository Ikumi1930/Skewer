#pragma once
#include "Player.h"
#include "Enemy.h"

class CollisionManager {
public:

	void Initialize();
	void Update();

	void Colliders();

	void CheckAllCollision();

	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

	/// <summary>
	/// 弾を発射し、タイマーをリセットするコールバック関数
	/// <param name="colliderA">コライダーA</param>
	/// <param name="colliderB">コライダーB</param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
private:
	std::list<Collider*> colliders_;

	Player* player_;
	Enemy* enemy_;
};
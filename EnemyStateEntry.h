#pragma once
#include "IEnemyState.h"
#include "MT.h"
#include "Vector3.h"

class Enemy;

// 画面外から
class EnemyStateEntry : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;

private:
	Vector3 move = {};

	Vector3 acceleration = {};
};
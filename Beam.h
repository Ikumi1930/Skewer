#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MT.h"
#include "vector3.h"

class Enemy;
class GameScene;

class Beam
{
public:
	void Initialize(Model* model, const Vector3& position, uint32_t textureHandle);

	void Update();

	void Draw(const ViewProjection& view);

	bool GetIsDead() { return isDead_; }

	//void Spawn();
private:
	WorldTransform worldTransform_;

	Enemy* enemy_;
	GameScene* gameScene_;

	Model* model_;
	uint32_t texturehandle_;

	Vector3 velocity_;

	Vector3 acceleration_;

	static const int32_t kLifeTime = 100;
	// デスタイマー
	int32_t deathtimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

	float velocityXZ_ = 0;
};


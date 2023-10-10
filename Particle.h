#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MT.h"
#include "vector3.h"

class Enemy;

class Particle
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& view);
private:
	WorldTransform worldTransform_;

	Enemy* enemy_;

	Model* model_;
	uint32_t texturehandle_;

	Vector3 velocity_;

	Vector3 acceleration_;

	static const int32_t kLifeTime = 10;
	// デスタイマー
	int32_t deathtimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};


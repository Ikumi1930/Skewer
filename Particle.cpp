#include "Particle.h"
#include <assert.h>
#include "Enemy.h"

void Particle::Initialize(Model* model, const Vector3& position) {

	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("gakugakun2.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = {(float)GetRandom(-2,2),(float)GetRandom(-2,2) ,(float)GetRandom(-2,2) };
	acceleration_ = { 0.001f,0.001f,0.001f };
	isDead_ = false;
}

void Particle::Update() {
	if (!isDead_) {
		velocity_ = Add(velocity_, acceleration_);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		worldTransform_.UpdateMatrix();
	}
	// 時間経過でデス
	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}
}

void Particle::Draw(const ViewProjection& view) {
	if (!isDead_) {
		model_->Draw(worldTransform_, view, texturehandle_);
	}
}
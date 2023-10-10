#include "Dust.h"
#include <assert.h>
#include "Enemy.h"
#include "GameScene.h"

void Dust::Initialize(Model* model, const Vector3& position, uint32_t textureHandle) {

	assert(model);
	model_ = model;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = { (float)GetRandom(-2,2),(float)GetRandom(-2,2) ,(float)GetRandom(-2,2) };
	acceleration_ = { 0.001f,0.001f,0.001f };
	isDead_ = false;
}

void Dust::Update() {
	if (!isDead_) {
		//velocity_ = Add(velocity_, acceleration_);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		worldTransform_.UpdateMatrix();
	}
	// 時間経過でデス
	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}
}

void Dust::Draw(const ViewProjection& view) {
	if (!isDead_) {
		model_->Draw(worldTransform_, view, texturehandle_);
	}
}

//void Dust::Spawn() {
//	Dust* newDust = new Dust();
//	newDust->Initialize(model_, enemy_->GetWorldPosition(), texturehandle_);
//	gameScene_->AddDust(newDust);
//	//Dust_.push_back(newDust);
//}
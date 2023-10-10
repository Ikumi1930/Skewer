#include "Beam.h"
#include <assert.h>
#include "Enemy.h"
#include "GameScene.h"

void Beam::Initialize(Model* model, const Vector3& position, uint32_t textureHandle) {

	assert(model);
	model_ = model;
	texturehandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = { (float)GetRandom(-2,2),(float)GetRandom(-2,2) ,(float)GetRandom(-2,2) };
	acceleration_ = { 0.001f,0.001f,0.001f };
	isDead_ = false;
}

void Beam::Update() {
	if (!isDead_) {
		// 座標を移動させる（1フレーム分の移動量を足しこむ)
		//Vector3 toReticle = Subtract(player_->GetReticleWorldPosition(), worldTransform_.translation_);

		////ベクトルを正規化する
		//toReticle = Normalize(toReticle);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// Y軸周り角度(0y)
		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);

		velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
		// X軸周り角度(0x)
		worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ_);

		worldTransform_.UpdateMatrix();
	}
	// 時間経過でデス
	if (--deathtimer_ <= 0) {
		isDead_ = true;
	}
}

void Beam::Draw(const ViewProjection& view) {
	if (!isDead_) {
		model_->Draw(worldTransform_, view, texturehandle_);
	}
}

//void Beam::Spawn() {
//	Beam* newBeam = new Beam();
//	newDust->Initialize(model_, enemy_->GetWorldPosition(), texturehandle_);
//	gameScene_->AddDust(newDust);
//	//Dust_.push_back(newDust);
//}
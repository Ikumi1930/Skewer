#include "Enemy.h"
#include "Player.h"
#include <assert.h>

Enemy::~Enemy() {

	//delete state;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

	for (TimedCall* timedCall : timedCall_) {
		delete timedCall;
	}
}




void Enemy::Initialize(Model* model, const Vector3& position) {

	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("gakugakun2.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	isAlive_ = true;
	state = new EnemyStateEntry();
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::ChangeState(IEnemyState* newEnemyState) {
	//delete state;

	state = newEnemyState;
}

void Enemy::SetPosition(Vector3 speed) {
	worldTransform_.translation_ = Math::Add(worldTransform_.translation_, speed);
}

/**
void EnemyStateApproah::Update() {
	Vector3 appSpeed(0, 0, -0.2f);
	enemy_->SetPosition(appSpeed);

	enemy_->Fire();

	if (enemy_->GetWT().translation_.z < 0.0f) {
		enemy_->ChangeState(new EnemyStateLeave);
	}
}

void EnemyStateLeave::Update() {
	Vector3 leaveSpeed(-0.2f, 0.2f, 0.2f);
	enemy_->SetPosition(leaveSpeed);

	enemy_->Fire();
}

**/

void Enemy::Update() {
	state->Update(this);

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
}



void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

	void Enemy::ChangePosition(Vector3 vector) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, vector);
}

bool Enemy::IsApproachChangeStatePosition() {
	bool isXComp{}, isYComp{};

	if (worldTransform_.translation_.x < 10.0f && worldTransform_.translation_.x > -10.0f) {
		isXComp = true;
	}
	if (worldTransform_.translation_.y < 10.0f && worldTransform_.translation_.y > -10.0f) {
		isYComp = true;
	}

	if (isXComp && isYComp) {
		return true;
	} else {
		return false;
	}
}

bool Enemy::IsLeaveChangeStatePosition() {
	if (worldTransform_.translation_.z < 80.0f) {
		return true;
	} else {
		return false;
	}
}
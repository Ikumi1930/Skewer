#include "Enemy.h"
#include "Player.h"
#include <assert.h>
#include "GameScene.h"

Enemy::~Enemy() {

	//delete state;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

	for (TimedCall* timedCall : timedCall_) {
		delete timedCall;
	}

	for (Dust* dust : dust_) {
		delete dust;
	}

	for (Beam* beam : beam_) {
		delete beam;
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
	Vector3 worldPos{};

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

	ImGui::Begin("enemyPos");
	ImGui::Text("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
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

void Enemy::OnCollision() {
	for (int i = 0; i < MAXDUST; i++) {
		SpawnDusts();
	}
	for (int i = 0; i < MAXBEAM; i++) {
 		SpawnBeam();
	}
}

void Enemy::Fire() {

	Attack();

	timedCall_.push_back(new TimedCall(std::bind(&Enemy::Fire, this), 60));
}

void Enemy::Attack() {
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 plaPos = player_->GetWorldPosition();
	Vector3 enePos = GetWorldPosition();
	Vector3 speed = {};
	speed.x = plaPos.x - enePos.x;
	speed.y = plaPos.y - enePos.y;
	speed.z = plaPos.z - enePos.z;
	speed = Math::Normalize(speed);
	speed.x *= kBulletSpeed;
	speed.y *= kBulletSpeed;
	speed.z *= kBulletSpeed;

	speed = Math::TransformNormal(speed, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, speed);
	// 弾を登録
	// bullet_ = newBullet;
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::SpawnDusts() {
	Dust* newDust = new Dust();
	newDust->Initialize(model_, worldTransform_.translation_,gameScene_->GetDustTexture());
	gameScene_->AddDust(newDust);
	//Dust_.push_back(newDust);
}

void Enemy::SpawnBeam() {
	Beam* newBeam = new Beam();
	newBeam->Initialize(model_, worldTransform_.translation_, gameScene_->GetDustTexture());
	gameScene_->AddBeam(newBeam);
}
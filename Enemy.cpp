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
}




void Enemy::Initialize(Model* model, const Vector3& position, Model* dustModel, uint32_t& dustTexture, Model* reFireModel, uint32_t& reFireTexture) {

	assert(model);
	model_ = model;
	texturehandle_ = TextureManager::Load("gakugakun2.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	isAlive_ = true;
	state = new EnemyStateEntry();

	dustModel_ = dustModel;
	dustTextureHandle_ = dustTexture;

	reFireModel_ = reFireModel;
	reFireTextureHandle_ = reFireTexture;
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


void Enemy::Update() {
	//state->Update(this);

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	//火花の更新
	for (std::list<std::unique_ptr<Dust>>::iterator dustIt = dusts_.begin(); dustIt != dusts_.end();) {
		Dust* dust = dustIt->get();

		if (dust->GetIsDead()) {
			dustIt = dusts_.erase(dustIt);
		}
		else {
			dust->Update();
			dustIt++;
		}
	}

	//残り火の更新
	for (std::list<std::unique_ptr<ReFire>>::iterator reFireIt = reFires_.begin(); reFireIt != reFires_.end();) {
		ReFire* reFire = reFireIt->get();

		if (reFire->GetIsDead()) {
			reFireIt = reFires_.erase(reFireIt);
		}
		else {
			reFire->Update();
			reFireIt++;
		}
	}

	ImGui::Begin("enemyPos");
	ImGui::Text("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::End();
}



void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);

	//火花を描画
	for(std::list<std::unique_ptr<Dust>>::iterator dustIt = dusts_.begin(); dustIt != dusts_.end();dustIt++){
		Dust* dust = dustIt->get();
		dustModel_->Draw(dust->GetWT(), view, dustTextureHandle_);
	}

	//残り火を描画
	for (std::list<std::unique_ptr<ReFire>>::iterator reFireIt = reFires_.begin(); reFireIt != reFires_.end(); reFireIt++) {
		ReFire* reFire = reFireIt->get();
		dustModel_->Draw(reFire->GetWT(), view, dustTextureHandle_);
	}
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
	for (int i = 0; i < MAXReFire; i++) {
 		SpawnReFire();
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
	std::unique_ptr<Dust> newDust = std::make_unique<Dust>();
	newDust->Initialize(worldTransform_.translation_);
	dusts_.push_back(std::move(newDust));
}

void Enemy::SpawnReFire() {
	std::unique_ptr<ReFire> newReFire = std::make_unique<ReFire>();
	newReFire->Initialize(worldTransform_.translation_);
	reFires_.push_back(std::move(newReFire));
}
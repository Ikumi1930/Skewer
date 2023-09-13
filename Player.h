﻿#pragma once

#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(ViewProjection& viewProjection);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	// 攻撃
	void Attack();

	Vector3 GetWorldPosition();

	// 衝突を検証したら呼び出される関数
	void OnCollision();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	void SetParent(const WorldTransform* parent);

	WorldTransform& GetWorldMatrix() { return worldTransform_; }

	void DrawUI();

	void MouseUpdate(ViewProjection& view);

	// デストラクタ
	~Player();

	//Vector3 GetReticleWorldPosition();

	bool GetIsAttack() { return isAttack; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Model* playerModel_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
	// ImGuiで値を入力する
	float inputFloat3[3] = {0, 0, 0};
	// 弾
	// PlayerBullet* bullet_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;

	bool isControl = false;
	bool isAttack = false;

	WorldTransform worldTransform3DReticle_;

	Sprite* sprite2DReticle_ = nullptr;

	
};
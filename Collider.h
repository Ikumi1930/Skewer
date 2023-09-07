#pragma once
#include "Vector3.h"

class Collider {
public:
	//半径を取得
	float GetRadius() { return radius_; }

	//半径を設定
	void SetRadius(float radius) { radius = radius_; }

	//衝突時に呼ばれる関数
	virtual void OnCollision() = 0;

	//ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;

	// 属性
	uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	void SetCollisionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}
	// マスク
	uint32_t GetCollisionMask() { return collisionMask_; }
	void SetCollisionMask(uint32_t collisionMask) { collisionMask_ = collisionMask; }

private:
	float radius_ = 2;

	//衝突属性（自分）
	uint32_t collisionAttribute_ = 0xffffffff;
	//衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;
};
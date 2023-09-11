#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	// delete modelSkydome_;
	delete skydome_;
	delete railCamera_;

	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}

	delete collisionManager_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	primitiveDrawer_ = PrimitiveDrawer::GetInstance();

	// テクスチャを読み込み
	textureHandle_ = TextureManager::Load("SusumePlayer1.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);
	// 敵の生成
	// enemy_ = new Enemy;
	// enemy_->SetPlayer(player_);
	// Vector3 position = {30.0f, 0.0f, 30.0f};
	// 敵初期化
	// enemy_->Initialize(model_, position);
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// アドレス渡し
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	skydome_ = new Skydome();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Initialize(modelSkydome_, {0, 80, 0});

	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, -100.0f}, player_->GetWorldMatrix().rotation_);

	player_->SetParent(&railCamera_->GetWorldTransform());

	// TextureManager::Load("beam.png");

	LoadEnemyPopData();

	collisionManager_ = new CollisionManager();
	collisionManager_->SetPlayer(player_);
	for (Enemy* enemy : enemys_) {
		collisionManager_->SetEnemy(enemy);
	}

	controlPoints_ = {
		{0,0,0},
		{10,10,0},
		{10,15,0},
		{20,15,0},
		{20,15,0},
		{20,0,0},
		{30,0,0}
	};

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	targetT_ = 1.0f / segmentCount;
}

void GameScene::UpdatePlayerPosition(float t) {
	Vector3 cameraPosition{};
	cameraPosition = CatmullRom(controlPoints_, t);
	railCamera_->SetPosition(cameraPosition);
}

void GameScene::Update() {
	

	for (size_t i = 0; i < segmentCount + 1; i++) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = CatmullRom(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	}

	// カメラの移動
	if (t_ < 0.99f) {
		t_ += 1.0f / segmentCount / 10;
	}
	else {
		t_ = 0.99f;
	}
	if (targetT_ < 0.99f) {
		targetT_ += 1.0f / segmentCount / 10;
	}
	else {
		targetT_ = 1.0f;
	}
	target_ = CatmullRom(controlPoints_, targetT_);
	UpdatePlayerPosition(t_);



	// 自キャラの更新

	player_->Update(viewProjection_);

	// enemy_->Update();

	UpDateEnemyPopCommands();

	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	collisionManager_->Update();
	skydome_->Update();

	// #ifdef _DEBUG

	if (input_->TriggerKey(DIK_RETURN) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_RETURN) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}
	// カメラの処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		railCamera_->Updata();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
	}
	// #endif

	// debugCamera_->Update();

	// 軸方向の表示を有効
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	skydome_->Draw(viewProjection_);

	// 3Dライン
	for (int i = 0; i < segmentCount - 1; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
			pointsDrawing_[i], pointsDrawing_[i + 1], { 1.0f, 0.0f, 0.0f, 1.0f });
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::AddEnemy(Enemy* enemy) { enemys_.push_back(enemy); }

void GameScene::EnemyIni(Model* model, const Vector3 position) {
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model, position, this);
	newEnemy->SetPlayer(player_);
	AddEnemy(newEnemy);
}

void GameScene::LoadEnemyPopData() {
	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpDateEnemyPopCommands() {

	if (isWait_) {
		waitTimer_--;

		if (waitTimer_ <= 0) {
			isWait_ = false;
		}
		return;
	}

	std::string line;

	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		} else if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			EnemyIni(model_, Vector3(x, y, z));
		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			isWait_ = true;
			waitTimer_ = waitTime;
			break;
		}
	}
}


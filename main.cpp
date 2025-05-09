#include <Novice.h>
#include <cmath>
#include"Function.h"

const char kWindowTitle[] = "LE2C_07_カトウ_ヒロキ_MT3";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*---変数の初期化---*/
	Function* function = new Function();

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f, 0.4f,-1.3f };
	Vector3 cross = function->Cross(v1, v2);

	Vector3 kLocalVertices[3]{
		{ 0.0f,  1.0f, 0.0f },  // 上
		{ 0.5f, -0.5f, 0.0f },  // 右下
		{ -0.5f, -0.5f, 0.0f }  //左下
	};

	Vector3 rotate{ 0.0f,0.0f,0.0f };

	Vector3 translate{ 0.0f,0.0f,0.0f };

	Vector3 cameraPosition{ 0.0f,0.0f, -10.0f };

	// 1行の高さ
	/*const int kRowHeight = 20;*/
	// 1列の幅
	//const int kcolumnWidth = 60;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		/*---キー入力---*/
		//前後
		if (keys[DIK_W])
		{
			translate.y += 0.1f;
		} 
		else if(keys[DIK_S])
		{
			translate.y -= 0.1f;
		}

		//左右
		if (keys[DIK_A])
		{
			translate.x -= 0.1f;
		}
		else if (keys[DIK_D])
		{
			translate.x += 0.1f;
		}

		//常に回転させる
		rotate.y -= 0.02f;


		Matrix4x4 worldMateix = function->MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = function->MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = function->Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = function->MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixの作成
		Matrix4x4 worldViewProjectionMatrix = function->Multiply(worldMateix, function->Multiply(viewMatrix, projectionMatrix));
		//viewPortMatrixの作成
		Matrix4x4 viewportMatrix = function->MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//screen空間へと頂点を変換
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i)
		{
			Vector3 ndcVectex = function->Transform(kLocalVertices[i], worldViewProjectionMatrix);

			screenVertices[i] = function->Transform(ndcVectex, viewportMatrix);
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);

		function->vectorScreenPrintf(0, 0, cross, "Cross");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

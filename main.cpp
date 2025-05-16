#include <Novice.h>
#include <cmath>
#include"Function.h"
#include"math.h"
#include <numbers>
#include<imgui.h>

const char kWindowTitle[] = "LE2C_07_カトウ_ヒロキ_MT3";


struct  Sphere
{
	//中心点
	Vector3  center;


	float radius;
};

Function function;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

void DrawGrid(Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix)
{
	//グリットの半分の幅
	const float  kGridHalfWidth = 2.0f;

	//分裂数
	const uint32_t kSubdivision = 10;

	//一つ分の長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);


	//奥から手前への線を順々に引いてく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		//上の情報を使ってワールド座標系上の始点と終点を求める
		float x = -kGridHalfWidth + kGridEvery * xIndex;

		Vector3 start = { x, 0.0f, -kGridHalfWidth };

		Vector3 end = { x, 0.0f, kGridHalfWidth };

		//スクリーン座標系まで変換をかける

		Vector3 screenStart = function.Transform(function.Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = function.Transform(function.Transform(end, viewProjectionMatrix), viewportMatrix);

		//変換した座標を使って描画
		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);


	}

	//左から右も同じように線を順々に引いてく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		//上の情報を使ってワールド座標系上の始点と終点を求める
		float z = -kGridHalfWidth + kGridEvery * zIndex;

		Vector3 start = { -kGridHalfWidth, 0.0f, z };
		Vector3 end = { kGridHalfWidth, 0.0f, z };

		//スクリーン座標系まで変換をかける
		Vector3 screenStart = function.Transform(function.Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = function.Transform(function.Transform(end, viewProjectionMatrix), viewportMatrix);

		//変換した座標を使って描画
		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);
	}
}

void DrawSphere(Sphere& sphere, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color)
{
	//分裂数
	const uint32_t kSubdivision = 16;

	//経度分割1つ分の角度
	const float kLonEvery = 2.0f * std::numbers::pi_v<float> / float(kSubdivision);

	//緯度分割1つ分の角度
	const float kLatEvery = std::numbers::pi_v<float> / float(kSubdivision);

	//緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++)
	{
		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;

		//経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++)
		{
			//現在の経度
			float lon = lonIndex * kLonEvery;

			//world座標系でのa,b,cを求める
			Vector3 a = {
			   sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
			   sphere.center.y + sphere.radius * sinf(lat),
			   sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};

			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon)
			};

			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery)
			};

			//a,b,cをScreen座標系まで変換
			Vector3 screenA = function.Transform(function.Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = function.Transform(function.Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = function.Transform(function.Transform(c, viewProjectionMatrix), viewportMatrix);

			//ab,acで線を引く
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*---変数の初期化---*/

	Sphere sphere =
	{
		{0.0f,0.0f-1.0f},

	 1.0f

	};

	Vector3 cameraRotate{ -0.26f,0.0f,0.0f };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	Vector3 cameraPosition{ 0.0f, 0.0f, 8.0f };

	uint32_t color = 0xFFFFFFFF;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMateix = function.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 cameraMatrix = function.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = function.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = function.MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixの作成
		Matrix4x4 worldViewProjectionMatrix = function.Multiply(worldMateix, function.Multiply(viewMatrix, projectionMatrix));
		//viewPortMatrixの作成
		Matrix4x4 viewportMatrix = function.MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate",&cameraTranslate.x,0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x,0.01f);
		ImGui::DragFloat3("cameraCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("cameraRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}




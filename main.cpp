#include <Novice.h>
#include <cmath>
#include"Function.h"
#include"math.h"
#include <algorithm>
#include <numbers>
#include<imgui.h>

const char kWindowTitle[] = "LE2C_07_カトウ_ヒロキ_MT3";


struct  Sphere
{
	//中心点
	Vector3  center;

	//半径
	float radius;

	//色
	uint32_t color;
};

struct Transform
{
	//スケール
	Vector3 scale;
	//回転
	Vector3 rotate;
	//位置
	Vector3 translate;
};

struct Plane
{
	//法線
	Vector3 normal;
	//距離
	float distance;
	//色
	uint32_t color;
};

struct Triangle
{
	//頂点
	Vector3 vertices[3];
	//色
	uint32_t color;
};

Function function;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y,vector.x,0.0f };
	}

	return{ 0.0f,-vector.z,vector.y };
}

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

void DrawPlane(const Plane& plane, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color)
{
	//中心点を求める
	Vector3 center = function.Vector3Multiply(plane.normal, plane.distance);

	//
	Vector3 perpendicular[4];
	perpendicular[0] = function.Normalize(Perpendicular(plane.normal));
	perpendicular[1] = { -perpendicular[0].x, -perpendicular[0].y,-perpendicular[0].z };
	perpendicular[2] = function.Cross(plane.normal, perpendicular[0]);
	perpendicular[3] = { -perpendicular[2].x, -perpendicular[2].y,-perpendicular[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++)
	{
		Vector3 extend = function.Vector3Multiply(perpendicular[index], 2.0f);
		Vector3 point = function.Vector3Add(center, extend);
		points[index] = function.Transform(function.Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	// 平面の四辺を描画
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}

void DrawTriangle(const Triangle& triangle, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenVertices[3];

	for (int i = 0; i < 3; ++i)
	{
		// ビュー・プロジェクション変換
		Vector3 projected = function.Transform(triangle.vertices[i], viewProjectionMatrix);

		// ビューポート変換
		screenVertices[i] = function.Transform(projected, viewportMatrix);
	}


	// 三辺を描画
	Novice::DrawLine(
		static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
		static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		color
	);
}

bool IsCollision(const Triangle& triangle, const Segment& segment)
{
	//各辺を結んだベクトルと頂点と衝突点pを結んだベクトルのクロス積を取る
	Vector3 cross01 = function.Cross();
	Vector3 cross12 = function.Cross();
	Vector3 cross20 = function.Cross();

	//全ての小三角形のクロス積と法線が同じ方向に向いていたら衝突
	if (function.Vector3Dot(cross01,) >= 0.0f &&
		function.Vector3Dot(cross12) >= 0.0f &&
		function.Vector3Dot() >= 0.0f )
	{
		return true;
	}

	return false;

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

	Transform  transform
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	//カメラ
	Transform  cameraPosition
	{
		{1.0f,1.0f,1.0f},
		{ 0.26f,0.0f,0.0f },
		{ 0.0f,1.9f,-6.25f },
	};

	//線
	Segment segment
	{
		{-2.0f,-1.0f, 0.0f},
		{ 3.0f, 2.0f, 2.0f},
		0xFFFFFFFF,
	};

	//球体
	Sphere sphere[2];
	sphere[0].center = { 0.0f,0.0f ,0.6f };
	sphere[0].radius = { 1.0f };
	sphere[0].color = 0xFFFFFFFF;
	sphere[1].center = { 1.7f,0.0f ,1.0f };
	sphere[1].radius = { 0.4f };
	sphere[1].color = 0xFFFFFFFF;

	//平面
	Plane plane
	{
		{0.0f,1.0f,0.0f},
		1.0f,
		0xFFFFFFFF,
	};

	//三角形
	Triangle triangle
	{
		{
			{ 0.0f,  1.0f, 0.0f },	// 頂点1
			{ 1.0f, -1.0f, 0.0f },  // 頂点2
			{-1.0f, -1.0f, 0.0f }   // 頂点3
		},

		0xFFFFFFFF
	};


	//カメラの操作用変数
	int mouseX = 0;
	int mouseY = 0;
	int preMouseX = 0;
	int preMouseY = 0;;
	int mouseWheel = 0;
	bool isRightMouseDown = false;

	Transform initialCameraPosition = cameraPosition;

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



#pragma region "カメラ操作"

		//カメラのマウス操作
		preMouseX = mouseX;
		preMouseY = mouseY;
		mouseWheel = Novice::GetWheel();
		Novice::GetMousePosition(&mouseX, &mouseY);
		isRightMouseDown = Novice::IsPressMouse(1);

		// 感度調整
		const float kRotateSensitivity = 0.001f;

		if (keys[DIK_W])
		{
			cameraPosition.translate.y += 0.01f;
		}

		if (keys[DIK_S])
		{
			cameraPosition.translate.y -= 0.01f;
		}

		if (keys[DIK_D])
		{
			cameraPosition.translate.x += 0.01f;
		}

		if (keys[DIK_A])
		{
			cameraPosition.translate.x -= 0.01f;
		}

		// カメラ回転
		if (isRightMouseDown)
		{
			float dx = float(mouseX - preMouseX);
			float dy = float(mouseY - preMouseY);

			//左右回転
			cameraPosition.rotate.y += dx * kRotateSensitivity;
			//上下回転
			cameraPosition.rotate.x += dy * kRotateSensitivity;

			// 上下回転を制限
			float limit = std::numbers::pi_v<float> / 2.0f;
			cameraPosition.rotate.x = std::clamp(cameraPosition.rotate.x, -limit, limit);
		}

		//ホイールでズーム
		cameraPosition.translate.z += float(mouseWheel) * kRotateSensitivity;

		//Rでリセット
		if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0)
		{
			cameraPosition = initialCameraPosition;
		}

#pragma endregion

		//当たり判定
		if (IsCollision(segment, plane))
		{
			segment.color = 0xFF0000FF;
		}
		else
		{
			segment.color = 0xFFFFFFFF;
		}


		Matrix4x4 worldMateix = function.MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
		Matrix4x4 cameraMatrix = function.MakeAffineMatrix(cameraPosition.scale, cameraPosition.rotate, cameraPosition.translate);
		Matrix4x4 viewMatrix = function.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = function.MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixの作成
		Matrix4x4 ViewProjectionMatrix = function.Multiply(worldMateix, function.Multiply(viewMatrix, projectionMatrix));
		//viewPortMatrixの作成
		Matrix4x4 viewportMatrix = function.MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 start = function.Transform(function.Transform(segment.origin, ViewProjectionMatrix), viewportMatrix);

		Vector3 end = function.Transform(function.Transform(function.Vector3Add(segment.origin, segment.diff), ViewProjectionMatrix), viewportMatrix);

		ImGui::Begin("window");
		ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("plane.Normal", &plane.normal.x, 0.01f);
		plane.normal = function.Normalize(plane.normal);
		ImGui::DragFloat("plane.distance", &plane.distance, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//グリッド
		DrawGrid(ViewProjectionMatrix, viewportMatrix);

		//球
		/*DrawSphere(sphere[0], ViewProjectionMatrix, viewportMatrix, sphere[0].color);*/

		//線
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), segment.color);

		//三角形
		DrawTriangle(triangle, ViewProjectionMatrix, viewportMatrix, triangle.color);

		//平面
		/*DrawPlane(plane, ViewProjectionMatrix, viewportMatrix, plane.color);*/




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

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

struct AABB
{
	Vector3 min;
	Vector3 max;
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

void DrawAABB(const AABB& aabb, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 vertices[8];

	// 1. AABBを構成する8頂点を計算（min/maxを使う）
	vertices[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	vertices[1] = { aabb.max.x, aabb.min.y, aabb.min.z };
	vertices[2] = { aabb.max.x, aabb.max.y, aabb.min.z };
	vertices[3] = { aabb.min.x, aabb.max.y, aabb.min.z };
	vertices[4] = { aabb.min.x, aabb.min.y, aabb.max.z };
	vertices[5] = { aabb.max.x, aabb.min.y, aabb.max.z };
	vertices[6] = { aabb.max.x, aabb.max.y, aabb.max.z };
	vertices[7] = { aabb.min.x, aabb.max.y, aabb.max.z };

	// 2. 各頂点を変換
	for (int i = 0; i < 8; ++i)
	{
		// ビュー・プロジェクション変換
		vertices[i] = function.Transform(vertices[i], viewProjectionMatrix);

		// ビューポート変換
		vertices[i] = function.Transform(vertices[i], viewportMatrix);
	}

	// 3. 12本のエッジを線で描画
	int edges[12][2] = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0}, // 前面
		{4, 5}, {5, 6}, {6, 7}, {7, 4}, // 背面
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 側面
	};

	for (int i = 0; i < 12; ++i)
	{
		Novice::DrawLine(static_cast<int>(vertices[edges[i][0]].x), static_cast<int>(vertices[edges[i][0]].y),
			static_cast<int>(vertices[edges[i][1]].x), static_cast<int>(vertices[edges[i][1]].y),
			color);
	}
}

bool IsCollision(const AABB& aabb, const Segment& segment)
{
	// 線分の始点
	Vector3 o = segment.origin;
	// 線分の方向ベクトル
	Vector3 b = segment.diff;

	// 線分上の交差開始点
	float tmin = 0.0f;

	// 線分上の交差終了点
	float tmax = 1.0f;

	// 浮動小数誤差許容範囲
	const float EPS = 1e-6f;

	// 各軸でスラブ交差判定
	for (int i = 0; i < 3; ++i)
	{
		// 現在の軸の線分始点成分
		float origin = (&o.x)[i];

		// 現在の軸の線分方向成分
		float dir = (&b.x)[i];

		// 現在の軸のAABB最小
		float slabMin = (&aabb.min.x)[i];

		// 現在の軸のAABB最大
		float slabMax = (&aabb.max.x)[i];

		if (fabs(dir) < EPS)
		{
			// 線分がスラブ面と平行な場合
			if (origin < slabMin || origin > slabMax)
			{
				return false;
			}
		}
		else
		{
			// t1, t2: スラブ面との交点のt
			float t1 = (slabMin - origin) / dir;
			float t2 = (slabMax - origin) / dir;

			// t1が小さいように順序調整
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}

			//AABBとの衝突点(貫通点)のtが小さい方
			tmin = max(tmin, t1);
			//AABBとの衝突点(貫通点)のtが大きい方
			tmax = min(tmax, t2);


			if (tmin > tmax)
			{
				//tminがtmaxより大きい場合は衝突しいない
				return false;
			}
		}
	}

	//衝突している
	return true;
}

//ベジェ曲線
//線形補間
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	return {
		v1.x + (v2.x - v1.x) * t,
		v1.y + (v2.y - v1.y) * t,
		v1.z + (v2.z - v1.z) * t
	};
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color)
{
	const int kNumSamples = 100;

	Vector3 prev{};

	Vector3 points[3] = { controlPoint0, controlPoint1, controlPoint2 };

	//ベジェ曲線
	for (int i = 0; i <= kNumSamples; ++i)
	{
		float t = static_cast<float>(i) / kNumSamples;

		// 線形補間を2回
		Vector3 p0 = Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1 = Lerp(controlPoint1, controlPoint2, t);
		Vector3 bezierPoint = Lerp(p0, p1, t);


		// ビュー・プロジェクション変換
		Vector3 projected = function.Transform(bezierPoint, viewProjectionMatrix);

		// ビューポート変換
		Vector3 screen = function.Transform(projected, viewportMatrix);

		// 線の描画
		if (i > 0)
		{
			Novice::DrawLine(static_cast<int>(prev.x), static_cast<int>(prev.y),
				static_cast<int>(screen.x), static_cast<int>(screen.y), color);

		}

		prev = screen;
	}

	//コントロールポイント
	for (int i = 0; i < 3; ++i)
	{
		// ビュー・プロジェクション変換
		Vector3 ndc = function.Transform(points[i], viewProjectionMatrix);

		// ビューポート変換
		Vector3 screen = function.Transform(ndc, viewportMatrix);

		//描画
		Novice::DrawEllipse(static_cast<int>(screen.x), static_cast<int>(screen.y),
			static_cast<int>(3.0f), static_cast<int>(3.0f), 0.0f, 0x000000FF, kFillModeSolid);
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

	Vector3 controlPoints[3] = {
		{-1.0f, 0.58f, 1.0f,},
		{1.76f, 1.0f, -0.3f,},
		{0.94f, -0.7f, 2.3f,},
	};

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f,0.0f,-0.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	uint32_t jointColors[3] = {
	0xFF0000FF, // 肩 → 赤
	0x00FF00FF, // 肘 → 緑
	0x0000FFFF  // 手 → 青
	};

	Vector3 jointPositions[3];

	Vector3 screenA;
	Vector3 screenB;

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


		// 関節のワールド行列
		Matrix4x4 jointWorldMatrix[3];

		// アフェイン変換
		jointWorldMatrix[0] = function.MakeAffineMatrix(
			scales[0], rotates[0], translates[0]
		);

		// 肘 → 肩に依存
		Matrix4x4 elbowLocal = function.MakeAffineMatrix(
			scales[1], rotates[1], translates[1]
		);

		jointWorldMatrix[1] = function.Multiply(elbowLocal, jointWorldMatrix[0]);

		// 手 → 肘に依存
		Matrix4x4 handLocal = function.MakeAffineMatrix(
			scales[2], rotates[2], translates[2]
		);


		jointWorldMatrix[2] = function.Multiply(handLocal, jointWorldMatrix[1]);




		Matrix4x4 worldMateix = function.MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
		Matrix4x4 cameraMatrix = function.MakeAffineMatrix(cameraPosition.scale, cameraPosition.rotate, cameraPosition.translate);
		Matrix4x4 viewMatrix = function.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = function.MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixの作成
		Matrix4x4 ViewProjectionMatrix = function.Multiply(worldMateix, function.Multiply(viewMatrix, projectionMatrix));
		//viewPortMatrixの作成
		Matrix4x4 viewportMatrix = function.MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		

		ImGui::Begin("window");
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//グリッド
		DrawGrid(ViewProjectionMatrix, viewportMatrix);


		for (int i = 0; i < 2; ++i)
		{
			Vector3 a = jointPositions[i];       // 現在の関節
			Vector3 b = jointPositions[i + 1];   // 次の関節

			screenA = function.Transform(function.Transform(a, ViewProjectionMatrix), viewportMatrix);

			screenB = function.Transform(function.Transform(b, ViewProjectionMatrix), viewportMatrix);

			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), 0xFFFFFFFF);
		}


		for (int i = 0; i < 3; ++i)
		{
			jointPositions[i] = { jointWorldMatrix[i].m[3][0], jointWorldMatrix[i].m[3][1], jointWorldMatrix[i].m[3][2] };

			Sphere s;
			s.center = jointPositions[i];
			s.radius = 0.1f;
			s.color = jointColors[i];

			DrawSphere(s, ViewProjectionMatrix, viewportMatrix, s.color);
		}


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



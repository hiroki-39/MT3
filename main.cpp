#include <Novice.h>
#include <cmath>
#include"Function.h"
#include <algorithm>
#include <numbers>
#include<imgui.h>

const char kWindowTitle[] = "LE2C_07_カトウ_ヒロキ_MT4";

Function function;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*---変数の初期化---*/
	Quaternion rotation = function.MakeRotateAxisAngleQuaternion(
		function.Normalize(Vector3{ 1.0f,0.4f, -0.2f }), 0.45f);
	Vector3 potintY = { 2.1f,-0.9f,1.3f };
	Matrix4x4 rotationMatrix = function.MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = function.RotateVector(potintY, rotation);
	Vector3 rotateByMatrix = function.Transform(potintY, rotationMatrix);

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


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 0, rotation, " : rotation");
		function.MatrixScreenPrintf(0, Function::kWindowHeight * 1, rotationMatrix, " : rotationMatrix");
		function.vectorScreenPrintf(0, Function::kWindowHeight * 6, rotateByQuaternion, " : rotateByQuaternion");
		function.vectorScreenPrintf(0, Function::kWindowHeight * 7, rotateByMatrix, " : rotateByQuaternion");

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



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

	/*---変数の初期化---*/;

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

		Quaternion rotation0 = function.MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = function.MakeRotateAxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);

		Quaternion interpolate0 = function.Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = function.Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = function.Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = function.Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = function.Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 0, interpolate0, " : interpolate0, Slerp(q0, q1 , 0.0f)");
		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 1, interpolate1, " : interpolate1, Slerp(q0, q1 , 0.3f)");
		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 2, interpolate2, " : interpolate2, Slerp(q0, q1 , 0.5f)");
		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 3, interpolate3, " : interpolate3, Slerp(q0, q1 , 0.7f)");
		function.QuaternionScreenPrintf(0, Function::kWindowHeight * 4, interpolate4, " : interpolate4, Slerp(q0, q1 , 1.0f)");

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



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
	Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
	Quaternion identity = function.IdentityQuaternion();
	Quaternion conj= function.Conjugate(q1);
	Quaternion inv = function.Inverse(q1);
	Quaternion normal = function.Normalize(q1);
	Quaternion mult1 = function.Multiply(q1, q2);
	Quaternion mult2 = function.Multiply(q2, q1);
	float norm = function.Norm(q1);

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
		
		// 四元数の計算結果を画面に表示
		int startX = 20;
		int startY = 20;
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 0, q1, "q1");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 1, q2, "q2");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 2, identity, "identity");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 3, conj, "conjugate");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 4, inv, "inverse");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 5, normal, "normalize");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 6, mult1, "q1 * q2");
		function.QuaternionScreenPrintf(startX, startY + Function::kWindowHeight * 7, mult2, "q2 * q1");
		Novice::ScreenPrintf(startX, startY + Function::kWindowHeight * 8, "norm(q1): %.03f", norm);

	
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



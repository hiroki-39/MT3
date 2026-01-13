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
	Vector3 from0 = function.Normalize({ 1.0f, 0.7f, 0.5f });
	Vector3 to0 = -from0;
	Vector3 from1 = function.Normalize({ -0.6f, 0.9f, 0.2f });
	Vector3 to1 = function.Normalize({ 0.4f,0.7f,-0.5f });
	
	Matrix4x4 rotMatrix0 = function.DirectionToDirection(
		function.Normalize({ 1.0f,0.0f,0.0f }),function.Normalize({ -1.0f,0.0f,0.0f }));

	Matrix4x4 rotMatrix1 = function.DirectionToDirection(from0, to0);
	Matrix4x4 rotMarix2 = function.DirectionToDirection(from1, to1);

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

		function.MatrixScreenPrintf(0, 0, rotMatrix0, "rotateMatrix0");
		function.MatrixScreenPrintf(0, Function::kWindowHeight * 5, rotMatrix1, "rotateMatrix1");
		function.MatrixScreenPrintf(0, Function::kWindowHeight * 10, rotMarix2, "rotateMatrix2");

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



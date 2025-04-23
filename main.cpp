#include <Novice.h>
#include <cmath>
#include"Function.h"

const char kWindowTitle[] = "LE2C_07_カトウ_ヒロキ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*---変数の初期化---*/
	Function* function = new Function();

	/*Vector3 v1 = { 1.0f, 3.0f, -5.0f };
	Vector3 v2 = { 4.0f, -1.0f, 2.0f };*/

	//float k = { 4.0f };

	/*Matrix4x4 m1 =
	{ 3.2f, 0.7f, 9.6f, 4.4f,
	  5.5f, 1.3f, 7.8f, 2.1f,
	  6.9f, 8.0f, 2.6f, 1.0f,
	  0.5f, 7.2f, 5.1f,3.3f
	};*/

	/*Matrix4x4 m2 =
	{ 4.1f, 6.5f, 3.3f, 2.2f,
	  8.8f, 0.6f, 9.9f, 7.7f,
	  1.1f, 5.5f, 6.6f, 0.0f,
	  3.3f, 9.9f, 8.8f, 2.2f
	};*/

	Vector3 scale = { 1.2f, 0.79f, -2.1f };
	Vector3 rotate = { 0.4f, 1.43f, -0.8f };
	Vector3 translate = { 2.7f, -4.15f, 1.57f };

	/*Vector3 point = { 2.3f, 3.8f, 1.4f };*/

	/*Matrix4x4 transformationMatrix =
	{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};*/

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

		/*---ベクトルの計算---*/ // 01_確認課題
	/*	Vector3 resultAdd = function->Add(v1, v2);
		Vector3 resultSubtract = function->Subtract(v1, v2);
		Vector3 resultMultiply = function->Multiply(v1, k);
		float resultDot = function->Dot(v1, v2);
		float resultLength = function->Length(v1);
		Vector3 resultNormalize = function->Normalize(v2);*/

		/*---行列の計算---*/ // 02_確認課題
		/*Matrix4x4 resultMatrixAdd = function->Add(m1, m2);
		Matrix4x4 resultMatrixMultiply = function->Multiply(m1, m2);
		Matrix4x4 resultMatrixSubtract = function->Subtract(m1, m2);
		Matrix4x4 resultMatrixInverseM1 = function->Inverse(m1);
		Matrix4x4 resultMatrixInverseM2 = function->Inverse(m2);
		Matrix4x4 resultMatrixTransposeM1 = function->Transpose(m1);
		Matrix4x4 resultMatrixTransposeM2 = function->Transpose(m2);
		Matrix4x4 resultMatrixIdentity = function->MakeIdentity();*/

		/*---拡大縮小行列と平行移動行列の計算---*/ // 03_確認課題
		/*Matrix4x4 scaleMatrix = function->MakeScaleMatrix(scale);
		Matrix4x4 translateMatrix = function->MakeTranslationMatrix(translate);
		Vector3 transformed = function->Transform(point, transformationMatrix);*/

		/*---回転行列の計算---*/ // 04_確認課題
		/*Matrix4x4 rotateXMatrix = function->MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = function->MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = function->MakeRotateZMatrix(rotate.z);
		Matrix4x4 rotateXYZMatrix = function->Multiply(rotateXMatrix, function->Multiply(rotateYMatrix,rotateZMatrix));*/

		/*---アフェイン変換行列の計算---*/ // 05_確認課題
		Matrix4x4 worldMatrix = function->MakeAffineMatrix(scale, rotate, translate);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*---ベクトルの描画---*/
		/*function->vectorScreenPrintf(0, 0, resultAdd, ":Add");
		function->vectorScreenPrintf(0, kRowHeight, resultSubtract, ":Subtract");
		function->vectorScreenPrintf(0, kRowHeight * 2, resultMultiply, ":Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		function->vectorScreenPrintf(0, kRowHeight * 5, resultNormalize, ": Normalize");*/

		/*---行列の計算---*/
		/*function->MatrixScreenPrintf(0, 0, resultMatrixAdd ,"Add");
		function->MatrixScreenPrintf(0, kRowHeight * 5, resultMatrixSubtract,"Subtracrt");
		function->MatrixScreenPrintf(0, kRowHeight * 10, resultMatrixMultiply,"Mulipty");
		function->MatrixScreenPrintf(0, kRowHeight * 15, resultMatrixInverseM1,"inverseM1");
		function->MatrixScreenPrintf(0, kRowHeight * 20, resultMatrixInverseM2,"inverseM2");
		function->MatrixScreenPrintf(kcolumnWidth * 5, 0, resultMatrixTransposeM1,"transposeM1");
		function->MatrixScreenPrintf(kcolumnWidth * 5, kRowHeight * 5, resultMatrixTransposeM2,"transposeM2");
		function->MatrixScreenPrintf(kcolumnWidth * 5, kRowHeight * 10, resultMatrixIdentity,"identity");*/

		/*---拡大縮小行列と平行移動行列の描画---*/
		/*function->vectorScreenPrintf(0, 0, transformed, "transformed");
		function->MatrixScreenPrintf(0, 20, translateMatrix, "translateMatrix");
		function->MatrixScreenPrintf(0, kRowHeight * 6, scaleMatrix, "scaleMatrix");*/

		/*---回転行列の描画---*/
		/*function->MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		function->MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		function->MatrixScreenPrintf(0, kRowHeight * 10, rotateZMatrix, "rotateZMatrix");
		function->MatrixScreenPrintf(0, kRowHeight * 15, rotateXYZMatrix, "rotateXYZMatrix");*/

		/*---アフェイン変換行列の描画---*/
		function->MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

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

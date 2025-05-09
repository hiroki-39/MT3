#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include"Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

class Function
{
public:
#pragma region "ベクトル"

	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="v1">変数1</param>
	/// <param name="v2">変数2</param>
	/// <returns>それぞれの合計値</returns>
	Vector3 Add(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="v1">変数1</param>
	/// <param name="v2">変数2</param>
	/// <returns>それぞれの合計値</returns>
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="v">変数1</param>
	/// <param name="scalar">変数2</param>
	/// <returns>それぞれの合計値</returns>
	Vector3 Multiply(const Vector3& v, float scalar);

	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="v1">変数1</param>
	/// <param name="v2">変数2</param>
	/// <returns>合計値</returns>
	float Dot(const Vector3& v1, const Vector3& v2);


	/// <summary>
	/// 長さ(ノルム)
	/// </summary>
	/// <param name="v">変数</param>
	/// <returns>長さの値</returns>
	float Length(const Vector3& v);

	/// <summary>
	/// 正規化
	/// </summary>
	/// <param name="v">変数</param>
	/// <returns>正規化した値</returns>
	Vector3 Normalize(const Vector3& v);
#pragma endregion

#pragma region "行列"
	/// <summary>
	/// 行列の加算
	/// </summary>
	/// <param name="m1">変数1</param>
	/// <param name="m2">変数2</param>
	/// <returns>値</returns>
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 行列の減算
	/// </summary>
	/// <param name="m1">変数1</param>
	/// <param name="m2">変数2</param>
	/// <returns>値</returns>
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 行列の積
	/// </summary>
	/// <param name="m1">変数1</param>
	/// <param name="m2">変数2</param>
	/// <returns>値</returns>
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="m">変数</param>
	/// <returns>値</returns>
	Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 逆行列(アフィン変換用)
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Matrix4x4 InverseAffine(const Matrix4x4& m);

	/// <summary>
	///転置行列
	/// </summary>
	/// <param name="m">変数</param>
	/// <returns>値</returns>
	Matrix4x4 Transpose(const Matrix4x4& m);

	/// <summary>
	/// 単位行列の作成
	/// </summary>
	/// <returns></returns>
	Matrix4x4 MakeIdentity();

#pragma endregion

#pragma region "拡大縮小、平行移動の行列"
	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	/// <param name="scale">変数</param>
	/// <returns>値</returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// 平行移動行列
	/// </summary>
	/// <param name="translate">変数</param>
	/// <returns>値</returns>
	Matrix4x4 MakeTranslationMatrix(const Vector3& translate);

	/// <summary>
	/// 座標変換行列
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns>値</returns>
	Vector3 Transform(const Vector3& vector, Matrix4x4& matrix);

#pragma endregion

#pragma region "3次元回転行列"
	/// <summary>
	/// X軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// Y軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// Z軸回転行列
	/// </summary>
	/// <param name="radion"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);

#pragma endregion

#pragma region "3次元のアフェイン変換行列"

	/// <summary>
	/// 3次元のアフィン変換行列
	/// </summary>
	/// <param name="scale">拡大縮小</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">平行移動</param>
	/// <returns>変換した値</returns>
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

#pragma endregion


	/*---レンダリングパイプライン---*/
    //透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	//正射影行列
	Matrix4x4 MakeOrthographicmatrix(float left, float top, float  right, float bottom, float nearClip, float farClip);

	//ビューポート変換行列 

	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	//クロス積
	Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="vector"></param>
	/// <param name="label"></param>
	void vectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

public:

	static const int kWindowWidth = 60;

	static const int kWindowHeight = 20;
};


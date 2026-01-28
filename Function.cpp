#include "Function.h"
#include <numbers>




/*---　3次元ベクトル ---*/
//加算
Vector3 Function::Vector3Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

//減算
Vector3 Function::Vector3Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

//スカラー倍
Vector3 Function::Vector3Multiply(const Vector3& v, float scalar) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

//内積
float Function::Vector3Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//長さ(ノルム)
float Function::Length(const Vector3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//正規化
Vector3 Function::Normalize(const Vector3& v) {
	float length = Length(v);
	Vector3 result;
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	} else {
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return result;
}

/*--- 3次元行列 ---*/
//行列の加算
Matrix4x4 Function::Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

//行列の減算	
Matrix4x4 Function::Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

//行列の積
Matrix4x4 Function::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

//逆行列
Matrix4x4 Function::Inverse(const Matrix4x4& m)
{
	Matrix4x4 result;

	// 行列式を計算 → 逆行列が存在するか確認
	float det =
		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - 
		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - 
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] - 
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] - 
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] + m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - 
		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3];

	// 行列式が0の場合、逆行列は存在しないのでそのままresultを返す
	if (det == 0.0f)
	{
		return result;
	}

	// 行列式が0でない場合、逆行列を計算

	float invDet = 1.0f / det;

	// 逆行列の計算式に従って各要素を計算	
	result.m[0][0] = invDet * (
		m.m[1][2] * m.m[2][3] * m.m[3][1] - m.m[1][3] * m.m[2][2] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][2] * m.m[3][3]);

	result.m[0][1] = invDet * (
		m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][3] * m.m[3][2] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][2] * m.m[3][3]);

	result.m[0][2] = invDet * (
		m.m[0][2] * m.m[1][3] * m.m[3][1] - m.m[0][3] * m.m[1][2] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][2] * m.m[3][3]);

	result.m[0][3] = invDet * (
		m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][3] * m.m[2][2] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][2] * m.m[2][3]);

	result.m[1][0] = invDet * (
		m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][3] * m.m[3][2] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][2] * m.m[3][3]);

	result.m[1][1] = invDet * (
		m.m[0][2] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][2] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][2] * m.m[3][3]);

	result.m[1][2] = invDet * (
		m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][3] * m.m[3][2] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][2] * m.m[3][3]);

	result.m[1][3] = invDet * (
		m.m[0][2] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][2] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][2] * m.m[2][3]);

	result.m[2][0] = invDet * (
		m.m[1][1] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][1] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][1] * m.m[3][3]);

	result.m[2][1] = invDet * (
		m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][0] * m.m[2][3] * m.m[3][1] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][1] * m.m[3][3]);

	result.m[2][2] = invDet * (
		m.m[0][1] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][1] * m.m[3][3]);

	result.m[2][3] = invDet * (
		m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][1] * m.m[2][3]);

	result.m[3][0] = invDet * (
		m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[1][0] * m.m[2][1] * m.m[3][2]);

	result.m[3][1] = invDet * (
		m.m[0][1] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] + m.m[0][0] * m.m[2][1] * m.m[3][2]);

	result.m[3][2] = invDet * (
		m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][0] * m.m[1][2] * m.m[3][1] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] - m.m[0][0] * m.m[1][1] * m.m[3][2]);

	result.m[3][3] = invDet * (
		m.m[0][1] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][1] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] + m.m[0][0] * m.m[1][1] * m.m[2][2]);

	return result;
}

//逆行列（アフィン変換用）
Matrix4x4 Function::InverseAffine(const Matrix4x4& m)
{
	Matrix4x4 result;

	// 回転部分を転置
	result.m[0][0] = m.m[0][0]; result.m[0][1] = m.m[1][0]; result.m[0][2] = m.m[2][0];
	result.m[1][0] = m.m[0][1]; result.m[1][1] = m.m[1][1]; result.m[1][2] = m.m[2][1];
	result.m[2][0] = m.m[0][2]; result.m[2][1] = m.m[1][2]; result.m[2][2] = m.m[2][2];

	// 平行移動部分に回転の逆をかける（転置行列×-位置）
	result.m[0][3] = -(result.m[0][0] * m.m[0][3] + result.m[0][1] * m.m[1][3] + result.m[0][2] * m.m[2][3]);
	result.m[1][3] = -(result.m[1][0] * m.m[0][3] + result.m[1][1] * m.m[1][3] + result.m[1][2] * m.m[2][3]);
	result.m[2][3] = -(result.m[2][0] * m.m[0][3] + result.m[2][1] * m.m[1][3] + result.m[2][2] * m.m[2][3]);

	// 最後の行は (0, 0, 0, 1)
	result.m[3][0] = result.m[3][1] = result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//転置行列
Matrix4x4 Function::Transpose(const Matrix4x4& m)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

//単位行列
Matrix4x4 Function::MakeIdentity()
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				result.m[i][j] = 1.0f;
			} else
			{
				result.m[i][j] = 0.0f;
			}
		}
	}

	return result;
}

/*--- その他 ---*/
//拡大縮小行列
Matrix4x4 Function::MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

//平行移動行列
Matrix4x4 Function::MakeTranslationMatrix(const Vector3& translate)
{
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

//座標変換行列
Vector3 Function::Transform(const Vector3& vector, Matrix4x4& matrix)
{
	Vector3 result;
	// 行列とベクトルの積を計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//X軸回転行列
Matrix4x4 Function::MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	// cos(radian)とsin(radian)を計算
	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	// X軸回転行列を作成
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cosRadian;
	result.m[1][2] = sinRadian;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -sinRadian;
	result.m[2][2] = cosRadian;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	// 行列を返す
	return result;
}

//Y軸回転行列
Matrix4x4 Function::MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;

	// cos(radian)とsin(radian)を計算
	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	// Y軸回転行列を作成
	result.m[0][0] = cosRadian;
	result.m[0][1] = 0.0f;
	result.m[0][2] = -sinRadian;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = sinRadian;
	result.m[2][1] = 0.0f;
	result.m[2][2] = cosRadian;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	// 行列を返す
	return result;
}

//Z軸回転行列
Matrix4x4 Function::MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;

	// cos(radian)とsin(radian)を計算
	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	// Z軸回転行列を作成
	result.m[0][0] = cosRadian;
	result.m[0][1] = sinRadian;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -sinRadian;
	result.m[1][1] = cosRadian;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	// 行列を返す
	return result;
}


Matrix4x4 Function::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result;
	// 拡大縮小行列
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	// 回転行列
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	// 平行移動行列
	Matrix4x4 translationMatrix = MakeTranslationMatrix(translate);
	// 拡大縮小行列と回転行列を掛け算
	result = Multiply(scaleMatrix, rotateXMatrix);
	// さらにY軸回転行列を掛け算
	result = Multiply(result, rotateYMatrix);
	// さらにZ軸回転行列を掛け算
	result = Multiply(result, rotateZMatrix);
	// 最後に平行移動行列を掛け算
	result = Multiply(result, translationMatrix);

	// 結果を返す
	return result;
}

/*---レンダリングパイプライン---*/
//透視投影行列
Matrix4x4 Function::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;

	float cot = 1.0f / std::tanf(fovY / 2.0f);

	//行列の作成
	result.m[0][0] = cot / aspectRatio;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cot;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0.0f;


	// 結果を返す
	return result;
};

//正射影行列
Matrix4x4 Function::MakeOrthographicmatrix(float left, float top, float  right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = -(right + left) / (right - left);
	result.m[3][1] = -(top + bottom) / (top - bottom);
	result.m[3][2] = -nearClip / (farClip - nearClip);
	result.m[3][3] = 1.0f;

	// 結果を返す
	return result;
};

//ビューポート変換行列
Matrix4x4 Function::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	// 結果を返す
	return result;
}

//クロス積
Vector3 Function::Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

//正射影ベクトル
Vector3 Function::project(const Vector3& v1, const Vector3& v2)
{
	float v2LenSq = Vector3Dot(v2, v2);

	if (v2LenSq == 0.0f) 
	{
		return { 0, 0, 0 };
	}; 

	float t = Vector3Dot(v1, v2) / v2LenSq;
	return Vector3Multiply(v2, t);
}

//最近接点
Vector3 Function::Closestpoint(const Vector3& point, const Segment& segment)
{
	// 点から線分の始点へのベクトル
	Vector3 toPoint = Vector3Subtract(point, segment.origin);

	// 線分の長さの2乗（diff の長さの2乗）
	float segLenSq = Vector3Dot(segment.diff, segment.diff);
	if (segLenSq == 0.0f)
	{
		// 長さゼロの線分（点）なら始点を返す
		return segment.origin;
	}

	// t = (toPoint ・ diff) / (diff ・ diff)
	float t = Vector3Dot(toPoint, segment.diff) / segLenSq;

	// t を 0 ～ 1 にクランプ
	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	// 最近接点 = origin + diff * t
	return Vector3Add(segment.origin, Vector3Multiply(segment.diff, t));
}

Matrix4x4 Function::MakeRotateAxisAgle(const Vector3& axis, float angle)
{
	Vector3 n = axis;
	Normalize(n);  // 軸を正規化

	float x = n.x;
	float y = n.y;
	float z = n.z;

	float c = std::cos(angle);
	float s = std::sin(angle);
	float oneMinusC = 1.0f - c;

	Matrix4x4 result{};

	result.m[0][0] = c + x * x * oneMinusC;
	result.m[0][1] = x * y * oneMinusC + z * s;
	result.m[0][2] = x * z * oneMinusC - y * s;
	result.m[0][3] = 0.0f;

	result.m[1][0] = y * x * oneMinusC - z * s;
	result.m[1][1] = c + y * y * oneMinusC;
	result.m[1][2] = y * z * oneMinusC + x * s;
	result.m[1][3] = 0.0f;

	result.m[2][0] = z * x * oneMinusC + y * s;
	result.m[2][1] = z * y * oneMinusC - x * s;
	result.m[2][2] = c + z * z * oneMinusC;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 Function::DirectionToDirection(const Vector3& from, const Vector3& to)
{
	// 正規化
	Vector3 f = Normalize(from);
	Vector3 t = Normalize(to);

	// 内積（cosθ）
	float dot = Vector3Dot(f, t);

	// 同じ方向（回転不要）
	if (dot > 0.9999f)
	{
		return MakeIdentity();
	}

	// 真逆方向（180度回転）
	if (dot < -0.9999f)
	{
		// from と直交する適当な軸を探す
		Vector3 axis = Cross(f, Vector3{ 1.0f, 0.0f, 0.0f });
		if (Length(axis) < 0.0001f)
		{
			axis = Cross(f, Vector3{ 0.0f, 1.0f, 0.0f });
		}
		axis = Normalize(axis);

		return MakeRotateAxisAgle(axis, std::numbers::pi_v<float>);
	}

	// 通常ケース
	Vector3 axis = Cross(f, t);
	float angle = std::acos(dot);

	axis = Normalize(axis);
	return MakeRotateAxisAgle(axis, angle);
}

Quaternion Function::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;

	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;

	return result;
}

Quaternion Function::IdentityQuaternion()
{
	return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

Quaternion Function::Conjugate(const Quaternion& quaternion)
{
	return Quaternion{
	-quaternion.x,
	-quaternion.y,
	-quaternion.z,
	 quaternion.w
	};
}

float Function::Norm(const Quaternion& quaternion)
{
	return std::sqrt(
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z +
		quaternion.w * quaternion.w
	);
}

Quaternion Function::Normalize(const Quaternion& quaternion)
{
	float length = Norm(quaternion);
	assert(length != 0.0f);

	Quaternion result;
	result.x = quaternion.x / length;
	result.y = quaternion.y / length;
	result.z = quaternion.z / length;
	result.w = quaternion.w / length;

	return result;
}

Quaternion Function::Inverse(const Quaternion& quaternion)
{
	float lengthSq =
		quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z +
		quaternion.w * quaternion.w;

	assert(lengthSq != 0.0f);

	Quaternion conjugate = Conjugate(quaternion);

	Quaternion result;
	result.x = conjugate.x / lengthSq;
	result.y = conjugate.y / lengthSq;
	result.z = conjugate.z / lengthSq;
	result.w = conjugate.w / lengthSq;

	return result;
}

Quaternion Function::MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	// 軸の長さ
	float length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	assert(length != 0.0f);

	// 正規化した軸
	Vector3 n;
	n.x = axis.x / length;
	n.y = axis.y / length;
	n.z = axis.z / length;

	float halfAngle = angle * 0.5f;
	float sinHalf = std::sin(halfAngle);
	float cosHalf = std::cos(halfAngle);

	Quaternion result;
	result.x = n.x * sinHalf;
	result.y = n.y * sinHalf;
	result.z = n.z * sinHalf;
	result.w = cosHalf;

	return result;
}

Vector3 Function::RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	// ベクトルをクォータニオン化
	Quaternion vq;
	vq.x = vector.x;
	vq.y = vector.y;
	vq.z = vector.z;
	vq.w = 0.0f;

	// q * v * q^-1
	Quaternion qInv = Inverse(quaternion);
	Quaternion temp = Multiply(quaternion, vq);
	Quaternion result = Multiply(temp, qInv);

	return Vector3{ result.x, result.y, result.z };
}

Matrix4x4 Function::MakeRotateMatrix(const Quaternion& quaternion)
{
	Quaternion q = Normalize(quaternion);

	float xx = q.x * q.x;
	float yy = q.y * q.y;
	float zz = q.z * q.z;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yz = q.y * q.z;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;

	Matrix4x4 mat{};

	mat.m[0][0] = 1.0f - 2.0f * (yy + zz);
	mat.m[0][1] = 2.0f * (xy + wz);
	mat.m[0][2] = 2.0f * (xz - wy);
	mat.m[0][3] = 0.0f;

	mat.m[1][0] = 2.0f * (xy - wz);
	mat.m[1][1] = 1.0f - 2.0f * (xx + zz);
	mat.m[1][2] = 2.0f * (yz + wx);
	mat.m[1][3] = 0.0f;

	mat.m[2][0] = 2.0f * (xz + wy);
	mat.m[2][1] = 2.0f * (yz - wx);
	mat.m[2][2] = 1.0f - 2.0f * (xx + yy);
	mat.m[2][3] = 0.0f;

	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 1.0f;

	return mat;
}

Quaternion Function::Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	// 念のため正規化
	Quaternion q0n = Normalize(q0);
	Quaternion q1n = Normalize(q1);

	// 内積（cosθ）
	float dot =
		q0n.x * q1n.x +
		q0n.y * q1n.y +
		q0n.z * q1n.z +
		q0n.w * q1n.w;

	// 反対向きなら最短経路を取る
	if (dot < 0.0f)
	{
		dot = -dot;
		q1n.x = -q1n.x;
		q1n.y = -q1n.y;
		q1n.z = -q1n.z;
		q1n.w = -q1n.w;
	}

	// 角度がほぼ 0 のときは Lerp
	const float kThreshold = 0.9995f;
	if (dot > kThreshold)
	{
		Quaternion result;
		result.x = q0n.x + t * (q1n.x - q0n.x);
		result.y = q0n.y + t * (q1n.y - q0n.y);
		result.z = q0n.z + t * (q1n.z - q0n.z);
		result.w = q0n.w + t * (q1n.w - q0n.w);
		return Normalize(result);
	}

	// θ = acos(dot)
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);

	float w0 = std::sin((1.0f - t) * theta) / sinTheta;
	float w1 = std::sin(t * theta) / sinTheta;

	Quaternion result;
	result.x = q0n.x * w0 + q1n.x * w1;
	result.y = q0n.y * w0 + q1n.y * w1;
	result.z = q0n.z * w0 + q1n.z * w1;
	result.w = q0n.w * w0 + q1n.w * w1;

	return result;
}


/*--- 3次元の描画 ---*/
//ベクトル
void Function::vectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kWindowWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kWindowWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kWindowWidth * 3, y, "%s", label);
}

//行列
void Function::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	for (int row = 0; row < 4; ++row)
	{
		// 行列の要素を表示
		for (int column = 0; column < 4; ++column)
		{
			// 行のラベルを表示
			if (row == 0)
			{
				Novice::ScreenPrintf(x, y, "%s", label);
			}

			Novice::ScreenPrintf(x + column * kWindowWidth, y + 20 + row * kWindowHeight,
				"%6.03F", matrix.m[row][column]);
		}


	}
}

// 四元数表示関数（x, y, z, w を横並びで表示）
void Function::QuaternionScreenPrintf(int x, int y, const Quaternion& q, const char* label)
{
	Novice::ScreenPrintf(x, y, "%6.02f", q.x);
	Novice::ScreenPrintf(x + kWindowWidth, y, "%6.02f", q.y);
	Novice::ScreenPrintf(x + kWindowWidth * 2, y, "%6.02f", q.z);
	Novice::ScreenPrintf(x + kWindowWidth * 3, y, "%6.02f", q.w);
	Novice::ScreenPrintf(x + kWindowWidth * 4, y, "%s", label);
}


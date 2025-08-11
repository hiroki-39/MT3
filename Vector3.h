#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	 // 加算
	Vector3 operator+(const Vector3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }

	// 減算
	Vector3 operator-(const Vector3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }

	// スカラー倍（右）
	Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

	// スカラー除算
	Vector3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

	// 符号反転
	Vector3 operator-() const { return {-x, -y, -z}; }

	// 合成代入 +=
	Vector3& operator+=(const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	// 合成代入 -=
	Vector3& operator-=(const Vector3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	// 合成代入 *=（スカラー）
	Vector3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// 合成代入 /=（スカラー）
	Vector3& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
};

// スカラー × Vector3 のための左側定義
inline Vector3 operator*(float scalar, const Vector3& v) { return v * scalar; }
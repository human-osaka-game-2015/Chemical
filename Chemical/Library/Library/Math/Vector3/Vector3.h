/**
 * @file	Vector3.h
 * @brief	3次元ベクタ構造体定義
 * @author	morimoto
 */
#ifndef LIB_VECTOR3_H
#define LIB_VECTOR3_H


namespace Lib
{
	/**
	 * 3次元ベクタ構造体
	 */
	struct VECTOR3
	{
	public:
		// Constructor コンストラクタ.
		VECTOR3();
		VECTOR3(const float* _pf);
		VECTOR3(float _x, float _y, float _z);

		// Cast キャスト.
		operator float* ();
		operator const float* () const;

		// Assignment operators 代入演算子.
		VECTOR3& operator += (const VECTOR3& _v);
		VECTOR3& operator -= (const VECTOR3& _v);
		VECTOR3& operator *= (float _f);
		VECTOR3& operator /= (float _f);

		// Unary operators 単項演算子.
		VECTOR3 operator + () const;
		VECTOR3 operator - () const;

		// Binary Operator 二項演算子.
		VECTOR3 operator + (const VECTOR3& _v) const;
		VECTOR3 operator - (const VECTOR3& _v) const;
		VECTOR3 operator * (float _f) const;
		VECTOR3 operator / (float _f) const;

		// Comparison Operator 比較演算子.
		bool operator == (const VECTOR3& _v) const;
		bool operator != (const VECTOR3& _v) const;


		float x, y, z;	//!< 要素.

	};
}


#endif // !LIB_VECTOR3_H

/**
 * @file	Vector4.h
 * @brief	4次元ベクタ構造体定義
 * @author	morimoto
 */
#ifndef LIB_VECTOR4_H
#define LIB_VECTOR4_H


namespace Lib
{
	/**
	 * 4次元ベクタ構造体
	 */
	struct VECTOR4
	{
	public:
		// Constructor コンストラクタ.
		VECTOR4();
		VECTOR4(const float* _pf);
		VECTOR4(float _x, float _y, float _z, float _w);

		// Cast キャスト.
		operator float* ();
		operator const float* () const;

		// Assignment operators 代入演算子.
		VECTOR4& operator += (const VECTOR4& _v);
		VECTOR4& operator -= (const VECTOR4& _v);
		VECTOR4& operator *= (float _f);
		VECTOR4& operator /= (float _f);

		// Unary operators 単項演算子.
		VECTOR4 operator + () const;
		VECTOR4 operator - () const;

		// Binary Operator 二項演算子.
		VECTOR4 operator + (const VECTOR4& _v) const;
		VECTOR4 operator - (const VECTOR4& _v) const;
		VECTOR4 operator * (float _f) const;
		VECTOR4 operator / (float _f) const;

		// Comparison Operator 比較演算子.
		bool operator == (const VECTOR4& _v) const;
		bool operator != (const VECTOR4& _v) const;


		float x, y, z, w;	//!< 要素.

	};
}


#endif // !LIB_VECTOR4_H

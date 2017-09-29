/**
 * @file	Vector2.h
 * @brief	2次元ベクタ構造体定義
 * @author	morimoto
 */
#ifndef LIB_VECTOR2_H
#define LIB_VECTOR2_H


namespace Lib
{
	/**
	 * 2次元ベクタ構造体
	 */
	struct VECTOR2
	{
	public:
		// Constructor コンストラクタ.
		VECTOR2();
		VECTOR2(const float* _pf);
		VECTOR2(float _x, float _y);

		// Cast キャスト.
		operator float* ();
		operator const float* () const;

		// Assignment operators 代入演算子.
		VECTOR2& operator += (const VECTOR2& _v);
		VECTOR2& operator -= (const VECTOR2& _v);
		VECTOR2& operator *= (float _f);
		VECTOR2& operator /= (float _f);

		// Unary operators 単項演算子.
		VECTOR2 operator + () const;
		VECTOR2 operator - () const;

		// Binary Operator 二項演算子.
		VECTOR2 operator + (const VECTOR2& _v) const;
		VECTOR2 operator - (const VECTOR2& _v) const;
		VECTOR2 operator * (float _f) const;
		VECTOR2 operator / (float _f) const;

		// Comparison Operator 比較演算子.
		bool operator == (const VECTOR2& _v) const;
		bool operator != (const VECTOR2& _v) const;


		float x, y;	//!< 要素.

	};
}


#endif // !LIB_VECTOR2_H

/**
 * @file	Matrix.h
 * @brief	行列構造体定義
 * @author	morimoto
 */
#ifndef LIB_MATRIX_H
#define LIB_MATRIX_H


namespace Lib
{
	/**
	 * 行列構造体
	 */
	struct MATRIX
	{
		// Constructor コンストラクタ.
		MATRIX();
		MATRIX(const float* _pf);
		MATRIX(const MATRIX& _m);
		MATRIX(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

		// Cast キャスト.
		operator float*();
		operator const float*() const;

		// Assignment operators 代入演算子.
		MATRIX& operator *= (const MATRIX& _m);
		MATRIX& operator += (const MATRIX& _m);
		MATRIX& operator -= (const MATRIX& _m);
		MATRIX& operator *= (float _f);
		MATRIX& operator /= (float _f);

		// Binary Operator 二項演算子.
		MATRIX operator * (const MATRIX& _m) const;
		MATRIX operator + (const MATRIX& _m) const;
		MATRIX operator - (const MATRIX& _m) const;
		MATRIX operator * (float _f) const;
		MATRIX operator / (float _f) const;

		// Comparison Operator 比較演算子.
		bool operator == (const MATRIX& _m) const;
		bool operator != (const MATRIX& _m) const;

		// 要素.
		union
		{
			struct
			{
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};
}


#endif // !LIB_MATRIX_H

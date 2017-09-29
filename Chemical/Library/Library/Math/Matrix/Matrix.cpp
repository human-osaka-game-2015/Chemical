/**
 * @file	Matrix.cpp
 * @brief	行列構造体実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Matrix.h"

#include <Windows.h>


namespace Lib
{
	//----------------------------------------------------------------------
	// MATRIX
	//----------------------------------------------------------------------
	MATRIX::MATRIX()
	{
		_11 = 0; _12 = 0; _13 = 0; _14 = 0;
		_21 = 0; _22 = 0; _23 = 0; _24 = 0;
		_31 = 0; _32 = 0; _33 = 0; _34 = 0;
		_41 = 0; _42 = 0; _43 = 0; _44 = 0;
	}

	MATRIX::MATRIX(const float* _pf)
	{
		memcpy(&_11, _pf, sizeof(MATRIX));
	}

	MATRIX::MATRIX(const MATRIX& _m)
	{
		*this = _m;
	}

	MATRIX::MATRIX(
		float _f11, float _f12, float _f13, float _f14,
		float _f21, float _f22, float _f23, float _f24,
		float _f31, float _f32, float _f33, float _f34,
		float _f41, float _f42, float _f43, float _f44)
	{
		_11 = _f11; _12 = _f12; _13 = _f13; _14 = _f14;
		_21 = _f21; _22 = _f22; _23 = _f23; _24 = _f24;
		_31 = _f31; _32 = _f32; _33 = _f33; _34 = _f34;
		_41 = _f41; _42 = _f42; _43 = _f43; _44 = _f44;
	}


	//----------------------------------------------------------------------
	// Cast
	//----------------------------------------------------------------------
	MATRIX::operator float*()
	{
		return static_cast<float*>(&_11);
	}

	MATRIX::operator const float*() const
	{
		return static_cast<const float*>(&_11);
	}


	//----------------------------------------------------------------------
	// Assignment operators
	//----------------------------------------------------------------------
	MATRIX& MATRIX::operator *= (const MATRIX& _m)
	{
		MATRIX Mat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Mat.m[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					Mat.m[i][j] += m[i][k] * _m.m[k][j];
				}
			}
		}

		memcpy(&_11, &Mat._11, sizeof(MATRIX));

		return *this;
	}

	MATRIX& MATRIX::operator += (const MATRIX& _m)
	{
		_11 += _m._11; _12 += _m._12; _13 += _m._13; _14 += _m._14;
		_21 += _m._21; _22 += _m._22; _23 += _m._23; _24 += _m._24;
		_31 += _m._31; _32 += _m._32; _33 += _m._33; _34 += _m._34;
		_41 += _m._41; _42 += _m._42; _43 += _m._43; _44 += _m._44;
		return *this;
	}

	MATRIX& MATRIX::operator -= (const MATRIX& _m)
	{
		_11 -= _m._11; _12 -= _m._12; _13 -= _m._13; _14 -= _m._14;
		_21 -= _m._21; _22 -= _m._22; _23 -= _m._23; _24 -= _m._24;
		_31 -= _m._31; _32 -= _m._32; _33 -= _m._33; _34 -= _m._34;
		_41 -= _m._41; _42 -= _m._42; _43 -= _m._43; _44 -= _m._44;
		return *this;
	}

	MATRIX& MATRIX::operator *= (float _f)
	{
		_11 *= _f; _12 *= _f; _13 *= _f; _14 *= _f;
		_21 *= _f; _22 *= _f; _23 *= _f; _24 *= _f;
		_31 *= _f; _32 *= _f; _33 *= _f; _34 *= _f;
		_41 *= _f; _42 *= _f; _43 *= _f; _44 *= _f;
		return *this;
	}

	MATRIX& MATRIX::operator /= (float _f)
	{
		float fInv = 1.0f / _f;
		_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
		_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
		return *this;
	}


	//----------------------------------------------------------------------
	// Binary Operator
	//----------------------------------------------------------------------
	MATRIX MATRIX::operator * (const MATRIX& _m) const
	{
		MATRIX Mat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Mat.m[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					Mat.m[i][j] += m[i][k] * _m.m[k][j];
				}
			}
		}
		return Mat;
	}

	MATRIX MATRIX::operator + (const MATRIX& _m) const
	{
		return MATRIX(
			_11 + _m._11, _12 + _m._12, _13 + _m._13, _14 + _m._14,
			_21 + _m._21, _22 + _m._22, _23 + _m._23, _24 + _m._24,
			_31 + _m._31, _32 + _m._32, _33 + _m._33, _34 + _m._34,
			_41 + _m._41, _42 + _m._42, _43 + _m._43, _44 + _m._44);
	}

	MATRIX MATRIX::operator - (const MATRIX& _m) const
	{
		return MATRIX(
			_11 - _m._11, _12 - _m._12, _13 - _m._13, _14 - _m._14,
			_21 - _m._21, _22 - _m._22, _23 - _m._23, _24 - _m._24,
			_31 - _m._31, _32 - _m._32, _33 - _m._33, _34 - _m._34,
			_41 - _m._41, _42 - _m._42, _43 - _m._43, _44 - _m._44);
	}

	MATRIX MATRIX::operator * (float _f) const
	{
		return MATRIX(
			_11 * _f, _12 * _f, _13 * _f, _14 * _f,
			_21 * _f, _22 * _f, _23 * _f, _24 * _f,
			_31 * _f, _32 * _f, _33 * _f, _34 * _f,
			_41 * _f, _42 * _f, _43 * _f, _44 * _f);
	}

	MATRIX MATRIX::operator / (float _f) const
	{
		float fInv = 1.0f / _f;
		return MATRIX(
			_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
			_41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
	}


	//----------------------------------------------------------------------
	// Comparison Operator
	//----------------------------------------------------------------------
	bool MATRIX::operator == (const MATRIX& _m) const
	{
		return 0 == memcmp(this, &_m, sizeof(MATRIX));
	}

	bool MATRIX::operator != (const MATRIX& _m) const
	{
		return 0 != memcmp(this, &_m, sizeof(MATRIX));
	}
}

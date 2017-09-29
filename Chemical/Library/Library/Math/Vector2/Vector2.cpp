/**
 * @file	Vector2.cpp
 * @brief	2次元ベクタ構造体実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Vector2.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// VECTOR2
	//----------------------------------------------------------------------
	VECTOR2::VECTOR2()
	{
		x = 0;
		y = 0;
	}

	VECTOR2::VECTOR2(const float* _pf)
	{
		x = _pf[0];
		y = _pf[1];
	}

	VECTOR2::VECTOR2(float _x, float _y) :
		x(_x),
		y(_x)
	{
	}


	//----------------------------------------------------------------------
	// Cast
	//----------------------------------------------------------------------
	VECTOR2::operator float* ()
	{
		return reinterpret_cast<float*>(&x);
	}

	VECTOR2::operator const float* () const
	{
		return reinterpret_cast<const float*>(&x);
	}


	//----------------------------------------------------------------------
	// Assignment operators
	//----------------------------------------------------------------------
	VECTOR2& VECTOR2::operator += (const VECTOR2& _v)
	{
		x += _v.x;
		y += _v.y;
		return *this;
	}

	VECTOR2& VECTOR2::operator -= (const VECTOR2& _v)
	{
		x -= _v.x;
		y -= _v.y;
		return *this;
	}

	VECTOR2& VECTOR2::operator *= (float _f)
	{
		x *= _f;
		y *= _f;
		return *this;
	}

	VECTOR2& VECTOR2::operator /= (float _f)
	{
		float fInv = 1.0f / _f;
		x *= fInv;
		y *= fInv;
		return *this;
	}


	//----------------------------------------------------------------------
	// Unary operators
	//----------------------------------------------------------------------
	VECTOR2 VECTOR2::operator + () const
	{
		return *this;
	}

	VECTOR2 VECTOR2::operator - () const
	{
		return VECTOR2(-x, -y);
	}


	//----------------------------------------------------------------------
	// Binary Operator
	//----------------------------------------------------------------------
	VECTOR2	VECTOR2::operator + (const VECTOR2& _v) const
	{
		return VECTOR2(x + _v.x, y + _v.y);
	}

	VECTOR2 VECTOR2::operator - (const VECTOR2& _v) const
	{
		return VECTOR2(x - _v.x, y - _v.y);
	}

	VECTOR2 VECTOR2::operator * (float _f) const
	{
		return VECTOR2(x * _f, y * _f);
	}

	VECTOR2	VECTOR2::operator / (float _f) const
	{
		float fInv = 1.0f / _f;
		return VECTOR2(x * fInv, y * fInv);
	}

	VECTOR2 operator * (float _f, const VECTOR2& _v)
	{
		return VECTOR2(_f * _v.x, _f * _v.y);
	}


	//----------------------------------------------------------------------
	// Comparison Operator
	//----------------------------------------------------------------------
	bool VECTOR2::operator == (const VECTOR2& _v) const
	{
		return
			x == _v.x &&
			y == _v.y;
	}

	bool VECTOR2::operator != (const VECTOR2& _v) const
	{
		return
			x != _v.x ||
			y != _v.y;
	}
}

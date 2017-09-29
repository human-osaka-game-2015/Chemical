/**
 * @file	Vector4.cpp
 * @brief	4次元ベクタ構造体実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Vector4.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// VECTOR4
	//----------------------------------------------------------------------
	VECTOR4::VECTOR4() :
		x(0),
		y(0),
		z(0),
		w(0)
	{
	}

	VECTOR4::VECTOR4(const float* _pf)
	{
		x = _pf[0];
		y = _pf[1];
		z = _pf[2];
		w = _pf[3];
	}

	VECTOR4::VECTOR4(float _x, float _y, float _z, float _w) : 
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{
	}


	//----------------------------------------------------------------------
	// Cast
	//----------------------------------------------------------------------
	VECTOR4::operator float*()
	{
		return reinterpret_cast<float*>(&x);
	}

	VECTOR4::operator const float*() const
	{
		return reinterpret_cast<const float*>(&x);
	}


	//----------------------------------------------------------------------
	// Assignment operators
	//----------------------------------------------------------------------
	VECTOR4& VECTOR4::operator += (const VECTOR4& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		w += _v.w;
		return *this;
	}

	VECTOR4& VECTOR4::operator -= (const VECTOR4& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		w -= _v.w;
		return *this;
	}

	VECTOR4& VECTOR4::operator *= (float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		w *= _f;
		return *this;
	}

	VECTOR4& VECTOR4::operator /= (float _f)
	{
		float fInv = 1.0f / _f;
		x *= fInv;
		y *= fInv;
		z *= fInv;
		w *= fInv;
		return *this;
	}


	//----------------------------------------------------------------------
	// Unary operators
	//----------------------------------------------------------------------
	VECTOR4 VECTOR4::operator + () const
	{
		return *this;
	}

	VECTOR4 VECTOR4::operator - () const
	{
		return VECTOR4(-x, -y, -z, -w);
	}


	//----------------------------------------------------------------------
	// Binary Operator
	//----------------------------------------------------------------------
	VECTOR4 VECTOR4::operator + (const VECTOR4& _v) const
	{
		return VECTOR4(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
	}

	VECTOR4	VECTOR4::operator - (const VECTOR4& _v) const
	{
		return VECTOR4(x - _v.x, y - _v.y, z - _v.z, w - _v.w);
	}

	VECTOR4	VECTOR4::operator * (float _f) const
	{
		return VECTOR4(x * _f, y * _f, z * _f, w * _f);
	}

	VECTOR4	VECTOR4::operator / (float _f) const
	{
		float fInv = 1.0f / _f;
		return VECTOR4(x * fInv, y * fInv, z * fInv, w * fInv);
	}

	VECTOR4	operator * (float _f, const VECTOR4& _v)
	{
		return VECTOR4(_f * _v.x, _f * _v.y, _f * _v.z, _f * _v.w);
	}


	//----------------------------------------------------------------------
	// Comparison Operator
	//----------------------------------------------------------------------
	bool VECTOR4::operator == (const VECTOR4& _v) const
	{
		return
			x == _v.x &&
			y == _v.y &&
			z == _v.z &&
			w == _v.w;
	}

	bool VECTOR4::operator != (const VECTOR4& _v) const
	{
		return
			x != _v.x ||
			y != _v.y ||
			z != _v.z ||
			w != _v.w;
	}
}

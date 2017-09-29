/**
 * @file	Vector3.cpp
 * @brief	3次元ベクタ構造体実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Vector3.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// VECTOR3
	//----------------------------------------------------------------------
	VECTOR3::VECTOR3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	VECTOR3::VECTOR3(const float* _pf)
	{
		x = _pf[0];
		y = _pf[1];
		z = _pf[2];
	}

	VECTOR3::VECTOR3(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{
	}


	//----------------------------------------------------------------------
	// Cast
	//----------------------------------------------------------------------
	VECTOR3::operator float* ()
	{
		return reinterpret_cast<float*>(&x);
	}

	VECTOR3::operator const float* () const
	{
		return reinterpret_cast<const float*>(&x);
	}


	//----------------------------------------------------------------------
	// Assignment operators
	//----------------------------------------------------------------------
	VECTOR3& VECTOR3::operator += (const VECTOR3& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		return *this;
	}

	VECTOR3& VECTOR3::operator -= (const VECTOR3& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		return *this;
	}

	VECTOR3& VECTOR3::operator *= (float _f)
	{
		x *= _f;
		y *= _f;
		z *= _f;
		return *this;
	}

	VECTOR3& VECTOR3::operator /= (float _f)
	{
		float fInv = 1.0f / _f;
		x *= fInv;
		y *= fInv;
		z *= fInv;
		return *this;
	}


	//----------------------------------------------------------------------
	// Unary operators
	//----------------------------------------------------------------------
	VECTOR3 VECTOR3::operator + () const
	{
		return *this;
	}

	VECTOR3 VECTOR3::operator - () const
	{
		return VECTOR3(-x, -y, -z);
	}


	//----------------------------------------------------------------------
	// Binary Operator
	//----------------------------------------------------------------------
	VECTOR3 VECTOR3::operator + (const VECTOR3& _v) const
	{
		return VECTOR3(x + _v.x, y + _v.y, z + _v.z);
	}

	VECTOR3 VECTOR3::operator - (const VECTOR3& _v) const
	{
		return VECTOR3(x - _v.x, y - _v.y, z - _v.z);
	}

	VECTOR3 VECTOR3::operator * (float _f) const
	{
		return VECTOR3(x * _f, y * _f, z * _f);
	}

	VECTOR3 VECTOR3::operator / (float _f) const
	{
		float fInv = 1.0f / _f;
		return VECTOR3(x * fInv, y * fInv, z * fInv);
	}

	VECTOR3 operator * (float f, const VECTOR3& _v)
	{
		return VECTOR3(f * _v.x, f * _v.y, f * _v.z);
	}


	//----------------------------------------------------------------------
	// Comparison Operator
	//----------------------------------------------------------------------
	bool VECTOR3::operator == (const VECTOR3& _v) const
	{
		return
			x == _v.x &&
			y == _v.y &&
			z == _v.z;
	}

	bool VECTOR3::operator != (const VECTOR3& _v) const
	{
		return
			x != _v.x ||
			y != _v.y ||
			z != _v.z;
	}

}

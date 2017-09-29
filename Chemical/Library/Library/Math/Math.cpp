/**
 * @file	Math.cpp
 * @brief	算術系関数実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Math.h"

#include <Windows.h>
#include <math.h>


namespace Lib
{
	//----------------------------------------------------------------------
	// Vector Functions
	//----------------------------------------------------------------------
	float Vector3Dot(const VECTOR3* _pIn1, const VECTOR3* _pIn2)
	{
		return 
			((_pIn1->x) * (_pIn2->x) + 
			 (_pIn1->y) * (_pIn2->y) + 
			 (_pIn1->z) * (_pIn2->z));
	}

	VECTOR3 Vector3Cross(const VECTOR3* _pIn1, const VECTOR3* _pIn2, VECTOR3* _pOut)
	{
		_pOut->x = (_pIn1->y * _pIn2->z - _pIn1->z * _pIn2->y);
		_pOut->y = (_pIn1->z * _pIn2->x - _pIn1->x * _pIn2->z);
		_pOut->z = (_pIn1->x * _pIn2->y - _pIn1->y * _pIn2->x);

		return *_pOut;
	}

	VECTOR3 Vector3Normalize(VECTOR3* _pOut)
	{
		float Len = 1.f / sqrt(_pOut->x * _pOut->x + _pOut->y * _pOut->y + _pOut->z * _pOut->z);
		_pOut->x *= Len;
		_pOut->y *= Len;
		_pOut->z *= Len;

		return *_pOut;
	}

	float VectorLength(const VECTOR2* _pIn)
	{
		return 
			sqrt(
			pow(_pIn->x, 2) + 
			pow(_pIn->y, 2));
	}

	float VectorLength(const VECTOR3* _pIn)
	{
		return
			sqrt(
			pow(_pIn->x, 2) +
			pow(_pIn->y, 2) + 
			pow(_pIn->z, 2));
	}

	float VectorDistance(const VECTOR2* _pIn1, const VECTOR2* _pIn2)
	{
		return 
			sqrt(
			pow(_pIn2->x - _pIn1->x, 2) +
			pow(_pIn2->y - _pIn1->y, 2));
	}

	float VectorDistance(const VECTOR3* _pIn1, const VECTOR3* _pIn2)
	{
		return 
			sqrt(
			pow(_pIn2->x - _pIn1->x, 2) + 
			pow(_pIn2->y - _pIn1->y, 2) + 
			pow(_pIn2->z - _pIn1->z, 2));
	}

	float VectorRadian(const VECTOR2* _pIn1, const VECTOR2* _pIn2)
	{
		return atan2(
			_pIn2->y - _pIn1->y,
			_pIn2->x - _pIn1->x);
	}

	float VectorDegree(const VECTOR2* _pIn1, const VECTOR2* _pIn2)
	{
		return ToDegree(
			atan2(
			_pIn2->y - _pIn1->y,
			_pIn2->x - _pIn1->x));
	}


	//----------------------------------------------------------------------
	// Matrix Functions
	//----------------------------------------------------------------------
	MATRIX MatrixIdentity(MATRIX* _pMat)
	{
		_pMat->_11 = 1.f; _pMat->_12 = 0.f; _pMat->_13 = 0.f; _pMat->_14 = 0.f;
		_pMat->_21 = 0.f; _pMat->_22 = 1.f; _pMat->_23 = 0.f; _pMat->_24 = 0.f;
		_pMat->_31 = 0.f; _pMat->_32 = 0.f; _pMat->_33 = 1.f; _pMat->_34 = 0.f;
		_pMat->_41 = 0.f; _pMat->_42 = 0.f; _pMat->_43 = 0.f; _pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixTranspose(MATRIX* _pMat)
	{
		MATRIX Mat = *_pMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_pMat->m[i][j] = Mat.m[j][i];
			}
		}

		return *_pMat;
	}

	MATRIX MatrixTranslation(MATRIX* _pMat, float _x, float _y, float _z)
	{
		_pMat->_11 = 1.f; _pMat->_12 = 0.f; _pMat->_13 = 0.f; _pMat->_14 = 0.f;
		_pMat->_21 = 0.f; _pMat->_22 = 1.f; _pMat->_23 = 0.f; _pMat->_24 = 0.f;
		_pMat->_31 = 0.f; _pMat->_32 = 0.f; _pMat->_33 = 1.f; _pMat->_34 = 0.f;
		_pMat->_41 =  _x; _pMat->_42 =  _y; _pMat->_43 =  _z; _pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixScaling(MATRIX* _pMat, float _x, float _y, float _z)
	{
		_pMat->_11 =  _x; _pMat->_12 = 0.f; _pMat->_13 = 0.f; _pMat->_14 = 0.f;
		_pMat->_21 = 0.f; _pMat->_22 =  _y; _pMat->_23 = 0.f; _pMat->_24 = 0.f;
		_pMat->_31 = 0.f; _pMat->_32 = 0.f; _pMat->_33 =  _z; _pMat->_34 = 0.f;
		_pMat->_41 = 0.f; _pMat->_42 = 0.f; _pMat->_43 = 0.f; _pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixRotationX(MATRIX* _pMat, float _angle)
	{
		_pMat->_11 = 1.f;
		_pMat->_12 = 0.f; 
		_pMat->_13 = 0.f;
		_pMat->_14 = 0.f;
		_pMat->_21 = 0.f; 
		_pMat->_22 = cos(ToRadian(_angle)); 
		_pMat->_23 = sin(ToRadian(_angle)); 
		_pMat->_24 = 0.f;
		_pMat->_31 = 0.f; 
		_pMat->_32 = -sin(ToRadian(_angle)); 
		_pMat->_33 = cos(ToRadian(_angle)); 
		_pMat->_34 = 0.f;
		_pMat->_41 = 0.f; 
		_pMat->_42 = 0.f;
		_pMat->_43 = 0.f; 
		_pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixRotationY(MATRIX* _pMat, float _angle)
	{
		_pMat->_11 = cos(ToRadian(_angle));
		_pMat->_12 = 0.f;
		_pMat->_13 = -sin(ToRadian(_angle));
		_pMat->_14 = 0.f;
		_pMat->_21 = 0.f; 
		_pMat->_22 = 1.f; 
		_pMat->_23 = 0.f; 
		_pMat->_24 = 0.f;
		_pMat->_31 = sin(ToRadian(_angle));
		_pMat->_32 = 0.f; 
		_pMat->_33 = cos(ToRadian(_angle));
		_pMat->_34 = 0.f;
		_pMat->_41 = 0.f; 
		_pMat->_42 = 0.f; 
		_pMat->_43 = 0.f; 
		_pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixRotationZ(MATRIX* _pMat, float _angle)
	{
		_pMat->_11 = cos(ToRadian(_angle));
		_pMat->_12 = sin(ToRadian(_angle));
		_pMat->_13 = 0.f;
		_pMat->_14 = 0.f;
		_pMat->_21 = -sin(ToRadian(_angle));
		_pMat->_22 = cos(ToRadian(_angle));
		_pMat->_23 = 0.f;
		_pMat->_24 = 0.f;
		_pMat->_31 = 0.f;
		_pMat->_32 = 0.f;
		_pMat->_33 = 1.f;
		_pMat->_34 = 0.f;
		_pMat->_41 = 0.f;
		_pMat->_42 = 0.f;
		_pMat->_43 = 0.f;
		_pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixLookAtLH(MATRIX* _pMat, VECTOR3* _eyePos, VECTOR3* _at, VECTOR3* _up)
	{
		VECTOR3 Zaxis = Vector3Normalize(&VECTOR3(*_at - *_eyePos));
		VECTOR3 Xaxis = Vector3Normalize(&Vector3Cross(_up, &Zaxis, &Xaxis));
		VECTOR3 Yaxis = Vector3Cross(&Zaxis, &Xaxis, &Yaxis);

		_pMat->_11 = Xaxis.x;
		_pMat->_12 = Yaxis.x;
		_pMat->_13 = Zaxis.x;
		_pMat->_14 = 0.f;
		_pMat->_21 = Xaxis.y;
		_pMat->_22 = Yaxis.y;
		_pMat->_23 = Zaxis.y;
		_pMat->_24 = 0.f;
		_pMat->_31 = Xaxis.z;
		_pMat->_32 = Yaxis.z;
		_pMat->_33 = Zaxis.z;
		_pMat->_34 = 0.f;
		_pMat->_41 = -Vector3Dot(&Xaxis, _eyePos);
		_pMat->_42 = -Vector3Dot(&Yaxis, _eyePos);
		_pMat->_43 = -Vector3Dot(&Zaxis, _eyePos);
		_pMat->_44 = 1.f;

		return *_pMat;
	}

	MATRIX MatrixPerspectiveFovLH(MATRIX* _pMat, float _fovY, float _aspect, float _zNear, float _zFar)
	{
		float h = 1 / tan(_fovY / 2);
		float w = h / _aspect;

		_pMat->_11 = w;
		_pMat->_12 = 0;
		_pMat->_13 = 0;
		_pMat->_14 = 0;
		_pMat->_21 = 0;
		_pMat->_22 = h;
		_pMat->_23 = 0;
		_pMat->_24 = 0;
		_pMat->_31 = 0;
		_pMat->_32 = 0;
		_pMat->_33 = _zFar / (_zFar - _zNear);
		_pMat->_34 = 1.f;
		_pMat->_41 = 0;
		_pMat->_42 = 0;
		_pMat->_43 = -_zNear * _zFar / (_zFar - _zNear);
		_pMat->_44 = 0;

		return *_pMat;
	}
}

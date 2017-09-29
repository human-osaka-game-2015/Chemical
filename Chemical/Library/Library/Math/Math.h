/**
 * @file	Math.cpp
 * @brief	算術系関数定義
 * @author	morimoto
 */
#ifndef LIB_MATH_H
#define LIB_MATH_H


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>
#include "Vector2\Vector2.h"
#include "Vector3\Vector3.h"
#include "Vector4\Vector4.h"
#include "Matrix\Matrix.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Global Variables
	//----------------------------------------------------------------------
	const float g_LibPI = 3.14159265358979323846f;


	//----------------------------------------------------------------------
	// Utility Functions
	//----------------------------------------------------------------------
	inline float ToRadian(float _degree)
	{
		return _degree * (g_LibPI / 180.0f);
	}

	inline float ToDegree(float _radian)
	{
		return _radian * (180.0f / g_LibPI);
	}


	//----------------------------------------------------------------------
	// Vector Functions
	//----------------------------------------------------------------------
	float Vector3Dot(const VECTOR3* _pIn1, const VECTOR3* _pIn2);
	VECTOR3 Vector3Cross(const VECTOR3* _pIn1, const VECTOR3* _pIn2, VECTOR3* _pOut);
	VECTOR3 Vector3Normalize(VECTOR3* _pOut);
	float VectorLength(const VECTOR2* _pIn);
	float VectorLength(const VECTOR3* _pIn);
	float VectorDistance(const VECTOR2* _pIn1, const VECTOR2* _pIn2);
	float VectorDistance(const VECTOR3* _pIn1, const VECTOR3* _pIn2);
	float VectorRadian(const VECTOR2* _pIn1, const VECTOR2* _pIn2);
	float VectorDegree(const VECTOR2* _pIn1, const VECTOR2* _pIn2);


	//----------------------------------------------------------------------
	// Matrix Functions
	//----------------------------------------------------------------------
	MATRIX MatrixIdentity(MATRIX* _pMat);
	MATRIX MatrixTranspose(MATRIX* _pMat);
	MATRIX MatrixTranslation(MATRIX* _pMat, float _x, float _y, float _z);
	MATRIX MatrixScaling(MATRIX* _pMat, float _x, float _y, float _z);
	MATRIX MatrixRotationX(MATRIX* _pMat, float _angle);
	MATRIX MatrixRotationY(MATRIX* _pMat, float _angle);
	MATRIX MatrixRotationZ(MATRIX* _pMat, float _angle);

	/**
	 * 左手系ビュー行列作成
	 * @param[out] _pMat 行列の出力先
	 * @param[in] _eyePos 視点の座標
	 * @param[in] _at 注視座標
	 * @param[in] _up 上方向
	 * @return 作成した行列
	 */
	MATRIX MatrixLookAtLH(
		MATRIX* _pMat,
		VECTOR3* _eyePos,
		VECTOR3* _at, 
		VECTOR3* _up = &VECTOR3(0.f, 1.f, 0.f));

	/**
	 * 左手座標系パースペクティブ射影行列作成
	 * @param[out] _pMat 行列の出力先
	 * @param[in] _fovY Y方向の視野角
	 * @param[in] _aspect アスペクト比
	 * @param[in] _zNear 最近点
	 * @param[in] _zFar 最遠点
	 * @return 作成した行列
	 */
	MATRIX MatrixPerspectiveFovLH(
		MATRIX* _pMat,
		float _fovY, 
		float _aspect,
		float _zNear, 
		float _zFar);

}


#endif // !LIB_MATH_H

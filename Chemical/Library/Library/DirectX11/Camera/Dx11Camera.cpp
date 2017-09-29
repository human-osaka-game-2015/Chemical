/**
 * @file   Dx11Camera.cpp
 * @brief  Cameraクラスの実装
 * @author morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11Camera.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------------------------------------
		Camera::Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ) :
			m_WindowWidth(_windowWidth),
			m_WindowHeight(_windowHeight),
			m_NearZ(_nearZ),
			m_FarZ(_farZ)
		{
			m_Aspect = m_WindowWidth / m_WindowHeight;
		}

		Camera::~Camera()
		{
		}


		//----------------------------------------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------------------------------------
		void Camera::TransformView(
			const D3DXVECTOR3* _pEyePos,
			const D3DXVECTOR3* _pLookPos,
			const D3DXVECTOR3* _pUpVec,
			float _viewAngle)
		{
			// ビュー座標変換行列の作成.
			D3DXMatrixLookAtLH(&m_MatView, _pEyePos, _pLookPos, _pUpVec);

			// プロジェクション座標変換行列の作成.
			D3DXMatrixPerspectiveFovLH(&m_MatProj, static_cast<float>(D3DXToRadian(_viewAngle)), m_Aspect, m_NearZ, m_FarZ);
		}
	}
}

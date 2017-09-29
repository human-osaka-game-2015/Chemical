/**
 * @file   Dx11Camera.h
 * @brief  Cameraクラスの定義
 * @author morimoto
 */
#ifndef LIB_DX11_CAMERA_H
#define LIB_DX11_CAMERA_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>


namespace Lib
{
	namespace Dx11
	{
		/**
		 * カメラ情報の管理クラス
		 */
		class Camera
		{
		public:
			/**
			 * コンストラクタ
			 * @param[in] _windowWidth ウィンドウの幅
			 * @param[in] _windowHeight ウィンドウの高さ
			 * @param[in] _nearZ カメラの最近点
			 * @param[in] _farZ カメラの最遠点
			 */
			Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ);

			/**
			 * デストラクタ
			 */
			~Camera();

			/**
			 * 座標変換用行列作成
			 * @param[in] _pEyePos カメラの座標
			 * @param[in] _pLookPos カメラの注視座標
			 * @param[in] _pUpVec カメラの上方向ベクトル
			 * @param[in] _viewAngle カメラの視野角
			 */
			void TransformView(
				const D3DXVECTOR3* _pEyePos,
				const D3DXVECTOR3* _pLookPos,
				const D3DXVECTOR3* _pUpVec,
				float _viewAngle);

			/**
			 * ビュー座標変換用行列の取得
			 * @return ビュー座標変換用行列
			 */
			inline const D3DXMATRIX& GetViewMatrix() const
			{
				return m_MatView;
			}

			/**
			 * プロジェクション座標変換用行列の取得
			 * @return プロジェクション座標変換用行列
			 */
			inline const D3DXMATRIX& GetProjectionMatrix() const
			{
				return m_MatProj;
			}

		private:
			D3DXMATRIX	m_MatView;		//!< カメラビュー行列.
			D3DXMATRIX	m_MatProj;		//!< カメラプロジェクション行列.
			float		m_WindowWidth;	//!< ウィンドウの幅.
			float		m_WindowHeight;	//!< ウィンドウの高さ.
			float		m_NearZ;		//!< カメラの最近点.
			float		m_FarZ;			//!< カメラの最遠点.
			float		m_Aspect;		//!< ウィンドウのアスペクト.

		};
	}
}


#endif // !LIB_DX11_CAMERA_H

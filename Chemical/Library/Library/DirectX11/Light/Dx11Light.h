/**
 * @file   Dx11Light.h
 * @brief  Lightクラスの定義
 * @author morimoto
 */
#ifndef LIB_DX11_LIGHT_H
#define LIB_DX11_LiGHT_H

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
		 * ライト情報の管理クラス
		 */
		class Light
		{
		public:
			/**
			 * コンストラクタ
			 */
			Light();

			/**
			 * デストラクタ
			 */
			~Light();

			/**
			 * ライト座標の設定
			 * @param[in] _pPos 設定する座標
			 */
			inline void SetPos(const D3DXVECTOR3* _pPos)
			{
				m_Pos = *_pPos;
			}

			/**
			 * ライトの向きの設定
			 * @param[in] 設定する向き
			 */
			inline void SetDirectionPos(const D3DXVECTOR3* _pDirectionPos)
			{
				m_DirectionPos = *_pDirectionPos;
			}

			/**
			 * ライト座標の取得
			 * @return ライト座標
			 */
			inline D3DXVECTOR3 GetPos() const
			{
				return m_Pos;
			}

			/**
			 * ライトの向きの取得
			 * @return ライトの向き
			 */
			inline D3DXVECTOR3 GetDirectionPos() const
			{
				return m_DirectionPos;
			}

		private:
			D3DXVECTOR3 m_Pos;			//!< ライトの座標.
			D3DXVECTOR3 m_DirectionPos;	//!< ライトが向いている座標.

		};
	}
}


#endif // !LIB_DX11_LIGHT_H

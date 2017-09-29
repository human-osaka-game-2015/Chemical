/**
 * @file	Dx11ITexture.h
 * @brief	テクスチャインターフェース定義
 * @author	morimoto
 */
#ifndef LIB_DX11_ITEXTURE_H
#define LIB_DX11_ITEXTURE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\..\..\Define\Define.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * テクスチャインターフェース
		 */
		interface ITexture
		{
		public:
			/**
			 * コンストラクタ
			 */
			ITexture();

			/**
			 * デストラクタ
			 */
			virtual ~ITexture() = 0;

			/**
			 * テクスチャの設定
			 * @param[in] _pTexture テクスチャリソースビュー
			 */
			virtual void Set(ID3D11ShaderResourceView* _pTexture) = 0;

			/**
			 * テクスチャの取得
			 * @return テクスチャ
			 */
			virtual ID3D11ShaderResourceView* Get() const = 0;


		private:
			DISALLOW_COPY_AND_ASSIGN(ITexture);

		};
	}
}



#endif // !LIB_DX11_ITEXTURE_H

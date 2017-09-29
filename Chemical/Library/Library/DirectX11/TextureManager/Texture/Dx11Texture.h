/**
 * @file	Dx11Texture.h
 * @brief	テクスチャクラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_TEXTURE_H
#define LIB_DX11_TEXTURE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\..\..\Define\Define.h"
#include "..\..\TextureManager\ITexture\Dx11ITexture.h"


namespace Lib
{
	namespace Dx11
	{
		class GraphicsDevice;

		/**
		 * テクスチャクラス
		 */
		class Texture : public ITexture
		{
		public:
			/**
			 * コンストラクタ
			 */
			Texture();

			/**
			 * コンストラクタ
			 * @param[in] _pGraphicsDevice グラフィックデバイス
			 * @param[in] _pTexturePath テクスチャのパス
			 */
			Texture(GraphicsDevice* _pGraphicsDevice, LPCTSTR _pTexturePath);

			/**
			 * デストラクタ
			 */
			virtual ~Texture();

			/**
			 * テクスチャの設定
			 * @param[in] _pTexture テクスチャリソースビュー
			 */
			virtual void Set(ID3D11ShaderResourceView* _pTexture);

			/**
			 * テクスチャの取得
			 * @return テクスチャ
			 */
			virtual ID3D11ShaderResourceView* Get() const;


		private:
			/**
			 * テクスチャの読み込み
			 * @param[in] _pTexturePath テクスチャのパス
			 */
			void Load(LPCTSTR _pTexturePath);

			/**
			 * テクスチャの解放
			 */
			void Release();


			GraphicsDevice*				m_pGraphicsDevice;	//!< グラフィックデバイス.
			ID3D11ShaderResourceView*	m_pTexture;			//!< テクスチャのシェーダーリソースビュー.


			DISALLOW_COPY_AND_ASSIGN(Texture);

		};
	}
}


#endif // !LIB_DX11_TEXTURE_H

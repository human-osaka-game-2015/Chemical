/**
 * @file	Dx11TextureManager.h
 * @brief	テクスチャ管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_TEXTUREMANAGER_H
#define LIB_DX11_TEXTUREMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "..\..\SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx11
	{
		class GraphicsDevice;
		interface ITexture;

		/**
		 * テクスチャ管理クラス
		 */
		class TextureManager : public SingletonBase<TextureManager>
		{
		public:
			friend SingletonBase<TextureManager>;

			static const int m_InvalidIndex;	//!< TextureManagerクラスがとるインデックスエラー値.

			/**
			 * 初期化処理
			 * @param[in] _pGraphicsDevice グラフィックデバイス
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize(GraphicsDevice* _pGraphicsDevice);

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * テクスチャの読み込み
			 * @param[in] _pTexturePath 読み込むテクスチャのパス
			 * @param[out] _pIndex 読み込んだテクスチャ格納先インデックス
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadTexture(LPCTSTR _pTexturePath, int* _pIndex);

			/**
			 * テクスチャの解放
			 * @param[in] _index 解放するテクスチャのインデックス
			 */
			void ReleaseTexture(int _index);

			/**
			 * テクスチャの取得
			 * @param[in] _index 取得するテクスチャのインデックス
			 * @return 格納先のテクスチャ
			 */
			ITexture* GetTexture(int _index) const;

			/**
			 * テクスチャを格納しているバッファを解放する
			 */
			void ClearBuffer();

		private:
			/**
			 * コンストラクタ
			 */
			TextureManager();

			/**
			 * デストラクタ
			 */
			virtual ~TextureManager();


			GraphicsDevice*			m_pGraphicsDevice;	//!< グラフィックデバイス.
			std::vector<ITexture*>	m_pTextures;		//!< テクスチャを格納するコンテナ.


			DISALLOW_COPY_AND_ASSIGN(TextureManager);

		};
	}
}


#endif // !LIB_DX11_TEXTUREMANAGER_H

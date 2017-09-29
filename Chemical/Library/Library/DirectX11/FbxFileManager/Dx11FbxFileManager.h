/**
 * @file   Dx11FbxFileManager.h
 * @brief  FbxFileManagerクラスの定義
 * @author morimoto
 */
#ifndef LIB_DX11_FBXFILEMANAGER_H
#define LIB_DX11_FBXFILEMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3D11.h>
#include <vector>

#include "FbxModel\Dx11FbxModel.h"
#include "SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx11
	{
		class GraphicsDevice;
		class FbxLoader;

		/**
		 *  Fbxファイルを管理するクラス
		 */
		class FbxFileManager : public SingletonBase<FbxFileManager>
		{
		public:
			friend SingletonBase<FbxFileManager>;

			static const int m_InvalidIndex; //!< FbxFileManagerクラスがとるインデックスのエラー値.

			/**
			 * 初期化処理
			 * @param[in] _pGraphicsDevice グラフィックデバイス
			 * @return 初期化に成功したらtrue
			 */
			bool Initialize(GraphicsDevice* _pGraphicsDevice);

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * Fbxモデルを読み込む
			 * @param[in] _pFileName 読み込むモデルのファイルパス
			 * @param[out] _pIndex 読み込んだモデルの格納先インデックス
			 * @return 読み込みに成功したらtrue
			 */
			bool LoadFbxModel(LPCTSTR _pFileName, int* _pIndex);

			/**
			 * Fbxモデルを取得する
			 * @param[in] _index 取得するモデルのインデックス
			 * @return Fbxのデータを格納したFbxModelクラス
			 */
			inline FbxModel* GetFbxModel(int _index) const
			{
				return m_pFbxModel[_index];
			}

			/**
			 * Fbxモデルを解放する
			 * @param[in] _index 解放するモデルのインデックス
			 */
			void ReleaseFbxModel(int _index);

			/**
			 * モデルを確保しているバッファをクリアする
			 *
			 * vectorを使用しているのでバッファ領域は解放されない。\n
			 * バッファ領域はFbxFileManagerが破棄されたときに解放される。
			 */
			inline void ClearBuffer()
			{
				m_pFbxModel.clear();
			}

		private:
			/**
			 * FbxFileManagerクラスのコンストラクタ
			 */
			FbxFileManager();

			/**
			 * FbxFileManagerクラスのデストラクタ
			 */
			virtual ~FbxFileManager();


			GraphicsDevice*				m_pGraphicsDevice;	//!< グラフィックデバイス.
			FbxLoader*					m_pFbxLoader;		//!< fbx読み込みオブジェクト.
			std::vector<FbxModel*>		m_pFbxModel;		//!< fbxモデルを管理するコンテナ.


			DISALLOW_COPY_AND_ASSIGN(FbxFileManager);

		};
	}
}


#endif // !LIB_DX11_FBXFILEMANAGER_H

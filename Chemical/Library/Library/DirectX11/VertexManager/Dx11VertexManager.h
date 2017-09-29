/**
 * @file	Dx11VertexManager.h
 * @brief	頂点管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_VERTEXMANAGER_H
#define LIB_DX11_VERTEXMANAGER_H

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
		interface IVertex;

		/**
		 * 頂点管理クラス
		 */
		class VertexManager : public SingletonBase<VertexManager>
		{
		public:
			friend SingletonBase<VertexManager>;

			/**
			 * コンストラクタ
			 */
			VertexManager();

			/**
			 * デストラクタ
			 */
			virtual ~VertexManager();

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

		private:
			GraphicsDevice*			m_pGraphicDevice;	//!< グラフィックデバイス.
			std::vector<IVertex*>	m_pVertexs;			//!< 頂点オブジェクトを格納するコンテナ.

		};
	}
}


#endif // !LIB_DX11_VERTEXMANAGER_H

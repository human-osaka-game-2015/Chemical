/**
 * @file	Dx11ShaderManager.h
 * @brief	シェーダーの管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_SHADERMANAGER_H
#define LIB_DX11_SHADERMANAGER_H


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

#include "..\..\SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx11
	{
		class GraphicsDevice;

		/**
		 * シェーダーの管理クラス
		 */
		class ShaderManager : public SingletonBase<ShaderManager>
		{
		public:
			friend SingletonBase<ShaderManager>;

			static const int m_InvalidIndex;	//!< ShaderManagerクラスがとるインデックスのエラー値.


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
			 * 頂点シェーダーを読み込む(バージョンはvs_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName 頂点シェーダーの関数名
			 * @param[out] _pIndex 頂点シェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadVertexShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * ピクセルシェーダーを読み込む(バージョンはps_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName ピクセルシェーダーの関数名
			 * @param[out] _pIndex ピクセルシェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadPixelShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * ジオメトリシェーダーを読み込む(バージョンはgs_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName ジオメトリシェーダーの関数名
			 * @param[out] _pIndex ジオメトリシェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadGeometryShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * ハルシェーダーを読み込む(バージョンはhs_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName ハルシェーダーの関数名
			 * @param[out] _pIndex ハルシェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadHullShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * ドメインシェーダーを読み込む(バージョンはds_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName ドメインシェーダーの関数名
			 * @param[out] _pIndex ドメインシェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadDomainShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * コンピュートシェーダーを読み込む(バージョンはcs_5_0)
			 * @param[in] _pFilePath 読み込むエフェクトファイルのパス
			 * @param[in] _pFuncName コンピュートシェーダーの関数名
			 * @param[out] _pIndex コンピュートシェーダーとコンパイルデータの格納先インデックスが入る
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadComputeShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex);

			/**
			 * 頂点シェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放する頂点シェーダーのインデックス
			 */
			void ReleaseVertexShader(int _index);

			/**
			 * 頂点シェーダーとそのコンパイルデータを全て解放
			 */
			void ReleaseVertexShader();

			/**
			 * ピクセルシェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放するピクセルシェーダーのインデックス
			 */
			void ReleasePixelShader(int _index);

			/**
			 * ピクセルシェーダーとそのコンパイルデータを全て解放
			 */
			void ReleasePixelShader();

			/**
			 * ジオメトリシェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放するジオメトリシェーダーのインデックス
			 */
			void ReleaseGeometryShader(int _index);

			/**
			 * ジオメトリシェーダーとそのコンパイルデータを全て解放
			 */
			void ReleaseGeometryShader();

			/**
			 * ハルシェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放するハルシェーダーのインデックス
			 */
			void ReleaseHullShader(int _index);

			/**
			 * ハルシェーダーとそのコンパイルデータを全て解放
			 */
			void ReleaseHullShader();

			/**
			 * ドメインシェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放するドメインシェーダーのインデックス
			 */
			void ReleaseDomainShader(int _index);

			/**
			 * ドメインシェーダーとそのコンパイルデータを全て解放
			 */
			void ReleaseDomainShader();

			/**
			 * コンピュートシェーダーとそのコンパイルデータを解放
			 * @param[in] _index 解放するコンピュートシェーダーのインデックス
			 */
			void ReleaseComputeShader(int _index);

			/**
			 * コンピュートシェーダーとそのコンパイルデータを全て解放
			 */
			void ReleaseComputeShader();

			/**
			 * 頂点シェーダーを取得
			 * @param[in] _index 取得したい頂点シェーダーのインデックス
			 * @return 頂点シェーダー
			 */
			inline ID3D11VertexShader* GetVertexShader(int _index) const
			{
				return m_pVertexShader[_index];
			}

			/**
			 * 頂点シェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return 頂点シェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledVertexShader(int _index) const
			{
				return m_pCompiledVertexShader[_index];
			}

			/**
			 * ピクセルシェーダーを取得
			 * @param[in] _index 取得したいピクセルシェーダーのインデックス
			 * @return ピクセルシェーダー
			 */
			inline ID3D11PixelShader* GetPixelShader(int _index) const
			{
				return m_pPixelShader[_index];
			}

			/**
			 * ピクセルシェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return ピクセルシェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledPixelShader(int _index) const
			{
				return m_pCompiledPixelShader[_index];
			}

			/**
			 * ジオメトリシェーダーを取得
			 * @param[in] _index 取得したいジオメトリシェーダーのインデックス
			 * @return ジオメトリシェーダー
			 */
			inline ID3D11GeometryShader* GetGeometryShader(int _index) const
			{
				return m_pGeometryShader[_index];
			}

			/**
			 * ジオメトリシェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return ジオメトリシェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledGeometryShader(int _index) const
			{
				return m_pCompiledGeometryShader[_index];
			}

			/**
			 * ハルシェーダーを取得
			 * @param[in] _index 取得したいハルシェーダーのインデックス
			 * @return ハルシェーダー
			 */
			inline ID3D11HullShader* GetHullShader(int _index) const
			{
				return m_pHullShader[_index];
			}

			/**
			 * ハルシェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return ハルシェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledHullShader(int _index) const
			{
				return m_pCompiledHullShader[_index];
			}

			/**
			 * ドメインシェーダーを取得
			 * @param[in] _index 取得したいドメインシェーダーのインデックス
			 * @return ドメインシェーダー
			 */
			inline ID3D11DomainShader* GetDomainShader(int _index) const
			{
				return m_pDomainShader[_index];
			}

			/**
			 * ドメインシェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return ドメインシェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledDomainShader(int _index) const
			{
				return m_pCompiledDomainShader[_index];
			}

			/**
			 * コンピュートシェーダーを取得
			 * @param[in] _index 取得したいコンピュートシェーダーのインデックス
			 * @return コンピュートシェーダー
			 */
			inline ID3D11ComputeShader* GetComputeShader(int _index) const
			{
				return m_pComputeShader[_index];
			}

			/**
			 * コンピュートシェーダーのコンパイルデータを取得
			 * @param[in] _index 取得したいコンパイルデータのインデックス
			 * @return コンピュートシェーダーのコンパイルデータ
			 */
			inline ID3DBlob* GetCompiledComputeShader(int _index) const
			{
				return m_pCompiledComputeShader[_index];
			}

			/**
			 * シェーダーのデータを確保しているバッファをクリア
			 */
			inline void ClearShaderBuffer()
			{
				m_pVertexShader.clear();
				m_pCompiledVertexShader.clear();

				m_pPixelShader.clear();
				m_pCompiledPixelShader.clear();

				m_pGeometryShader.clear();
				m_pCompiledGeometryShader.clear();

				m_pHullShader.clear();
				m_pCompiledHullShader.clear();

				m_pDomainShader.clear();
				m_pCompiledDomainShader.clear();

				m_pComputeShader.clear();
				m_pCompiledComputeShader.clear();
			}

		private:
			/**
			 * コンストラクタ
			 */
			ShaderManager();

			/**
			 * デストラクタ
			 */
			virtual ~ShaderManager();


			GraphicsDevice*						m_pGraphicsDevice;			//!< グラフィックデバイス.
			std::vector<ID3D11VertexShader*>	m_pVertexShader;			//!< 頂点シェーダーを格納するコンテナ.
			std::vector<ID3D11PixelShader*>		m_pPixelShader;				//!< ピクセルシェーダーを格納するコンテナ.
			std::vector<ID3D11GeometryShader*>	m_pGeometryShader;			//!< ジオメトリシェーダーを格納するコンテナ.
			std::vector<ID3D11HullShader*>		m_pHullShader;				//!< ハルシェーダーを格納するコンテナ.
			std::vector<ID3D11DomainShader*>	m_pDomainShader;			//!< ドメインシェーダーを格納するコンテナ.
			std::vector<ID3D11ComputeShader*>	m_pComputeShader;			//!< コンピュートシェーダーを格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledVertexShader;	//!< 頂点シェーダのコンパイル情報を格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledPixelShader;		//!< ピクセルシェーダのコンパイル情報を格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledGeometryShader;	//!< ジオメトリシェーダーのコンパイル情報を格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledHullShader;		//!< ハルシェーダーのコンパイル情報を格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledDomainShader;	//!< ドメインシェーダーのコンパイル情報を格納するコンテナ.
			std::vector<ID3DBlob*>				m_pCompiledComputeShader;	//!< コンピュートシェーダーのコンパイル情報を格納するコンテナ.


			DISALLOW_COPY_AND_ASSIGN(ShaderManager);

		};
	}
}



#endif // !LIB_DX11_SHADERMANAGER_H

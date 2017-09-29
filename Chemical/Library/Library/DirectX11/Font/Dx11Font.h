/**
 * @file	Dx11Font.h
 * @brief	フォントクラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_FONT_H
#define LIB_DX11_FONT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\GraphicsDevice\Dx11GraphicsDevice.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * フォントクラス
		 */
		class Font
		{
		public:
			/**
			 * コンストラクタ
			 */
			Font();

			/**
			 * デストラクタ
			 */
			~Font();

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
			 * 頂点バッファの生成
			 * @param[in] _pSize フォントのサイズ情報
			 * @param[in] _pColor フォントのカラー値
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexBuffer(
				const D3DXVECTOR2* _pSize, 
				const D3DXCOLOR* _pColor = &D3DXCOLOR(0xffffffff));

			/**
			 * 頂点バッファの解放
			 */
			void ReleaseVertexBuffer();

			/**
			 * 2Dポリゴンの描画
			 * @param[in] _pDrawPos フォントの描画位置
			 * @param[in] _pStr 描画する文字列
			 */
			void Draw(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr);

		private:
			enum
			{
				VERTEX_NUM = 4 //!< 頂点数.
			};

			/**
			 * フォント表示のための頂点構造体
			 */
			struct FONT_VERTEX
			{
				D3DXVECTOR3 Pos;	//!< 頂点座標.
				D3DXVECTOR2	Texel;	//!< テクスチャ座標.
				D3DXCOLOR	Color;	//!< 頂点カラー.
			};

			/**
			 * シェーダーに渡す定数バッファ構造体
			 */
			struct CONSTANT_BUFFER
			{
				D3DXMATRIX	MatWorld;	//!< ワールド変換行列.
				D3DXVECTOR4 TexelOffset;//!< テクスチャ座標のオフセット.
				D3DXVECTOR4 PosOffset;	//!< 頂点座標のオフセット.
				D3DXVECTOR4 WindowSize;	//!< ウィンドウの縦横サイズ.
			};

			/**
			 * 頂点シェーダーの生成
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexShader();

			/**
			 * 頂点入力レイアウトの生成
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexLayout();

			/**
			 * ピクセルシェーダーの生成
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreatePixelShader();

			/**
			 * 描画ステートの生成
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateState();

			/**
			 * リソースビューの生成
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateResourceView();

			/**
			 * 頂点シェーダーの解放
			 */
			void ReleaseVertexShader();

			/**
			 * 頂点入力レイアウトの解放
			 */
			void ReleaseVertexLayout();

			/**
			 * ピクセルシェーダーの解放
			 */
			void ReleasePixelShader();

			/**
			 * 描画ステートの解放
			 */
			void ReleaseState();

			/**
			 * リソースビューの解放
			 */
			void ReleaseResourceView();


			static const float			m_FontTu;				//!< テクスチャ上でのフォントサイズ.
			static const int			m_SpaceAsciiCode;		//!< スペースのアスキーコード.
			GraphicsDevice*				m_pGraphicsDevice;		//!< グラフィックデバイス.
			ID3D11VertexShader*			m_pVertexShader;		//!< 頂点シェーダー.
			ID3DBlob*					m_pVertexCompiledShader;//!< 頂点シェーダーのコンパイル情報.
			ID3D11InputLayout*			m_pVertexLayout;		//!< 頂点入力レイアウト.
			ID3D11PixelShader*			m_pPixelShader;			//!< ピクセルシェーダー.
			ID3DBlob*					m_pPixelCompiledShader;	//!< ピクセルシェーダーのコンパイル情報.
			ID3D11BlendState*			m_pBlendState;			//!< ブレンドステート.
			ID3D11SamplerState*			m_pSamplerState;		//!< サンプラステート.
			ID3D11Buffer*				m_pVertexBuffer;		//!< 頂点バッファ.
			ID3D11Buffer*				m_pConstantBuffer;		//!< 定数バッファ.
			ID3D11ShaderResourceView*	m_pShaderResource;		//!< テクスチャのシェーダーリソースビュー.
			D3DXVECTOR2					m_FontSize;				//!< フォントのサイズ.
			float						m_WindowWidth;			//!< ウィンドウの幅.
			float						m_WindowHeight;			//!< ウィンドウの高さ.

		};
	}
}


#endif // !LIB_DX11_FONT_H

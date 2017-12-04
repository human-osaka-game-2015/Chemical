/**
 * @file	MultipleVertex2DUV.h
 * @brief	複数の矩形描画クラス定義
 * @author	morimoto
 */
#ifndef LIB_MULTIPLEVERTEX2DUV_H
#define LIB_MULTIPLEVERTEX2DUV_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\GraphicsDevice\Dx11GraphicsDevice.h"
#include "..\TextureManager\ITexture\Dx11ITexture.h"


namespace Lib
{
	namespace Dx11
	{
		/*** 複数の矩形描画クラス */
		class MultipleVertex2DUV
		{
		public:
			/*** コンストラクタ */
			MultipleVertex2DUV();

			/*** デストラクタ */
			~MultipleVertex2DUV();

			/**
			 * 初期化処理
			 * @param[in] _pGraphicsDevice グラフィックデバイス
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize(GraphicsDevice* _pGraphicsDevice);

			/*** 終了処理 */
			void Finalize();

			/**
			 * 頂点バッファの生成
			 * @param[in] _pSize 描画する2Dポリゴンの矩形サイズ
			 * @param[in] _pMinUV テクスチャのMin座標
			 * @param[in] _pMaxUV テクスチャのMax座標
			 * @param[in] _pColor 頂点色
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexBuffer(
				const D3DXVECTOR2* _pSize,
				const D3DXVECTOR2* _pMinUV = &D3DXVECTOR2(0.f, 0.f),
				const D3DXVECTOR2* _pMaxUV = &D3DXVECTOR2(1.0f, 1.0f),
				const D3DXCOLOR* _pColor = &D3DXCOLOR(0xffffffff));

			/**
			 * インスタンスバッファの生成
			 * @param[in] _pMat インスタンスごとの変換行列
			 * @param[in] _pUV インスタンスごとのUV
			 * @param[in] _instanceNum インスタンスの数
			 * @return 生成に成功したらtrue 失敗したらfalse
			 */
			bool CreateInstanceBufferUV(D3DXMATRIX* _pMat, D3DXVECTOR2* _pUV, int _instanceNum);

			/*** 頂点バッファの解放 */
			void ReleaseVertexBuffer();

			/*** インスタンスバッファの解放 */
			void ReleaseInstanceBufferUV();

			/**
			 * 定数バッファにデータを書き込む
			 * @return 書き込みに成功したらtrue 失敗したらfalse
			 */
			bool WriteConstantBuffer(D3DXVECTOR2 _pos = D3DXVECTOR2(0, 0));

			/**
			 * 頂点バッファにデータを書き込む
			 * @return 書き込みに成功したらtrue 失敗したらfalse
			 */
			bool WriteVertexBuffer();

			/**
			 * 矩形情報から頂点座標を設定する
			 * @param[in] _pSize 描画する2Dポリゴンの矩形サイズ
			 */
			void SetVertex(const D3DXVECTOR2* _pSize);

			/**
			 * テクスチャ座標を設定する
			 * @param[in] _pMinUV UVの最小値
			 * @param[in] _pMaxUV UVの最大値
			 */
			void SetUV(const D3DXVECTOR2* _pMinUV, const D3DXVECTOR2* _pMaxUV);

			/**
			 * カラー情報を設定する
			 * @param[in] _pColor 描画するポリゴンの色
			 */
			void SetColor(const D3DXCOLOR* _pColor);

			/**
			 * インスタンスバッファにデータを書き込む
			 * @param[in] _pDrawPos 描画位置
			 * @param[in] _pUV UV値
			 * @return 書き込みに成功したらtrue 失敗したらfalse
			 */
			bool WriteInstanceBuffer(const D3DXVECTOR2* _pDrawPos, const D3DXVECTOR2* _pUV);

			/*** デフォルトのシェーダーの準備 */
			void ShaderSetup();

			/*** テクスチャの準備 */
			void TextureSetup();

			/*** デフォルトの深度ステンシルステート準備*/
			void DepthStencilStateSetup();

			/*** デフォルトのブレンドステート準備*/
			void BlendStateSetup();

			/**
			 * 複数矩形のデフォルト描画 
			 * @param[in] _pDrawPos 描画位置
			 * @param[in] _pUV UV値
			 * @param[in] _instanceNum 描画インスタンス数
			 */
			void DefaultDraw(const D3DXVECTOR2* _pDrawPos, const D3DXVECTOR2* _pUV, int _instanceNum = 0);

			/**
			 * 複数矩形の描画(ポリゴンの描画処理のみ行う) 
			 * @param[in] _instanceNum 描画インスタンス数
			 */
			void Draw(int _instanceNum = 0);

			/**
			 * 描画するテクスチャの設定
			 * @param[in] _pTexture テクスチャオブジェクト
			 */
			void SetTexture(ITexture* _pTexture) { m_pTexture = _pTexture; }

		private:
			enum
			{
				VERTEX_NUM = 4 //!< 頂点数.
			};

			/*** 2D矩形描画用の頂点構造体 */
			struct VERTEX
			{
				D3DXVECTOR3		Pos;	//!< 頂点座標.
				D3DXVECTOR2		UV;		//!< テクスチャ座標.
				D3DXCOLOR		Color;	//!< 頂点カラー値.
			};

			/*** インスタンス別データ構造体 */
			struct INSTANCE_DATA_UV
			{
				D3DXMATRIX Mat;		//!< 変換行列.
				D3DXVECTOR4 UV;
			};

			/*** シェーダーで使用する定数バッファ */
			struct CONSTANT_BUFFER
			{
				D3DXVECTOR4 WindowSize;		//!< ウィンドウの縦横サイズ.
				D3DXVECTOR4 InstancePos;	//!< インスタンス全体に影響する座標値.
			};


			/**
			 * 頂点シェーダーの初期化
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexShader();

			/**
			 * 頂点入力レイアウトの初期化
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreateVertexLayout();

			/**
			 * ピクセルシェーダーの初期化
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreatePixelShader();

			/**
			 * 描画ステートの初期化
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreateState();

			/*** 頂点シェーダーの解放 */
			void ReleaseVertexShader();

			/*** 頂点入力レイアウトの解放 */
			void ReleaseVertexLayout();

			/*** ピクセルシェーダーの解放 */
			void ReleasePixelShader();

			/*** ステートの解放 */
			void ReleaseState();

			GraphicsDevice*				m_pGraphicsDevice;			//!< グラフィックデバイス.
			ID3D11VertexShader*			m_pVertexShader;			//!< 頂点シェーダー.
			ID3DBlob*					m_pVertexCompiledShader;	//!< 頂点シェーダーのコンパイル情報.
			ID3D11InputLayout*			m_pVertexLayout;			//!< 頂点入力レイアウト.
			ID3D11PixelShader*			m_pPixelShader;				//!< ピクセルシェーダー.
			ID3DBlob*					m_pPixelCompiledShader;		//!< ピクセルシェーダーのコンパイル情報.
			ID3D11BlendState*			m_pBlendState;				//!< ブレンドステート.
			ID3D11SamplerState*			m_pSamplerState;			//!< サンプラステート.
			ID3D11DepthStencilState*	m_pDepthStencilState;		//!< 深度ステンシルステート.
			ID3D11DepthStencilState*	m_pUserDepthStencilState;	//!< ユーザー指定の深度ステンシルステート.
			ID3D11Buffer*				m_pVertexBuffer;			//!< 頂点バッファ.
			ID3D11Buffer*				m_pConstantBuffer;			//!< 定数バッファ.
			ID3D11Buffer*				m_pInstanceBuffer;			//!< インスタンシングバッファ.
			ITexture*					m_pTexture;					//!< テクスチャインターフェース.
			VERTEX						m_pVertexData[VERTEX_NUM];	//!< 頂点情報構造体.
			INSTANCE_DATA_UV*			m_pInstanceDataUV;			//!< インスタンスデータ.
			float						m_WindowWidth;				//!< ウィンドウの幅.
			float						m_WindowHeight;				//!< ウィンドウの高さ.
			int							m_InstanceNum;				//!< インスタンスの数.

		};
	}
}


#endif // !LIB_MULTIPLEVERTEX2DUV_H

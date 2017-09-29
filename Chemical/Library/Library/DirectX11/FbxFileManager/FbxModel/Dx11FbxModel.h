/**
 * @file   Dx11FbxModel.h
 * @brief  FbxModelクラスの定義
 * @author morimoto
 */
#ifndef LIB_DX11_FBXMODEL_H
#define LIB_DX11_FBXMODEL_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * Fbxファイルのモデル情報を管理するクラス
		 */
		class FbxModel
		{
		public:
			/**
			 * Fbxの描画の際に利用する頂点構造体
			 */
			struct FBXMODEL_VERTEX
			{
				D3DXVECTOR3 Pos;	//!< 頂点座標.
				D3DXVECTOR3	Normal;	//!< 法線ベクトル.
				D3DXVECTOR2 Texel;	//!< テクスチャ座標.
			};

			/**
			 * Fbxファイルから取得する頂点情報構造体
			 */
			struct VERTEX_DATA
			{
				int				PolygonNum;			//!< ポリゴンの数.
				int				PolygonVertexNum;	//!< Meshの総頂点数.
				int*			pIndexAry;			//!< インデックスバッファ.
				int				ControlPositionNum;	//!< インデックスバッファが指す頂点の数.
				D3DXVECTOR3*	pVertex;			//!< インデックスが参照する頂点.
			};

			/**
			 * Fbxファイルから取得する法線情報構造体
			 */
			struct NORMAL_DATA
			{
				D3DXVECTOR3* pNormalVec; //!< 法線ベクトルの配列.
			};

			/**
			 * メッシュの描画に利用するマテリアル構造体
			 */
			struct MATERIAL
			{
				D3DXCOLOR	Diffuse;	//!< ディフューズ反射.
				D3DXCOLOR	Ambient;	//!< アンビエント反射.
				D3DXCOLOR	Specular;	//!< スペキュラ反射.
				D3DXCOLOR	Emissive;	//!< エミッシブ.
				float		Power;		//!< スペキュラ強度.
			};

			/**
			 * テクスチャUVのデータ構造体
			 */
			struct TEXTURE_UV_DATA
			{
				LPCTSTR			pUVSetName;	//!< UVセットの名前(テクスチャ座標とテクスチャを紐づける).
				D3DXVECTOR2*	pTextureUV;	//!< テクスチャ座標.
			};

			/**
			 * Fbxファイルから取得するテクスチャ構造体
			 */
			struct TEXTURE_DATA
			{
				TEXTURE_UV_DATA* pTextureUVData;	//!< テクスチャUVデータ.
				int TextureUVCount;					//!< テクスチャUVデータの数.
			};

			/**
			 * Fbxから取得するマテリアル構造体
			 */
			struct MATERIAL_DATA
			{
				MATERIAL					pMaterial;			//!< メッシュのマテリアル.
				int							TextureCount;		//!< マテリアルに紐づいているテクスチャの数.
				LPCTSTR*					pTextureName;		//!< マテリアルに紐づいているテクスチャの名前が格納された配列.
				LPCTSTR*					pTextureUVSetName;	//!< マテリアルに紐づいているテクスチャとUVを結びつける文字列が格納された配列.
				ID3D11ShaderResourceView**	pTextureView;		//!< マテリアルに紐づいているテクスチャのビューが格納された配列.
			};

			/**
			 * Fbxから取得するメッシュのデータ構造体
			 */
			struct MESH_DATA
			{
				VERTEX_DATA*	pVertexData;	//!< メッシュの頂点情報.
				NORMAL_DATA*	pNormalData;	//!< メッシュの法線情報.
				TEXTURE_DATA*	pTextureData;	//!< テクスチャの情報.
				MATERIAL_DATA*	pMaterialData;	//!< マテリアルの情報.
			};


			/**
			 * コンストラクタ
			 * @param[in] _pGraphicsDevice グラフィックデバイス
			 */
			FbxModel(GraphicsDevice* _pGraphicsDevice);

			/**
			 * デストラクタ
			 */
			~FbxModel();

			/**
			 * メッシュデータを追加する
			 * @param[in] _pMeshData 追加するメッシュデータ
			 */
			void AddMeshData(MESH_DATA* _pMeshData);

			/**
			 * メッシュデータをもとに初期化処理を行う
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize();

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * オブジェクト描画
			 * @param[in] _meshNum 描画するメッシュの番号
			 */
			void Draw(int _meshNum = 0);

			/**
			 * アニメーション描画
			 */
			void AnimationDraw();

			/**
			 * アニメーションフレームをセットする
			 * @param[in] _setFrame セットするフレーム
			 */
			void SetAnimationFrame(int _setFrame);

			/**
			 * アニメーションの最大フレームを取得する
			 * @return 最大フレーム
			 */
			int GetAnimationFrame();

			/**
			 * モデル内のメッシュ数を取得する
			 * @return モデル内のメッシュ数
			 */
			int GetMeshNum();


		private:
			/**
			 * マテリアルの定数バッファ
			 */
			struct MATERIAL_CONSTANT_BUFFER
			{
				D3DXVECTOR4 Diffuse;	//!< ディフューズ.
				D3DXVECTOR4 Ambient;	//!< アンビエント.
				D3DXVECTOR4 Specular;	//!< スペキュラ.
				D3DXVECTOR4 Emissive;	//!< エミッシブ.
			};

			/**
			 * インデックスバッファを初期化する
			 * @return 初期化に成功したらtrue 失敗したらfalsef
			 */
			bool CreateIndexBuffer();

			/**
			 * 頂点バッファを初期化する
			 * @return 初期化に成功したらtrue 失敗したらfalsef
			 */
			bool CreateVertexBuffer();

			/**
			 * サンプラステートを初期化する
			 * @return 初期化に成功したらtrue 失敗したらfalsef
			 */
			bool CreateSamplerState();

			/**
			 * 定数バッファを初期化する
			 * @return 初期化に成功したらtrue 失敗したらfalsef
			 */
			bool CreateConstantBuffer();

			/**
			 * インデックスバッファの解放
			 */
			void ReleaseIndexBuffer();

			/**
			 * 頂点バッファの解放
			 */
			void ReleaseVertexBuffer();

			/**
			 * サンプラステートの解放
			 */
			void ReleaseSamplerState();

			/**
			 * 定数バッファの解放
			 */
			void ReleaseConstantBuffer();

			/**
			 * 定数バッファへの書き込み関数
			 * @param[in] 定数バッファに書き込むデータを持つメッシュ
			 */
			void WriteConstantBuffer(int _meshNum = 0);


			GraphicsDevice*				m_pGraphicsDevice;			//!< グラフィックデバイス.
			std::vector<MESH_DATA>		m_MeshData;					//!< メッシュデータ.
			ID3D11Buffer**				m_ppIndexBuffer;			//!< インデックスバッファ.
			ID3D11Buffer**				m_ppVertexBuffer;			//!< 頂点バッファ.
			FBXMODEL_VERTEX**			m_ppVertexData;				//!< 頂点データ.
			ID3D11SamplerState*			m_pSamplerState;			//!< サンプラステート.
			ID3D11Buffer*				m_pMaterialConstantBuffer;	//!< マテリアルの定数バッファ.

		};
	}
}


#endif // !LIB_DX11_FBXMODEL_H

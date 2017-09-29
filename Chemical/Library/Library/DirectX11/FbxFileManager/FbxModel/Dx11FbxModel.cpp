/**
 * @file   Dx11FbxModel.cpp
 * @brief  FbxModelクラスの実装
 * @author morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11FbxModel.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		FbxModel::FbxModel(GraphicsDevice* _pGraphicsDevice) :
			m_pGraphicsDevice(_pGraphicsDevice),
			m_ppIndexBuffer(nullptr),
			m_ppVertexBuffer(nullptr),
			m_ppVertexData(nullptr),
			m_pSamplerState(nullptr),
			m_pMaterialConstantBuffer(nullptr)
		{
		}

		FbxModel::~FbxModel()
		{
		}


		//----------------------------------------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------------------------------------
		void FbxModel::AddMeshData(MESH_DATA* _pMeshData)
		{
			m_MeshData.push_back(*_pMeshData);
		}

		bool FbxModel::Initialize()
		{
			MyAssert(m_MeshData.size() == 0, "メッシュデータがありません");

			if (!CreateIndexBuffer())
			{
				OutputErrorLog("インデックスバッファの初期化に失敗しました");
				return false;
			}

			if (!CreateVertexBuffer())
			{
				OutputErrorLog("頂点バッファの初期化に失敗しました");

				ReleaseIndexBuffer();

				return false;
			}

			if (!CreateSamplerState())
			{
				OutputErrorLog("サンプラステートの初期化に失敗しました");

				ReleaseVertexBuffer();
				ReleaseIndexBuffer();

				return false;
			}

			if (!CreateConstantBuffer())
			{
				OutputErrorLog("定数バッファの初期化に失敗しました");

				ReleaseSamplerState();
				ReleaseVertexBuffer();
				ReleaseIndexBuffer();
			}

			WriteConstantBuffer();	///@todo 現状は複数メッシュの対応はしない.

			return true;
		}

		void FbxModel::Finalize()
		{
			ReleaseConstantBuffer();
			ReleaseSamplerState();
			ReleaseVertexBuffer();
			ReleaseIndexBuffer();

			for (unsigned int i = 0; i < m_MeshData.size(); i++)
			{
				// マテリアル関連の破棄.
				SafeDelete(m_MeshData[i].pMaterialData->pTextureName);
				SafeDelete(m_MeshData[i].pMaterialData->pTextureUVSetName);

				for (int n = 0; n < m_MeshData[i].pMaterialData->TextureCount; n++)
				{
					SafeRelease(m_MeshData[i].pMaterialData->pTextureView[n]);
				}
				SafeDelete(m_MeshData[i].pMaterialData->pTextureView);
				SafeDelete(m_MeshData[i].pMaterialData);

				// テクスチャ関連の破棄.
				for (int n = 0; n < m_MeshData[i].pTextureData->TextureUVCount; n++)
				{
					SafeDelete(m_MeshData[i].pTextureData->pTextureUVData[n].pTextureUV);
				}

				SafeDelete(m_MeshData[i].pTextureData->pTextureUVData);
				SafeDelete(m_MeshData[i].pTextureData);

				// 法線関連の破棄.
				SafeDelete(m_MeshData[i].pNormalData->pNormalVec);
				SafeDelete(m_MeshData[i].pNormalData);

				// 頂点関連の破棄.
				SafeDelete(m_MeshData[i].pVertexData->pVertex);
				SafeDelete(m_MeshData[i].pVertexData->pIndexAry);
				SafeDelete(m_MeshData[i].pVertexData);
			}
		}

		void FbxModel::Draw(int _meshNum)
		{
			UINT stride = sizeof(FBXMODEL_VERTEX);
			UINT offset = 0;

			m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_ppVertexBuffer[_meshNum], &stride, &offset);
			m_pGraphicsDevice->GetDeviceContext()->IASetIndexBuffer(m_ppIndexBuffer[_meshNum], DXGI_FORMAT_R32_UINT, 0);
			m_pGraphicsDevice->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			m_pGraphicsDevice->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);

			m_pGraphicsDevice->GetDeviceContext()->OMSetBlendState(nullptr, nullptr, 0xffffffff);

			m_pGraphicsDevice->GetDeviceContext()->VSSetConstantBuffers(3, 1, &m_pMaterialConstantBuffer);
			m_pGraphicsDevice->GetDeviceContext()->PSSetConstantBuffers(3, 1, &m_pMaterialConstantBuffer);

			for (int i = 0; i < m_MeshData[_meshNum].pMaterialData->TextureCount; i++)
			{
				m_pGraphicsDevice->GetDeviceContext()->PSSetShaderResources(i, 1, &m_MeshData[_meshNum].pMaterialData->pTextureView[i]);
			}

			m_pGraphicsDevice->GetDeviceContext()->DrawIndexed(m_MeshData[_meshNum].pVertexData->PolygonVertexNum, 0, 0);
		}

		void FbxModel::AnimationDraw()
		{
			/// @todo アニメーション情報の取得がまだなので未実装.
		}

		void FbxModel::SetAnimationFrame(int _setFrame)
		{
			/// @todo アニメーション情報の取得がまだなので未実装.
		}

		int FbxModel::GetAnimationFrame()
		{
			/// @todo アニメーション情報の取得がまだなので未実装(とりあえず0だけ返す).
			return 0;
		}


		//----------------------------------------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------------------------------------
		bool FbxModel::CreateIndexBuffer()
		{
			m_ppIndexBuffer = new ID3D11Buffer*[m_MeshData.size()];

			for (unsigned int MeshIndex = 0; MeshIndex < m_MeshData.size(); MeshIndex++)
			{
				int PolygonVertexNum = m_MeshData[MeshIndex].pVertexData->PolygonVertexNum;	// メッシュの総頂点数.

				// インデックスバッファの設定.
				D3D11_BUFFER_DESC BufferDesc;
				ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
				BufferDesc.ByteWidth = sizeof(int) * PolygonVertexNum;
				BufferDesc.Usage = D3D11_USAGE_DEFAULT;
				BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				BufferDesc.CPUAccessFlags = 0;
				BufferDesc.MiscFlags = 0;
				BufferDesc.StructureByteStride = 0;

				// インデックスバッファに格納するデータの設定.
				D3D11_SUBRESOURCE_DATA ResourceData;
				ZeroMemory(&ResourceData, sizeof(ResourceData));
				ResourceData.pSysMem = m_MeshData[MeshIndex].pVertexData->pIndexAry;
				ResourceData.SysMemPitch = 0;
				ResourceData.SysMemSlicePitch = 0;

				// インデックスバッファの生成.
				if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
					&BufferDesc,
					&ResourceData,
					&m_ppIndexBuffer[MeshIndex])))
				{
					OutputErrorLog("インデックスバッファの作成に失敗しました");

					for (unsigned int i = 0; i < MeshIndex; i++)
					{
						SafeRelease(m_ppIndexBuffer[i]);
					}
					SafeDeleteArray(m_ppIndexBuffer);

					return false;
				}
			}

			return true;
		}

		bool FbxModel::CreateVertexBuffer()
		{
			m_ppVertexBuffer = new ID3D11Buffer*[m_MeshData.size()];
			m_ppVertexData = new FBXMODEL_VERTEX*[m_MeshData.size()];

			for (unsigned int MeshIndex = 0; MeshIndex < m_MeshData.size(); MeshIndex++)
			{
				MESH_DATA MeshData = m_MeshData[MeshIndex]; // 現在のメッシュデータ.

				int ControlPositionNum = MeshData.pVertexData->ControlPositionNum;				// メッシュのインデックスバッファが指す総頂点数.
				D3DXVECTOR3* pVertex = MeshData.pVertexData->pVertex;							// メッシュが持つ頂点座標の配列.
				D3DXVECTOR3* pNormal = MeshData.pNormalData->pNormalVec;						// メッシュが持つ法線ベクトルの配列.
				///@todo 現状 複数テクスチャは考慮しない.
				D3DXVECTOR2* pUVVertex = MeshData.pTextureData->pTextureUVData[0].pTextureUV;	// メッシュが持つテクスチャ座標の配列.


				// メッシュに格納されているデータを設定.
				m_ppVertexData[MeshIndex] = new FBXMODEL_VERTEX[ControlPositionNum];
				for (int i = 0; i < ControlPositionNum; i++)
				{
					m_ppVertexData[MeshIndex][i].Pos = pVertex[i];
					m_ppVertexData[MeshIndex][i].Normal = pNormal[i];
					m_ppVertexData[MeshIndex][i].Texel = pUVVertex[i];
				}


				// 頂点バッファの設定.
				D3D11_BUFFER_DESC BufferDesc;
				ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
				BufferDesc.ByteWidth = sizeof(FBXMODEL_VERTEX) * ControlPositionNum;
				BufferDesc.Usage = D3D11_USAGE_DEFAULT;
				BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				BufferDesc.CPUAccessFlags = 0;
				BufferDesc.MiscFlags = 0;

				// 頂点バッファに格納するデータの設定.
				D3D11_SUBRESOURCE_DATA ResourceData;
				ZeroMemory(&ResourceData, sizeof(ResourceData));
				ResourceData.pSysMem = m_ppVertexData[MeshIndex];
				ResourceData.SysMemPitch = 0;
				ResourceData.SysMemSlicePitch = 0;

				// 頂点バッファの生成.
				if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
					&BufferDesc,
					&ResourceData,
					&m_ppVertexBuffer[MeshIndex])))
				{
					OutputErrorLog("頂点バッファの作成に失敗しました");

					for (unsigned int i = 0; i < MeshIndex; i++)
					{
						SafeRelease(m_ppVertexBuffer[i]);
					}
					SafeDeleteArray(m_ppVertexBuffer);

					return false;
				}
			}
			return true;
		}

		bool FbxModel::CreateSamplerState()
		{
			// サンプラの設定.
			D3D11_SAMPLER_DESC SamplerDesc;
			ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
			SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.MipLODBias = 0;
			SamplerDesc.MaxAnisotropy = 0;
			SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			for (int i = 0; i < 4; i++)
			{
				SamplerDesc.BorderColor[i] = 0.0f;
			}
			SamplerDesc.MinLOD = 0;
			SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


			// サンプラの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateSamplerState(
				&SamplerDesc,
				&m_pSamplerState)))
			{
				OutputErrorLog("サンプラステートの生成に失敗");
				return false;
			}

			return true;
		}

		bool FbxModel::CreateConstantBuffer()
		{
			// 定数バッファの設定.
			D3D11_BUFFER_DESC ConstantBufferDesc;
			ConstantBufferDesc.ByteWidth = sizeof(MATERIAL_CONSTANT_BUFFER);
			ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDesc.MiscFlags = 0;
			ConstantBufferDesc.StructureByteStride = 0;

			// 定数バッファの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
				&ConstantBufferDesc,
				nullptr,
				&m_pMaterialConstantBuffer)))
			{
				OutputErrorLog("定数バッファ生成に失敗しました");
				return false;
			}

			return true;
		}

		void FbxModel::ReleaseIndexBuffer()
		{
			if (m_ppIndexBuffer != nullptr)
			{
				for (unsigned int i = 0; i < m_MeshData.size(); i++)
				{
					SafeRelease(m_ppIndexBuffer[i]);
				}
				SafeDeleteArray(m_ppIndexBuffer);
			}
		}

		void FbxModel::ReleaseVertexBuffer()
		{
			if (m_ppVertexData != nullptr)
			{
				for (unsigned int i = 0; i < m_MeshData.size(); i++)
				{
					SafeDelete(m_ppVertexData[i]);
				}
				SafeDeleteArray(m_ppVertexData);
			}

			if (m_ppVertexBuffer != nullptr)
			{
				for (unsigned int i = 0; i < m_MeshData.size(); i++)
				{
					SafeRelease(m_ppVertexBuffer[i]);
				}
				SafeDeleteArray(m_ppVertexBuffer);
			}
		}

		void FbxModel::ReleaseSamplerState()
		{
			SafeRelease(m_pSamplerState);
		}

		void FbxModel::ReleaseConstantBuffer()
		{
			SafeRelease(m_pMaterialConstantBuffer);
		}

		void FbxModel::WriteConstantBuffer(int _meshNum)
		{
			D3D11_MAPPED_SUBRESOURCE SubResourceData;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(
				m_pMaterialConstantBuffer,
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&SubResourceData)))
			{
				// マテリアルデータを定数バッファに詰める.
				MATERIAL_CONSTANT_BUFFER ConstantBuffer;
				ConstantBuffer.Diffuse = static_cast<D3DXVECTOR4>(m_MeshData[_meshNum].pMaterialData->pMaterial.Diffuse);
				ConstantBuffer.Ambient = static_cast<D3DXVECTOR4>(m_MeshData[_meshNum].pMaterialData->pMaterial.Ambient);
				ConstantBuffer.Specular = static_cast<D3DXVECTOR4>(m_MeshData[_meshNum].pMaterialData->pMaterial.Specular);
				ConstantBuffer.Emissive = static_cast<D3DXVECTOR4>(m_MeshData[_meshNum].pMaterialData->pMaterial.Emissive);

				memcpy_s(
					SubResourceData.pData,
					SubResourceData.RowPitch,
					reinterpret_cast<void*>(&ConstantBuffer),
					sizeof(ConstantBuffer));

				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pMaterialConstantBuffer, 0);
			}
		}
	}
}

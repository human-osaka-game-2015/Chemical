/**
 * @file   Dx11FbxLoader.cpp
 * @brief  FbxLoaderクラスの実装
 * @author morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11FbxLoader.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------------------------------------
		// Static Private Variables
		//----------------------------------------------------------------------------------------------------
		const D3DXCOLOR FbxLoader::m_DefaultAmbient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//----------------------------------------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------------------------------------
		FbxLoader::FbxLoader(GraphicsDevice* _pGraphicsDevice) :
			m_pGraphicsDevice(_pGraphicsDevice),
			m_pFbxManager(nullptr),
			m_pFbxScene(nullptr),
			m_pFbxImporter(nullptr),
			m_pFbxIOSettings(nullptr),
			m_pModel(nullptr)
		{
		}

		FbxLoader::~FbxLoader()
		{
		}


		//----------------------------------------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------------------------------------
		bool FbxLoader::Initialize()
		{
			MyAssert(m_pFbxManager != nullptr, "FbxLoaderオブジェクトは既に初期化されています");

			if (!InitFbxManager())
			{
				return false;
			}

			if (!InitFbxScene())
			{
				ReleaseFbxManager();
				return false;
			}

			if (!InitFbxImporter())
			{
				ReleaseFbxScene();
				ReleaseFbxManager();
				return false;
			}

			if (!InitFbxIOSettings())
			{
				ReleaseFbxImporter();
				ReleaseFbxScene();
				ReleaseFbxManager();
				return false;
			}

			return true;
		}

		void FbxLoader::Finalize()
		{
			ReleaseFbxIOSettings();
			ReleaseFbxImporter();
			ReleaseFbxScene();
			ReleaseFbxManager();
		}

		bool FbxLoader::LoadFbxModel(FbxModel* _pModel, LPCTSTR _pFileName)
		{
			m_pModel = _pModel;
			if (!m_pFbxImporter->Initialize(_pFileName, -1, m_pFbxIOSettings))
			{
				OutputErrorLog("FbxImporterのInitializeに失敗しました");
				return false;
			}

			if (!m_pFbxImporter->Import(m_pFbxScene))
			{
				OutputErrorLog("FbxImporterのImportに失敗しました");
				return false;
			}

			FbxGeometryConverter GeometryConverter(m_pFbxManager);
			if (!GeometryConverter.Triangulate(m_pFbxScene, true))
			{
				OutputErrorLog("三角形化に失敗しました");
				return false;
			}

			FbxNode* pNode = m_pFbxScene->GetRootNode();
			RecursiveNode(pNode);

			return true;
		}

		void FbxLoader::RecursiveNode(FbxNode* _pFbxNode)
		{
			FbxNode* pChildNode = nullptr;
			int ChildCount = _pFbxNode->GetChildCount();
			for (int i = 0; i < ChildCount; i++)
			{
				pChildNode = _pFbxNode->GetChild(i);
				RecursiveNode(pChildNode);
			}

			fbxsdk::FbxNodeAttribute* pAttribute = _pFbxNode->GetNodeAttribute();

			if (pAttribute != nullptr)
			{
				switch (pAttribute->GetAttributeType())
				{
				case fbxsdk::FbxNodeAttribute::eMesh:

					LoadMesh(pAttribute);

					break;
				}
			}
		}

		bool FbxLoader::LoadMesh(FbxNodeAttribute* _pAttribute)
		{
			FbxMesh* pFbxMesh = reinterpret_cast<FbxMesh*>(_pAttribute);
			FbxModel::MESH_DATA MeshData;
			ZeroMemory(&MeshData, sizeof(FbxModel::MESH_DATA));

			if (!LoadMeshVertexData(pFbxMesh, &MeshData))
			{
				OutputErrorLog("頂点情報の読み込みに失敗しました");
				return false;
			}

			if (!LoadMeshNormalData(pFbxMesh, &MeshData))
			{
				OutputErrorLog("法線情報の読み込みに失敗しました");
				return false;
			}

			if (!LoadMeshTextureData(pFbxMesh, &MeshData))
			{
				OutputErrorLog("テクスチャ情報の読み込みに失敗しました");
				return false;
			}

			if (!LoadMeshMaterialData(pFbxMesh, &MeshData))
			{
				OutputErrorLog("マテリアル情報の読み込みに失敗しました");
				return false;
			}

			if (!LoadMeshAnimationData(pFbxMesh, &MeshData))
			{
				OutputErrorLog("アニメーション情報の読み込みに失敗しました");
				return false;
			}

			if (!MeshDataConvert(&MeshData))
			{
				OutputErrorLog("モデルデータの変換に失敗しました");
				return false;
			}

			m_pModel->AddMeshData(&MeshData);

			return true;
		}

		bool FbxLoader::LoadMeshVertexData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
		{
			FbxModel::VERTEX_DATA* pVertex = new FbxModel::VERTEX_DATA;

			// 総ポリゴン数.
			int PolygonNum = _pMesh->GetPolygonCount();

			// 全ての頂点数(インデックスの数).
			int PolygonVertexNum = _pMesh->GetPolygonVertexCount();

			// インデックスデータ.
			int* pIndexAry = _pMesh->GetPolygonVertices();

			// インデックスバッファが指す頂点数.
			int ControlPositionNum = _pMesh->GetControlPointsCount();

			// インデックスバッファが指す頂点.
			fbxsdk::FbxVector4* pFbxVec = _pMesh->GetControlPoints();


			pVertex->PolygonNum = PolygonNum;
			pVertex->PolygonVertexNum = PolygonVertexNum;
			pVertex->ControlPositionNum = ControlPositionNum;

			pVertex->pIndexAry = new int[PolygonVertexNum];
			for (int i = 0; i < PolygonVertexNum; i++)
			{
				pVertex->pIndexAry[i] = pIndexAry[i];
			}

			pVertex->pVertex = new D3DXVECTOR3[ControlPositionNum];
			for (int i = 0; i < ControlPositionNum; i++)
			{
				pVertex->pVertex[i].x = static_cast<float>(pFbxVec[i][0]);
				pVertex->pVertex[i].y = static_cast<float>(pFbxVec[i][1]);
				pVertex->pVertex[i].z = static_cast<float>(pFbxVec[i][2]);
			}

			_pMeshData->pVertexData = pVertex;

			return true;
		}

		bool FbxLoader::LoadMeshNormalData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
		{
			int NormalSetCount = _pMesh->GetElementNormalCount();
			FbxModel::NORMAL_DATA* pNormalData = new FbxModel::NORMAL_DATA;

			for (int NormalIndex = 0; NormalIndex < NormalSetCount; NormalIndex++)
			{
				if (NormalIndex >= 1)
				{
					OutputErrorLog("法線セットが複数あります(対応していません)\n一番最初の法線セットを適応させます");
					break;
				}

				fbxsdk::FbxGeometryElementNormal* pNormal = _pMesh->GetElementNormal(NormalIndex);	// 法線セットの取得.
				FbxGeometryElement::EMappingMode MappingMode = pNormal->GetMappingMode();			// マッピングモード取得.
				FbxGeometryElement::EReferenceMode ReferenceMode = pNormal->GetReferenceMode();		// リファレンスモード取得.

				switch (MappingMode)
				{
				case FbxGeometryElement::eByPolygonVertex:
					switch (ReferenceMode)
					{
					case FbxGeometryElement::eDirect:
						pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
						for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
						{
							pNormalData[NormalIndex].pNormalVec[i].x = float(pNormal->GetDirectArray().GetAt(i)[0]);
							pNormalData[NormalIndex].pNormalVec[i].y = float(pNormal->GetDirectArray().GetAt(i)[1]);
							pNormalData[NormalIndex].pNormalVec[i].z = float(pNormal->GetDirectArray().GetAt(i)[2]);
						}
						break;
					default:
						/// 不明なモードは空データで対応.

						pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
						for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
						{
							pNormalData[NormalIndex].pNormalVec[i].x = 0.0f;
							pNormalData[NormalIndex].pNormalVec[i].y = 0.0f;
							pNormalData[NormalIndex].pNormalVec[i].z = 0.0f;
						}
						break;
					}
					break;
				case FbxGeometryElement::eByControlPoint:

					switch (ReferenceMode)
					{
					case FbxGeometryElement::eDirect:
						pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
						for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
						{
							pNormalData[NormalIndex].pNormalVec[i].x = float(pNormal->GetDirectArray().GetAt(_pMeshData->pVertexData->pIndexAry[i])[0]);
							pNormalData[NormalIndex].pNormalVec[i].y = float(pNormal->GetDirectArray().GetAt(_pMeshData->pVertexData->pIndexAry[i])[1]);
							pNormalData[NormalIndex].pNormalVec[i].z = float(pNormal->GetDirectArray().GetAt(_pMeshData->pVertexData->pIndexAry[i])[2]);
						}
						break;
					case FbxGeometryElement::eIndexToDirect:
						break;
					default:
						pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
						for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
						{
							pNormalData[NormalIndex].pNormalVec[i].x = 0.0f;
							pNormalData[NormalIndex].pNormalVec[i].y = 0.0f;
							pNormalData[NormalIndex].pNormalVec[i].z = 0.0f;
						}
						break;
					}

					break;
				default:

					pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
					for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
					{
						pNormalData[NormalIndex].pNormalVec[i].x = 0.0f;
						pNormalData[NormalIndex].pNormalVec[i].y = 0.0f;
						pNormalData[NormalIndex].pNormalVec[i].z = 0.0f;
					}
					break;
				}
			}

			_pMeshData->pNormalData = pNormalData;

			return true;
		}

		bool FbxLoader::LoadMeshTextureData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
		{
			std::vector<fbxsdk::FbxString> UvSetName;
			int UVSetCount = _pMesh->GetElementUVCount();

			FbxModel::TEXTURE_DATA* pTextureData = new FbxModel::TEXTURE_DATA;	// UVセットの数確保.
			pTextureData->pTextureUVData = new FbxModel::TEXTURE_UV_DATA[UVSetCount];
			pTextureData->TextureUVCount = UVSetCount;
			D3DXVECTOR2** ppTextureUV = new D3DXVECTOR2*[UVSetCount];
			for (int i = 0; i < UVSetCount; i++)
			{
				ppTextureUV[i] = new D3DXVECTOR2[_pMeshData->pVertexData->PolygonVertexNum];
			}


			for (int i = 0; i < UVSetCount; i++)
			{
				fbxsdk::FbxGeometryElementUV* UVSet = _pMesh->GetElementUV(i);					// UVセットの取得.
				FbxGeometryElement::EMappingMode MappingMode = UVSet->GetMappingMode();			// マッピングモードの取得.
				FbxGeometryElement::EReferenceMode ReferenceMode = UVSet->GetReferenceMode();	// リファレンスモード取得.

				switch (MappingMode)
				{
				case FbxGeometryElement::eByPolygonVertex:

					switch (ReferenceMode)
					{
					case FbxGeometryElement::eDirect:
					{
						for (int n = 0; n < _pMeshData->pVertexData->PolygonVertexNum; n++)
						{
							ppTextureUV[i][n].x = static_cast<float>(UVSet->GetDirectArray().GetAt(n)[0]);
							ppTextureUV[i][n].y = 1.0f - static_cast<float>(UVSet->GetDirectArray().GetAt(n)[1]);
						}

						UvSetName.push_back(UVSet->GetName());
					}
					break;
					case FbxGeometryElement::eIndexToDirect:
					{
						FbxLayerElementArrayTemplate<int>* UVIndex = &UVSet->GetIndexArray();
						for (int n = 0; n < _pMeshData->pVertexData->PolygonVertexNum; n++)
						{
							int Index = UVIndex->GetAt(n);
							ppTextureUV[i][n].x = static_cast<float>(UVSet->GetDirectArray().GetAt(Index)[0]);
							ppTextureUV[i][n].y = 1.0f - static_cast<float>(UVSet->GetDirectArray().GetAt(Index)[1]);
						}

						UvSetName.push_back(UVSet->GetName());
					}
					break;
					default:
						return false;
						break;
					}

					break;
				default:
					return false;
					break;
				}

				pTextureData->pTextureUVData[i].pTextureUV = ppTextureUV[i];
				pTextureData->pTextureUVData[i].pUVSetName = UVSet->GetName();
			}

			delete[] ppTextureUV;

			_pMeshData->pTextureData = pTextureData;

			return true;
		}

		bool FbxLoader::LoadMeshMaterialData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
		{
			std::vector<FbxModel::MATERIAL> pMaterial;
			int								TextureFileCount = 0;
			std::vector<const char*>		TextureFileName;
			std::vector<fbxsdk::FbxString>	TextureUvSetName;


			fbxsdk::FbxNode* Node = _pMesh->GetNode();
			int MaterialCount = Node->GetMaterialCount();

			FbxModel::MATERIAL_DATA* pMaterialData = new FbxModel::MATERIAL_DATA[MaterialCount];


			for (int i = 0; i < MaterialCount; i++)
			{
				fbxsdk::FbxSurfaceMaterial* Material = Node->GetMaterial(i);	// マテリアルの取得.

				if (Material->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
				{
					// Lambertにダウンキャスト.
					fbxsdk::FbxSurfaceLambert* lambert = reinterpret_cast<fbxsdk::FbxSurfaceLambert*>(Material);

					FbxModel::MATERIAL MaterialData;
					ZeroMemory(&MaterialData, sizeof(MaterialData));

					// アンビエントの取得.
					MaterialData.Ambient.r = (float)lambert->Ambient.Get().mData[0] * (float)lambert->AmbientFactor.Get();
					MaterialData.Ambient.g = (float)lambert->Ambient.Get().mData[1] * (float)lambert->AmbientFactor.Get();
					MaterialData.Ambient.b = (float)lambert->Ambient.Get().mData[2] * (float)lambert->AmbientFactor.Get();
					GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sAmbient, &TextureFileName, &TextureUvSetName, &TextureFileCount);

					MaterialData.Ambient = m_DefaultAmbient; ///@todo デフォルトのアンビエントを使うようにする


					// ディフューズの取得.
					MaterialData.Diffuse.r = (float)lambert->Diffuse.Get().mData[0] * (float)lambert->DiffuseFactor.Get();
					MaterialData.Diffuse.g = (float)lambert->Diffuse.Get().mData[1] * (float)lambert->DiffuseFactor.Get();
					MaterialData.Diffuse.b = (float)lambert->Diffuse.Get().mData[2] * (float)lambert->DiffuseFactor.Get();
					GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sDiffuse, &TextureFileName, &TextureUvSetName, &TextureFileCount);

					// エミッシブの取得.
					MaterialData.Emissive.r = (float)lambert->Emissive.Get().mData[0] * (float)lambert->EmissiveFactor.Get();
					MaterialData.Emissive.g = (float)lambert->Emissive.Get().mData[1] * (float)lambert->EmissiveFactor.Get();
					MaterialData.Emissive.b = (float)lambert->Emissive.Get().mData[2] * (float)lambert->EmissiveFactor.Get();
					GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sEmissive, &TextureFileName, &TextureUvSetName, &TextureFileCount);

					// 透過度の取得.
					MaterialData.Ambient.a = (float)lambert->TransparentColor.Get().mData[0];
					MaterialData.Diffuse.a = (float)lambert->TransparentColor.Get().mData[1];
					MaterialData.Emissive.a = (float)lambert->TransparentColor.Get().mData[2];
					GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sTransparentColor, &TextureFileName, &TextureUvSetName, &TextureFileCount);


					// 法線マップの取得.
					GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sNormalMap, &TextureFileName, &TextureUvSetName, &TextureFileCount);

					pMaterial.push_back(MaterialData);
				}
				else
				{
					return false;
				}

				pMaterialData[i].pMaterial = pMaterial[i];
				pMaterialData[i].TextureCount = TextureFileCount;
				pMaterialData[i].pTextureName = new LPCTSTR[TextureFileCount];
				pMaterialData[i].pTextureUVSetName = new LPCTSTR[TextureFileCount];
				pMaterialData[i].pTextureView = new ID3D11ShaderResourceView*[TextureFileCount];
				for (int n = 0; n < TextureFileCount; n++)
				{
					pMaterialData[i].pTextureName[n] = TextureFileName[n];
					pMaterialData[i].pTextureUVSetName[n] = TextureUvSetName[n];

					// テクスチャ読み込みの設定.
					D3DX11_IMAGE_LOAD_INFO LoadInfo;
					ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
					LoadInfo.Width = D3DX11_DEFAULT;
					LoadInfo.Height = D3DX11_DEFAULT;
					LoadInfo.Depth = D3DX11_DEFAULT;
					LoadInfo.FirstMipLevel = D3DX11_DEFAULT;
					LoadInfo.MipLevels = 1;
					LoadInfo.Usage = D3D11_USAGE_DEFAULT;
					LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					LoadInfo.CpuAccessFlags = 0;
					LoadInfo.MiscFlags = 0;
					LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
					LoadInfo.Filter = D3DX11_FILTER_POINT;
					LoadInfo.MipFilter = D3DX11_FILTER_POINT;
					LoadInfo.pSrcInfo = nullptr;

					ID3D11ShaderResourceView* pResourceView = nullptr;
					if (FAILED(D3DX11CreateShaderResourceViewFromFile(
						m_pGraphicsDevice->GetDevice(),
						TextureFileName[n],
						&LoadInfo,
						nullptr,
						&pResourceView,
						nullptr)))
					{
						OutputErrorLog("テクスチャの読み込みに失敗しました");
						return false;
					}

					pMaterialData[i].pTextureView[n] = pResourceView;
				}
			}

			_pMeshData->pMaterialData = pMaterialData;

			return true;
		}

		bool FbxLoader::LoadMeshAnimationData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
		{
			/// @todo アニメーションデータの取得は未実装.
			return true;
		}

		bool FbxLoader::MeshDataConvert(FbxModel::MESH_DATA* _pMeshData)
		{
			FbxModel::VERTEX_DATA* pVertexData = new FbxModel::VERTEX_DATA;
			FbxModel::VERTEX_DATA* pBaseVertexData = _pMeshData->pVertexData;

			pVertexData->ControlPositionNum = pBaseVertexData->ControlPositionNum;
			pVertexData->PolygonNum = pBaseVertexData->PolygonNum;
			pVertexData->PolygonVertexNum = pBaseVertexData->PolygonVertexNum;
			pVertexData->pVertex = new D3DXVECTOR3[pBaseVertexData->PolygonVertexNum];
			pVertexData->pIndexAry = new int[pBaseVertexData->PolygonVertexNum];


			FbxModel::TEXTURE_DATA* pTextureData = new FbxModel::TEXTURE_DATA;
			FbxModel::TEXTURE_DATA* pBaseTextureData = _pMeshData->pTextureData;

			pTextureData->pTextureUVData = new FbxModel::TEXTURE_UV_DATA[pBaseTextureData->TextureUVCount];
			pTextureData->TextureUVCount = pBaseTextureData->TextureUVCount;
			for (int i = 0; i < pBaseTextureData->TextureUVCount; i++)
			{
				pTextureData->pTextureUVData[i].pTextureUV = new D3DXVECTOR2[pBaseVertexData->PolygonVertexNum];
				pTextureData->pTextureUVData[i].pUVSetName = pBaseTextureData->pTextureUVData[i].pUVSetName;
			}


			for (int i = 0; i < pBaseVertexData->PolygonVertexNum; i++)
			{
				int Index = pBaseVertexData->pIndexAry[i];
				pVertexData->pVertex[i] = pBaseVertexData->pVertex[Index];
				pVertexData->pIndexAry[i] = i;	///@todo これじゃあindex描画使う意味ないけど現状はこれで対応する.
			}

			for (int n = 0; n < pBaseTextureData->TextureUVCount; n++)
			{
				for (int k = 0; k < pBaseVertexData->PolygonVertexNum; k++)
				{
					pTextureData->pTextureUVData[n].pTextureUV[k] = pBaseTextureData->pTextureUVData[n].pTextureUV[k];
				}
			}

			pVertexData->ControlPositionNum = pBaseVertexData->PolygonVertexNum;	// インデックス数変更.


			///@todo 法線対応する.


			// テクスチャ関連のデータ入れ替え.
			for (int n = 0; n < pBaseTextureData->TextureUVCount; n++)
			{
				SafeDeleteArray(_pMeshData->pTextureData->pTextureUVData[n].pTextureUV);
			}
			SafeDeleteArray(_pMeshData->pTextureData->pTextureUVData);
			SafeDelete(_pMeshData->pTextureData);
			_pMeshData->pTextureData = pTextureData;

			// 頂点関連のデータ入れ替え.
			SafeDeleteArray(_pMeshData->pVertexData->pVertex);
			SafeDeleteArray(_pMeshData->pVertexData->pIndexAry);
			SafeDelete(_pMeshData->pVertexData);
			_pMeshData->pVertexData = pVertexData;

			return true;
		}

		void FbxLoader::GetTextureName(
			fbxsdk::FbxSurfaceMaterial* _pMaterial,
			LPCTSTR _pMatFlag,
			std::vector<LPCTSTR>* _pOutFileName,
			std::vector<fbxsdk::FbxString>* _pOutUvSetName,
			int* _pOutCount)
		{
			fbxsdk::FbxProperty Property = _pMaterial->FindProperty(_pMatFlag);
			int LayerTextureCount = Property.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

			if (LayerTextureCount == 0)
			{
				int TextureCount = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
				for (int i = 0; i < TextureCount; i++)
				{
					(*_pOutCount)++;
					fbxsdk::FbxFileTexture* fbxTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<fbxsdk::FbxFileTexture>(i));
					_pOutUvSetName->push_back(fbxTexture->UVSet.Get());
					_pOutFileName->push_back(fbxTexture->GetRelativeFileName());
				}
			}
		}


		//----------------------------------------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------------------------------------
		bool FbxLoader::InitFbxManager()
		{
			m_pFbxManager = fbxsdk::FbxManager::Create();
			if (m_pFbxManager == nullptr)
			{
				OutputErrorLog("FbxManagerクラスの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool FbxLoader::InitFbxScene()
		{
			m_pFbxScene = fbxsdk::FbxScene::Create(m_pFbxManager, "");
			if (m_pFbxScene == nullptr)
			{
				OutputErrorLog("FbxSceneクラスの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool FbxLoader::InitFbxImporter()
		{
			m_pFbxImporter = fbxsdk::FbxImporter::Create(m_pFbxManager, "");
			if (m_pFbxImporter == nullptr)
			{
				OutputErrorLog("FbxImporterクラスの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool FbxLoader::InitFbxIOSettings()
		{
			m_pFbxIOSettings = fbxsdk::FbxIOSettings::Create(m_pFbxManager, IOSROOT);
			if (m_pFbxIOSettings == nullptr)
			{
				OutputErrorLog("FbxIOSettingsクラスの生成に失敗しました");
				return false;
			}
			m_pFbxManager->SetIOSettings(m_pFbxIOSettings);

			return true;
		}

		void FbxLoader::ReleaseFbxManager()
		{
			SafeDestroy(m_pFbxManager);
		}

		void FbxLoader::ReleaseFbxScene()
		{
			SafeDestroy(m_pFbxScene);
		}

		void FbxLoader::ReleaseFbxImporter()
		{
			SafeDestroy(m_pFbxImporter);
		}

		void FbxLoader::ReleaseFbxIOSettings()
		{
			SafeDestroy(m_pFbxIOSettings);
		}
	}
}


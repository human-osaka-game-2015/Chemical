/**
 * @file	MultipleVertex2D.cpp
 * @brief	複数の矩形描画クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11MultipleVertex2D.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		MultipleVertex2D::MultipleVertex2D() :
			m_pGraphicsDevice(nullptr),
			m_pVertexShader(nullptr),
			m_pVertexCompiledShader(nullptr),
			m_pVertexLayout(nullptr),
			m_pPixelShader(nullptr),
			m_pPixelCompiledShader(nullptr),
			m_pBlendState(nullptr),
			m_pSamplerState(nullptr),
			m_pDepthStencilState(nullptr),
			m_pVertexBuffer(nullptr),
			m_pConstantBuffer(nullptr),
			m_pInstanceBuffer(nullptr),
			m_pTexture(nullptr),
			m_pInstanceData(nullptr),
			m_WindowWidth(0),
			m_WindowHeight(0)
		{
		}

		MultipleVertex2D::~MultipleVertex2D()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool MultipleVertex2D::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			if (m_pGraphicsDevice != nullptr)
			{
				OutputErrorLog("このオブジェクトは既に初期化されています");
				return false;
			}

			m_pGraphicsDevice = _pGraphicsDevice;

			RECT WindowRect;
			GetWindowRect(m_pGraphicsDevice->GetMainWindowHandle(), &WindowRect);
			m_WindowWidth = static_cast<float>(WindowRect.right - WindowRect.left);
			m_WindowHeight = static_cast<float>(WindowRect.bottom - WindowRect.top);

			if (!CreateVertexShader())	return false;
			if (!CreateVertexLayout())	return false;
			if (!CreatePixelShader())	return false;
			if (!CreateState())			return false;

			return true;
		}

		void MultipleVertex2D::Finalize()
		{
			ReleaseState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
		}

		bool MultipleVertex2D::CreateVertexBuffer(
			const D3DXVECTOR2* _pSize, 
			const D3DXVECTOR2* _pMinUV, 
			const D3DXVECTOR2* _pMaxUV, 
			const D3DXCOLOR* _pColor)
		{
			if (m_pVertexBuffer != nullptr)
			{
				OutputErrorLog("頂点バッファはすでに生成されています");
				return false;
			}

			VERTEX VertexData[VERTEX_NUM] =
			{
				VERTEX{ D3DXVECTOR3(-_pSize->x / 2, -_pSize->y / 2, 0), D3DXVECTOR2(_pMinUV->x, _pMinUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3( _pSize->x / 2, -_pSize->y / 2, 0), D3DXVECTOR2(_pMaxUV->x, _pMinUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3(-_pSize->x / 2,  _pSize->y / 2, 0), D3DXVECTOR2(_pMinUV->x, _pMaxUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3( _pSize->x / 2,  _pSize->y / 2, 0), D3DXVECTOR2(_pMaxUV->x, _pMaxUV->y), *_pColor }
			};

			for (int i = 0; i < VERTEX_NUM; i++)
			{
				m_pVertexData[i].Pos	= VertexData[i].Pos;
				m_pVertexData[i].UV		= VertexData[i].UV;
				m_pVertexData[i].Color	= VertexData[i].Color;
			}

			// 頂点バッファの設定.
			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
			BufferDesc.ByteWidth = sizeof(VERTEX) * VERTEX_NUM;
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			BufferDesc.MiscFlags = 0;
			BufferDesc.StructureByteStride = 0;

			// 頂点バッファに格納するデータの設定.
			D3D11_SUBRESOURCE_DATA ResourceData;
			ZeroMemory(&ResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
			ResourceData.pSysMem = m_pVertexData;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
				&BufferDesc, 
				&ResourceData,
				&m_pVertexBuffer)))
			{
				OutputErrorLog("頂点バッファの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool MultipleVertex2D::CreateInstanceBuffer(D3DXMATRIX* _pMat, int _instanceNum)
		{
			m_InstanceNum = _instanceNum;

			m_pInstanceData = new INSTANCE_DATA[m_InstanceNum];
			for (int i = 0; i < m_InstanceNum; i++)
			{
				D3DXMatrixTranspose(&m_pInstanceData[i].Mat, &_pMat[i]);
			}

			// インスタンスバッファの設定.
			D3D11_BUFFER_DESC InstanceBufferDesc;
			ZeroMemory(&InstanceBufferDesc, sizeof(D3D11_BUFFER_DESC));
			InstanceBufferDesc.ByteWidth = sizeof(INSTANCE_DATA) * m_InstanceNum;
			InstanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			InstanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			InstanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			InstanceBufferDesc.MiscFlags = 0;
			InstanceBufferDesc.StructureByteStride = 0;

			// インスタンスバッファに格納するデータの設定.
			D3D11_SUBRESOURCE_DATA InstanceResourceData;
			ZeroMemory(&InstanceResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
			InstanceResourceData.pSysMem = m_pInstanceData;
			if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateBuffer(
				&InstanceBufferDesc,
				&InstanceResourceData,
				&m_pInstanceBuffer)))
			{
				OutputErrorLog("インスタンスバッファの生成に失敗しました");
				return false;
			}

			return true;
		}

		void MultipleVertex2D::ReleaseVertexBuffer()
		{
			SafeRelease(m_pVertexBuffer);
		}

		void MultipleVertex2D::ReleaseInstanceBuffer()
		{
			SafeDeleteArray(m_pInstanceData);
			SafeRelease(m_pInstanceBuffer);
		}

		bool MultipleVertex2D::WriteConstantBuffer(D3DXVECTOR2 _pos)
		{
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(
				m_pConstantBuffer,
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&MappedResource)))
			{
				CONSTANT_BUFFER ConstantBuffer;
				ConstantBuffer.WindowSize.x = m_WindowWidth;
				ConstantBuffer.WindowSize.y = m_WindowHeight;
				ConstantBuffer.InstancePos = D3DXVECTOR4(_pos.x, _pos.y, 0, 0);

				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					reinterpret_cast<void*>(&ConstantBuffer),
					sizeof(ConstantBuffer));
				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);

				return true;
			}

			return false;
		}

		bool MultipleVertex2D::WriteVertexBuffer()
		{
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(
				m_pVertexBuffer,
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&MappedResource)))
			{
				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					m_pVertexData,
					sizeof(VERTEX) * VERTEX_NUM);

				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pVertexBuffer, 0);

				return true;
			}

			return false;
		}

		void MultipleVertex2D::SetVertex(const D3DXVECTOR2* _pSize)
		{
			m_pVertexData[0].Pos.x = -_pSize->x / 2; m_pVertexData[0].Pos.y = -_pSize->y / 2;
			m_pVertexData[1].Pos.x =  _pSize->x / 2; m_pVertexData[1].Pos.y = -_pSize->y / 2;
			m_pVertexData[2].Pos.x = -_pSize->x / 2; m_pVertexData[2].Pos.y =  _pSize->y / 2;
			m_pVertexData[3].Pos.x =  _pSize->x / 2; m_pVertexData[3].Pos.y =  _pSize->y / 2;
		}

		void MultipleVertex2D::SetUV(const D3DXVECTOR2* _pMinUV, const D3DXVECTOR2* _pMaxUV)
		{
			m_pVertexData[0].UV.x = _pMinUV->x; m_pVertexData[0].UV.y = _pMinUV->y;
			m_pVertexData[1].UV.x = _pMaxUV->x; m_pVertexData[1].UV.y = _pMinUV->y;
			m_pVertexData[2].UV.x = _pMinUV->x; m_pVertexData[2].UV.y = _pMaxUV->y;
			m_pVertexData[3].UV.x = _pMaxUV->x; m_pVertexData[3].UV.y = _pMaxUV->y;
		}

		void MultipleVertex2D::SetColor(const D3DXCOLOR* _pColor)
		{
			m_pVertexData[0].Color = *_pColor;
			m_pVertexData[1].Color = *_pColor;
			m_pVertexData[2].Color = *_pColor;
			m_pVertexData[3].Color = *_pColor;
		}

		bool MultipleVertex2D::WriteInstanceBuffer(const D3DXVECTOR2* _pDrawPos)
		{
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(
				m_pInstanceBuffer,
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&MappedResource)))
			{
				INSTANCE_DATA* pInstanceData = reinterpret_cast<INSTANCE_DATA*>(MappedResource.pData);

				for (int i = 0; i < m_InstanceNum; i++)
				{
					D3DXMATRIX MatWorld, MatTranslate;

					D3DXMatrixIdentity(&MatWorld);
					D3DXMatrixTranslation(&MatTranslate, _pDrawPos[i].x, _pDrawPos[i].y, 0.0f);
					D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTranslate);
					D3DXMatrixTranspose(&pInstanceData[i].Mat, &MatWorld);
				}

				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pInstanceBuffer, 0);

				return true;
			}

			return false;
		}

		void MultipleVertex2D::ShaderSetup()
		{
			m_pGraphicsDevice->GetDeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->HSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->DSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			m_pGraphicsDevice->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
			m_pGraphicsDevice->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

			m_pGraphicsDevice->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
		}

		void MultipleVertex2D::TextureSetup()
		{
			// テクスチャインターフェースがあれば貼り付ける.
			if (m_pTexture != nullptr)
			{
				ID3D11ShaderResourceView* pTextureResource = m_pTexture->Get();
				m_pGraphicsDevice->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);
				m_pGraphicsDevice->GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureResource);
			}
		}

		void MultipleVertex2D::DepthStencilStateSetup()
		{
			m_pGraphicsDevice->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencilState, 0);
		}

		void MultipleVertex2D::BlendStateSetup()
		{
			m_pGraphicsDevice->GetDeviceContext()->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);
		}

		void MultipleVertex2D::DefaultDraw(const D3DXVECTOR2* _pDrawPos)
		{
			if (!WriteInstanceBuffer(_pDrawPos))	return;

			ShaderSetup();
			TextureSetup();
			DepthStencilStateSetup();
			BlendStateSetup();
			Draw();
		}

		void MultipleVertex2D::Draw()
		{
			ID3D11Buffer* pBuffer[2] = { m_pVertexBuffer, m_pInstanceBuffer };
			UINT Stride[2] = { sizeof(VERTEX), sizeof(INSTANCE_DATA) };
			UINT Offset[2] = { 0, 0 };
			m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 2, pBuffer, Stride, Offset);

			m_pGraphicsDevice->GetDeviceContext()->DrawInstanced(VERTEX_NUM, m_InstanceNum, 0, 0);
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		bool MultipleVertex2D::CreateVertexShader()
		{
			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Vertex2D\\MultipleVertex2D\\Effect\\Vertex2D.fx"),
				nullptr,
				nullptr,
				"VS",
				"vs_5_0",
				Flag1,
				0,
				nullptr,
				&m_pVertexCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("頂点シェーダーの読み込みに失敗しました");
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateVertexShader(
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				nullptr,
				&m_pVertexShader)))
			{
				OutputErrorLog("頂点シェーダーの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool MultipleVertex2D::CreateVertexLayout()
		{
			D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA,   0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 12, D3D11_INPUT_PER_VERTEX_DATA,   0 },
				{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA,   0 },
				{ "MATRIX",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,  0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MATRIX",   1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MATRIX",   2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MATRIX",   3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
			};

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateInputLayout(
				InputElementDesc,
				sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				&m_pVertexLayout)))
			{
				OutputErrorLog("入力レイアウトの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool MultipleVertex2D::CreatePixelShader()
		{
			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Vertex2D\\MultipleVertex2D\\Effect\\Vertex2D.fx"),
				nullptr,
				nullptr,
				"PS",
				"ps_5_0",
				Flag1,
				0,
				nullptr,
				&m_pPixelCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("ピクセルシェーダーの読み込みに失敗しました");
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreatePixelShader(
				m_pPixelCompiledShader->GetBufferPointer(),
				m_pPixelCompiledShader->GetBufferSize(),
				nullptr,
				&m_pPixelShader)))
			{
				OutputErrorLog("ピクセルシェーダーの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool MultipleVertex2D::CreateState()
		{
			D3D11_BLEND_DESC BlendDesc;
			ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
			BlendDesc.AlphaToCoverageEnable = false;
			BlendDesc.IndependentBlendEnable = false;
			BlendDesc.RenderTarget[0].BlendEnable = true;
			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBlendState(
				&BlendDesc,
				&m_pBlendState)))
			{
				OutputErrorLog("ブレンドステートの生成に失敗しました");
				return false;
			}

			D3D11_SAMPLER_DESC SamplerDesc;
			ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
			SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateSamplerState(
				&SamplerDesc,
				&m_pSamplerState)))
			{
				OutputErrorLog("サンプラステートの生成に失敗しました");
				return false;
			}

			D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
			ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
			DepthStencilDesc.DepthEnable = TRUE;
			DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			DepthStencilDesc.StencilEnable = FALSE;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateDepthStencilState(
				&DepthStencilDesc,
				&m_pDepthStencilState)))
			{
				OutputErrorLog("深度ステンシルステートの生成に失敗しました");
				return false;
			}

			D3D11_BUFFER_DESC ConstantBufferDesc;
			ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
			ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);
			ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDesc.MiscFlags = 0;
			ConstantBufferDesc.StructureByteStride = 0;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
				&ConstantBufferDesc,
				nullptr,
				&m_pConstantBuffer)))
			{
				OutputErrorLog("定数バッファの生成に失敗しました");
				return false;
			}

			if (!WriteConstantBuffer())	return false;

			return true;
		}

		void MultipleVertex2D::ReleaseVertexShader()
		{
			SafeRelease(m_pVertexShader);
			SafeRelease(m_pVertexCompiledShader);
		}

		void MultipleVertex2D::ReleaseVertexLayout()
		{
			SafeRelease(m_pVertexLayout);
		}

		void MultipleVertex2D::ReleasePixelShader()
		{
			SafeRelease(m_pPixelShader);
			SafeRelease(m_pPixelCompiledShader);
		}

		void MultipleVertex2D::ReleaseState()
		{
			SafeRelease(m_pConstantBuffer);
			SafeRelease(m_pDepthStencilState);
			SafeRelease(m_pSamplerState);
			SafeRelease(m_pBlendState);
		}
	}
}

/**
 * @file	MultipleObject2DBase.cpp
 * @brief	複数オブジェクト描画クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MultipleObject2DBase.h"

#include "Debugger\Debugger.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------
MultipleObject2DBase::MultipleObject2DBase() :
	m_pMultipleVertex(nullptr),
	m_Size(D3DXVECTOR2(0, 0))
{
	m_pDrawTask = new Lib::Draw2DTask();
	m_pUpdateTask = new Lib::UpdateTask();

	m_pDrawTask->SetObject(this);
	m_pUpdateTask->SetObject(this);
}


MultipleObject2DBase::~MultipleObject2DBase()
{
	SafeDelete(m_pUpdateTask);
	SafeDelete(m_pDrawTask);
}


//----------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------
bool MultipleObject2DBase::Initialize()
{
	return true;
}

void MultipleObject2DBase::Finalize()
{
}

void MultipleObject2DBase::UpdateStartUp()
{
}

void MultipleObject2DBase::Update()
{
}

void MultipleObject2DBase::DrawStartUp()
{
}

void MultipleObject2DBase::Draw()
{
}


//----------------------------------------------------------------------
// Protected Functions
//----------------------------------------------------------------------
bool MultipleObject2DBase::CreateVertex2D()
{
	m_pMultipleVertex = new Lib::Dx11::MultipleVertex2D();
	if (!m_pMultipleVertex->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
	{
		OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
		return false;
	}

	if (!m_pMultipleVertex->CreateVertexBuffer(&m_Size))
	{
		OutputErrorLog("頂点バッファの生成に失敗しました");
		return false;
	}

	return true;
}

void MultipleObject2DBase::ReleaseVertex2D()
{
	if (m_pMultipleVertex != nullptr)
	{
		m_pMultipleVertex->ReleaseVertexBuffer();
		m_pMultipleVertex->Finalize();
		SafeDelete(m_pMultipleVertex);
	}
}


/**
 * @file	リザルト背景クラス実装
 * @brief	ResultBackground.cpp
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultBackground.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\ResultDefine.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultBackground::ResultBackground()
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);
	}

	ResultBackground::~ResultBackground()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultBackground::Initialize()
	{
		m_ResultFile.Open();
		m_ResultFile.Close();

		char FilePath[256];
		sprintf_s(
			FilePath,
			256,
			"Resource\\ResultScene\\Texture\\Background_%d.png", 
			m_ResultFile.GetClear());

		m_pUpdateTask->SetName("ResultBackground");
		m_pDrawTask->SetName("ResultBackground");

		m_pDrawTask->SetPriority(RESULT_DRAW_BACKGROUND);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			FilePath,
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void ResultBackground::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void ResultBackground::Update()
	{
	}

	void ResultBackground::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

/**
 * @file	StageBackground.cpp
 * @brief	ステージ背景クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageBackground.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageBackground::StageBackground() : 
		m_pPlayFile(nullptr),
		m_CenterPos(0, 0)
	{
		m_Pos = D3DXVECTOR2(640, 360);
		m_Size = D3DXVECTOR2(1280, 720);
	}

	StageBackground::~StageBackground()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageBackground::Initialize()
	{
		int StageNum = 0;
		m_pPlayFile = new GamePlayFile();
		m_pPlayFile->Open();
		StageNum = m_pPlayFile->GetStageNum();
		m_pPlayFile->Close();

		char FilePath[256];
		sprintf_s(FilePath, 256, "Resource\\GameScene\\Texture\\StageBackground%d.png", StageNum);

		m_pUpdateTask->SetName("StageBackground");
		m_pDrawTask->SetName("StageBackground");

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

	void StageBackground::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		SafeDelete(m_pPlayFile);
	}

	void StageBackground::Update()
	{
	}

	void StageBackground::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

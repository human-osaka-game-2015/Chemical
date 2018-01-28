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
#include "..\..\GameDataManager\GameDataManager.h"
#include "GameDefine.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageBackground::StageBackground() : 
		m_pPlayFile(nullptr),
		m_CenterPos(0, 0)
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);

		m_BackgroundPos = D3DXVECTOR2(960, 540);
		m_BackgroundPos2 = D3DXVECTOR2(2880, 540);
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
		char FilePath2[256];
		sprintf_s(FilePath, 256, "Resource\\GameScene\\Texture\\StageBackground%d.png", StageNum);
		sprintf_s(FilePath2, 256, "Resource\\GameScene\\Texture\\StageBackground%d_2.png", StageNum);

		m_pUpdateTask->SetName("StageBackground");
		m_pDrawTask->SetName("StageBackground");

		m_pDrawTask->SetPriority(GAME_DRAW_BACKGROUND);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			FilePath,
			&m_TextureIndex))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			FilePath2,
			&m_TextureIndex2))
		{
			return false;
		}

		return true;
	}

	void StageBackground::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex2);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		SafeDelete(m_pPlayFile);
	}

	void StageBackground::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();

		float ScroolX = ScreenPos.x;
		float ScroolY = ScreenPos.y;
		if (ScroolX > m_Size.x)
			ScroolX -= m_Size.x * static_cast<int>(ScroolX / m_Size.x);

		if (ScroolY > m_Size.y)
			ScroolY += m_Size.y * static_cast<int>(ScroolY / m_Size.y);

		m_BackgroundPos.x = m_Pos.x - ScroolX;
		m_BackgroundPos.y = m_Pos.y - ScroolY;
		m_BackgroundPos2.x = m_Pos.x + m_Size.x - ScroolX;
		m_BackgroundPos2.y = m_Pos.y - ScroolY;
	}

	void StageBackground::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_BackgroundPos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();

		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_BackgroundPos2);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

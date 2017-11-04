/**
 * @file	TitleBackLogo.cpp
 * @brief	タイトルロゴクラス実装
 * @author	morimoto
 */
//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TitleBackLogo.h"

#include "..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	BackLogo::BackLogo()
	{
		m_Pos = D3DXVECTOR2(960, 200);
		m_Size = D3DXVECTOR2(300, 100);
	}

	BackLogo::~BackLogo()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool BackLogo::Initialize()
	{
		m_pDrawTask->SetPriority(TITLE_DRAW_BACK_LOGO);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Texture\\BackLogo.png",
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void BackLogo::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void BackLogo::Update()
	{
	}

	void BackLogo::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}


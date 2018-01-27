/**
 * @file	BackCharacter.cpp
 * @brief	バックキャラクタークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "BackCharacter.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\ResultDefine.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	BackCharacter::BackCharacter()
	{
		m_Pos = D3DXVECTOR2(1600, 540);
		m_Size = D3DXVECTOR2(400, 800);
	}

	BackCharacter::~BackCharacter()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool BackCharacter::Initialize()
	{
		m_ResultFile.Open();
		m_ResultFile.Close();

		char FilePath[256];
		sprintf_s(
			FilePath,
			256,
			"Resource\\ResultScene\\Texture\\Character_%d.png",
			m_ResultFile.GetClear());

		m_pUpdateTask->SetName("BackCharacter");
		m_pDrawTask->SetName("BackCharacter");

		m_pDrawTask->SetPriority(RESULT_DRAW_BACKCHARA);

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

	void BackCharacter::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void BackCharacter::Update()
	{
	}

	void BackCharacter::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

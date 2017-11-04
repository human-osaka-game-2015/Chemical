/**
 * @file	StartButton.cpp
 * @brief	スタートボタンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StartButton.h"

#include "..\..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StartButton::StartButton()
	{
		m_Pos = D3DXVECTOR2(960, 850);
		m_Size = D3DXVECTOR2(300, 100);
	}

	StartButton::~StartButton()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StartButton::Initialize()
	{
		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Texture\\Start.png",
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void StartButton::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();
	}

	void StartButton::Update()
	{
	}

	void StartButton::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

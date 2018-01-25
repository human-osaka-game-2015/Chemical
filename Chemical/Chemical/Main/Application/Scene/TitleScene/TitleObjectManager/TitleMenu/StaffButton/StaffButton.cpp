/**
 * @file	StaffButton.cpp
 * @brief	スタッフボタンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StaffButton.h"

#include "..\..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StaffButton::StaffButton()
	{
		m_Pos = D3DXVECTOR2(990, 850);
		m_Size = D3DXVECTOR2(600, 100);
	}

	StaffButton::~StaffButton()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StaffButton::Initialize()
	{
		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Texture\\Staff.png",
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void StaffButton::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();
	}

	void StaffButton::Update()
	{
	}

	void StaffButton::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

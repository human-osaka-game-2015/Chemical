/**
 * @file	StaffBackground.cpp
 * @brief	スタッフバックグラウンド実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StaffBackground.h"

#include "Math\Math.h"
#include "..\..\StaffDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "EventManager\EventManager.h"
#include "JoyconManager\JoyconManager.h"


namespace Staff
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Background::Background()
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);
	}

	Background::~Background()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Background::Initialize()
	{
		m_pDrawTask->SetPriority(STAFF_DRAW_BACKGROUND);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\StaffScene\\Texture\\Background.png",
			&m_TextureIndex))
		{
			return false;
		}

		m_pEvent = new TitleBackEvent(STAFF_EVENT);

		return true;
	}

	void Background::Finalize()
	{
		SafeDelete(m_pEvent);

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void Background::Update()
	{
		if (SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState()[DIK_SPACE] == 
			Lib::KeyDevice::KEY_PUSH ||
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER)->GetButtonState()[Joycon::A_BUTTON] ==
			Joycon::PUSH_BUTTON)
		{
			SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
				m_pEvent, 
				TO_STRING(STAFF_GROUP));
		}
	}

	void Background::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}

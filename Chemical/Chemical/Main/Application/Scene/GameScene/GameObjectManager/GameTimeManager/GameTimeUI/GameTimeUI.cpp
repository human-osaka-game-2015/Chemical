/**
 * @file	GameTimeUI.cpp
 * @brief	ゲームタイムUIクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameTimeUI.h"

#include "Debugger\Debugger.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 TimeUI::m_DefaultPos = D3DXVECTOR2(70, 650);
	const D3DXVECTOR2 TimeUI::m_DefaultSize = D3DXVECTOR2(32, 64);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	TimeUI::TimeUI() : 
		m_Frame(0),
		m_Seconds(0),
		m_Minute(0)
	{
	}

	TimeUI::~TimeUI()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool TimeUI::Initialize()
	{
		m_pFont = new Lib::Dx11::Font();
		if (!m_pFont->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("フォントオブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pFont->CreateVertexBuffer(&m_DefaultSize))
		{
			OutputErrorLog("フォントオブジェクトの頂点生成に失敗しました");
			return false;
		}

		m_pFont->SetAlignment(false);

		return true;
	}

	void TimeUI::Finalize()
	{
		m_pFont->ReleaseVertexBuffer();
		m_pFont->Finalize();
		SafeDelete(m_pFont);
	}

	void TimeUI::Update()
	{
	}

	void TimeUI::Draw()
	{
		char Str[256];
		sprintf_s(Str, "%d:%d:%d", m_Minute, m_Seconds, m_Frame);	// 現状はフレームで代用.

		m_pFont->Draw(&m_DefaultPos, Str);
	}
}

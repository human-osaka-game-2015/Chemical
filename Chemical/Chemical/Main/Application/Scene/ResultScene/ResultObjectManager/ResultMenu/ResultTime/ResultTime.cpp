/**
 * @file	ResultTime.cpp
 * @brief	リザルト時間クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultTime.h"

#include "..\..\..\ResultDefine.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 ResultTime::m_DefaultPos = D3DXVECTOR2(300, 650);
	const D3DXVECTOR2 ResultTime::m_DefaultSize = D3DXVECTOR2(32, 64);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultTime::ResultTime() :
		m_Seconds(0),
		m_Minute(0)
	{
		m_Pos = m_DefaultPos;
		m_Size = m_DefaultSize;
	}

	ResultTime::~ResultTime()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultTime::Initialize()
	{
		m_pUpdateTask->SetName("ResultTime");
		m_pDrawTask->SetName("ResultTime");

		m_pDrawTask->SetPriority(RESULT_DRAW_FONT);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

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

		m_ResultFile.Open();
		m_Minute = m_ResultFile.GetMinute();
		m_Seconds = m_ResultFile.GetSeconds();

		m_ResultFile.Close();

		return true;
	}

	void ResultTime::Finalize()
	{
		m_pFont->ReleaseVertexBuffer();
		m_pFont->Finalize();
		SafeDelete(m_pFont);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void ResultTime::Update()
	{
	}

	void ResultTime::Draw()
	{
		char Str[256];
		sprintf_s(Str, "TIME    : %dm %ds", m_Minute, m_Seconds);
		m_pFont->Draw(&m_DefaultPos, Str);
	}
}

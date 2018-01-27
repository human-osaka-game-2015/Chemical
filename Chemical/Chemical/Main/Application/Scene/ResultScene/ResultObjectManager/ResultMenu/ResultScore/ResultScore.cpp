/**
 * @file	ResultScore.cpp
 * @brief	リザルトスコアクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultScore.h"

#include "..\..\..\ResultDefine.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 ResultScore::m_DefaultPos = D3DXVECTOR2(100, 450);
	const D3DXVECTOR2 ResultScore::m_DefaultSize = D3DXVECTOR2(32, 64);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultScore::ResultScore() : 
		m_Score(0)
	{
		m_Pos = m_DefaultPos;
		m_Size = m_DefaultSize;
	}

	ResultScore::~ResultScore()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultScore::Initialize()
	{
		m_pUpdateTask->SetName("ResultScore");
		m_pDrawTask->SetName("ResultScore");

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
		m_Score = m_ResultFile.GetScore();

		m_ResultFile.Close();

		return true;
	}

	void ResultScore::Finalize()
	{
		m_pFont->ReleaseVertexBuffer();
		m_pFont->Finalize();
		SafeDelete(m_pFont);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void ResultScore::Update()
	{
	}

	void ResultScore::Draw()
	{
		char Str[256];
		sprintf_s(Str, "Score   : %d", m_Score);
		m_pFont->Draw(&m_DefaultPos, Str);
	}
}

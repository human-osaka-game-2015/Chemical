/**
 * @file	Ranking.cpp
 * @brief	ランキングクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Ranking.h"

#include "..\..\..\ResultDefine.h"
#include <vector>


namespace Result
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 Ranking::m_DefaultPos = D3DXVECTOR2(300, 450);
	const D3DXVECTOR2 Ranking::m_DefaultSize = D3DXVECTOR2(32, 64);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Ranking::Ranking() : 
		m_Ranking(1)
	{
		m_Pos = m_DefaultPos;
		m_Size = m_DefaultSize;
	}

	Ranking::~Ranking()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Ranking::Initialize()
	{
		m_pUpdateTask->SetName("Ranking");
		m_pDrawTask->SetName("Ranking");

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
		int Stage = m_ResultFile.GetStageNum();


		FILE* pFile;
		char FileName[128];
		sprintf_s(FileName, "Resource\\StageSelectScene\\RankingWindow\\RankingData\\Stage%d.csv", Stage);
		fopen_s(&pFile, FileName, "r");

		int CSVData = 0;
		int RankingNum = 0;
		while ((CSVData = fgetc(pFile)) != EOF)
		{
			if (CSVData == '\n')
			{
				RankingNum++;
			}
		}

		std::vector<int> RankingScores;
		RankingScores.resize(RankingNum);

		fseek(pFile, 0, SEEK_SET);
		for (int i = 0; i < RankingNum; i++)
		{
			char tmpTime[16];
			fscanf_s(pFile, "%d,", &RankingScores[i]);
			fscanf_s(pFile, "%s", tmpTime, sizeof(tmpTime));
		}

		fclose(pFile);

		for (int i = 0; i < RankingNum; i++)
		{
			// ランキングファイルはソートされているので.
			// 比較で現在のランキングを取得.
			if (RankingScores[i] < m_ResultFile.GetScore())
			{
				m_Ranking = i + 1;
				break;
			}
		}

		m_ResultFile.Close();

		return true;
	}

	void Ranking::Finalize()
	{
		m_pFont->ReleaseVertexBuffer();
		m_pFont->Finalize();
		SafeDelete(m_pFont);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void Ranking::Update()
	{
	}

	void Ranking::Draw()
	{
		char Str[256];
		sprintf_s(Str, "RANK    : %d", m_Ranking);
		m_pFont->Draw(&m_DefaultPos, Str);
	}
}

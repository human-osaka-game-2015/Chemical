/**
 * @file   ScoreRanking.cpp
 * @brief  ScoreRankingクラスの実装
 * @author fujioka
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ScoreRanking.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include <string>
#include "InputDeviceManager\InputDeviceManager.h"


namespace Select
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const float ScoreRanking::m_FontSize = 20.f;
	const int ScoreRanking::m_ScoreShift = 200;
	const int ScoreRanking::m_NameShift = 200;
	const int ScoreRanking::m_VerticalShift = 70;
	const int ScoreRanking::m_ScrollSpeed = 10;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ScoreRanking::ScoreRanking(int _stageNum) :
		m_StageNum(_stageNum),
		m_RankingNum(0),
		m_pFile(nullptr)
	{
		m_BasePosition = D3DXVECTOR2(1960, 200);
	}

	ScoreRanking::~ScoreRanking()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ScoreRanking::Initialize()
	{
		D3DXVECTOR2 FontSize = D3DXVECTOR2(m_FontSize, m_FontSize);
		m_pFont = new Lib::Dx11::Font();
		m_pFont->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice));
		m_pFont->CreateVertexBuffer(&(FontSize));
		if (!LoadRankingData())
		{
			return false;
		}

		return true;
	}

	void ScoreRanking::Finalize()
	{
		ReleaseRankingData();
		m_pFont->ReleaseVertexBuffer();
		m_pFont->Finalize();
		SafeDelete(m_pFont);
	}

	void ScoreRanking::Update()
	{
		if (m_BasePosition.x >= 100)
		{
			m_BasePosition.x -= m_ScrollSpeed;
		}
		else
		{
			const Lib::KeyDevice::KEYSTATE* pKey =
				SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();

			if (pKey[DIK_UP] == Lib::KeyDevice::KEY_ON &&
				m_BasePosition.y > -(m_RankingNum - (1080 / (m_VerticalShift))) * m_VerticalShift)
			{
				m_BasePosition.y -= m_ScrollSpeed;
			}

			if (pKey[DIK_DOWN] == Lib::KeyDevice::KEY_ON &&
				m_BasePosition.y < 100)
			{
				m_BasePosition.y += m_ScrollSpeed;
			}
		}
	}

	void ScoreRanking::Draw()
	{
		for (int i = 0; i < m_RankingNum; i++)
		{
			D3DXVECTOR2 DrawPos = m_BasePosition;
			DrawPos.y += i * m_VerticalShift;

			char Rank[64] = { 0 };

			sprintf_s(Rank, "%d", i + 1);

			m_pFont->Draw(&DrawPos, Rank);

			char Score[64] = { 0 };

			DrawPos.x += m_ScoreShift;

			sprintf_s(Score, "%d", m_pRankingData[i].Score);
			m_pFont->Draw(&DrawPos, Score);

			DrawPos.x += m_NameShift;
			m_pFont->Draw(&DrawPos, m_pRankingData[i].Name);
		}
	}

	bool ScoreRanking::LoadRankingData()
	{
		char FileName[128] = { 0 };

		sprintf_s(FileName, "Resource\\StageSelectScene\\RankingWindow\\RankingData\\Stage%d.csv", m_StageNum);

		fopen_s(&m_pFile, FileName, "r");

		if (m_pFile == nullptr)
		{
			return false;
		}

		int CSVData;

		while ((CSVData = fgetc(m_pFile)) != EOF)
		{
			if (CSVData == '\n')
			{
				m_RankingNum++;
			}
		}

		m_pRankingData = new RANKING_DATA[m_RankingNum];

		fseek(m_pFile, 0, SEEK_SET);

		for (int i = 0; i < m_RankingNum; i++)
		{
			m_pRankingData[i].Score = 0;

			fscanf_s(m_pFile, "%d,", &m_pRankingData[i].Score);
			fscanf_s(m_pFile, "%s", &m_pRankingData[i].Name, sizeof(m_pRankingData[i].Name));
		}

		fclose(m_pFile);

		return true;
	}

	void ScoreRanking::ReleaseRankingData()
	{
		SafeDelete(m_pRankingData);
	}
}

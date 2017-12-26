/**
 * @file	Rain.cpp
 * @brief	雨ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Rain.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageGimmickManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"
#include "CollisionManager\CollisionManager.h"
#include "Debugger\DebugTimer\DebugTimer.h"
#include <algorithm>
#include <functional>
#include <random>
#include <time.h>


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const int Rain::m_GimmickMaxLow = 120;
	const int Rain::m_GimmickMaxNormal = 240;
	const int Rain::m_GimmickMaxHigh = 360;
	const float Rain::m_Gravity = 0.6f;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Rain::Rain(D3DXVECTOR2 _pos, GRADE _grade) :
		m_TextureName("Resource\\GameScene\\Texture\\Gimmick12.png"),
		m_TaskName("RainGimmick"),
		m_GimmickNum(0),
		m_RainPos(_pos),
		m_Grade(_grade),
		m_Time(0),
		m_pCollision(new RainGimmickCollision(RAIN_GIMMICK_COLLISION_ID))
	{
		m_Size = D3DXVECTOR2(6, 6);

		switch (m_Grade)
		{
		case LOW_GRADE:
			m_GimmickMax = m_GimmickMaxLow;
			break;
		case NORMAL_GRADE:
			m_GimmickMax = m_GimmickMaxNormal;
			break;
		case HIGH_GRADE:
			m_GimmickMax = m_GimmickMaxHigh;
			break;
		}
	}

	Rain::~Rain()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Rain::Initialize()
	{
		m_pUpdateTask->SetName(m_TaskName);
		m_pDrawTask->SetName(m_TaskName);

		m_pDrawTask->SetPriority(GAME_DRAW_RAIN);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		m_pMultipleVertexUV = new Lib::Dx11::MultipleVertex2DUV();
		if (!m_pMultipleVertexUV->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(1, 1)))
		{
			OutputErrorLog("頂点バッファの生成に失敗しました");
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			m_TextureName,
			&m_TextureIndex))
		{
			OutputErrorLog("テクスチャの読み込みに失敗しました");
			return false;
		}

		if (!CreateInstanceBuffer())
		{
			OutputErrorLog("インスタンスの生成に失敗しました");
			return false;
		}

		m_Positions.resize(m_GimmickMax);
		m_GimmickUV.resize(m_GimmickMax);
		m_Times.resize(m_GimmickMax);
		m_pCollision->ResizeRect(m_GimmickMax);

		for (auto itr = m_Times.begin(); itr != m_Times.end(); itr++)
		{
			(*itr) = -1;
		}

		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		return true;
	}

	void Rain::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		ReleaseInstanceBuffer();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		if (m_pMultipleVertexUV != nullptr)
		{
			m_pMultipleVertexUV->ReleaseVertexBuffer();
			m_pMultipleVertexUV->Finalize();
			SafeDelete(m_pMultipleVertexUV);
		}

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void Rain::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		///@todo 当たり判定処理.

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
		
			m_Times[Data.Id] = -1;
			m_GimmickNum--;
		}

		m_Time++;
		if (m_Time % 2 == 0)
		{
			if (m_GimmickNum != m_GimmickMax)	GenerateParticle();
		}

		for (int i = 0; i < m_GimmickMax; i++)
		{
			if (m_Times[i] != -1)
			{
				m_Times[i]++;

				float Acceleration = (m_Times[i] * m_Gravity);
				m_Positions[i].y += Acceleration < 22.f ? Acceleration : 22.f;

				GIMMICK_RECTANGLE Rect(
					m_Positions[i].x - m_Size.x / 2,
					m_Positions[i].y - m_Size.y / 2,
					m_Positions[i].x + m_Size.x / 2,
					m_Positions[i].y + m_Size.y / 2,
					i);
				(*m_pCollision->GetRect())[i] = Rect;

				if (m_Positions[i].y > 1100)
				{
					(*m_pCollision->GetRect())[i] = GIMMICK_RECTANGLE();
					m_Times[i] = -1;
					m_GimmickNum--;
				}
			}
		}
	}

	void Rain::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
	}

	
	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	bool Rain::CreateInstanceBuffer()
	{
		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickMax];
		D3DXVECTOR2* pUV = new D3DXVECTOR2[m_GimmickMax];
		for (int i = 0; i < m_GimmickMax; i++)	D3DXMatrixIdentity(&pMat[i]);
		for (int i = 0; i < m_GimmickMax; i++)	pUV[i] = D3DXVECTOR2(1, 1);
		m_pMultipleVertexUV->CreateInstanceBufferUV(pMat, pUV, m_GimmickMax);

		SafeDeleteArray(pUV);
		SafeDeleteArray(pMat);

		return true;
	}

	void Rain::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}

	void Rain::GenerateParticle()
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		float RainRange = 0.0f;
		switch (m_Grade)
		{
		case LOW_GRADE:
			RainRange = 60.f;
			break;
		case NORMAL_GRADE:
			RainRange = 155.f;
			break;
		case HIGH_GRADE:
			RainRange = 300.f;
			break;
		}

		// 粒の座標計算.
		D3DXVECTOR2 Pos(m_RainPos.x, m_RainPos.y);
		srand(unsigned int(time(nullptr) + m_Time));
		std::mt19937 RandomGenerater(static_cast<unsigned int>(rand()));
		std::uniform_real_distribution<float> Distribution(-RainRange, RainRange);
		Pos.x += Distribution(RandomGenerater);

		// ギミックの追加.
		for (int i = 0; i < m_GimmickMax; i++)
		{
			if (m_Times[i] == -1)
			{
				m_Positions[i] = Pos;
				m_GimmickUV[i] = D3DXVECTOR2(0.f, 0.f);
				m_Times[i] = 0;

				GIMMICK_RECTANGLE Rect(
					Pos.x - m_Size.x / 2,
					Pos.y - m_Size.y / 2,
					Pos.x + m_Size.x / 2,
					Pos.y + m_Size.y / 2,
					i);
				(*m_pCollision->GetRect())[i] = Rect;
				break;
			}
		}

		m_GimmickNum++;
	}
}

/**
 * @file	RainCloud.cpp
 * @brief	雨雲ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RainCloud.h"

#include "..\..\StageGimmickManager.h"
#include "CollisionManager\CollisionManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\RainChemical\RainChemicalEvent\RainChemicalEvent.h"
#include "EventManager\EventManager.h"
#include <time.h>


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const int RainCloud::m_GimmickMax = 10;
	const int RainCloud::m_InitialTime = 360;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RainCloud::RainCloud() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick11.png", "RainCloudGimmick"),
		m_pCollision(new RainCloudGimmickCollision(RAINCLOUD_GIMMICK_COLLISION_ID))
	{
	}

	RainCloud::~RainCloud()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool RainCloud::Initialize()
	{
		m_pUpdateTask->SetName(m_TaskName);
		m_pDrawTask->SetName(m_TaskName);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		m_pMultipleVertexUV = new Lib::Dx11::MultipleVertex2DUV();
		if (!m_pMultipleVertexUV->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(0.5f, 1)))
		{
			OutputErrorLog("頂点バッファの生成に失敗しました");
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			m_TextureName,
			&m_TextureIndex))
		{
			return false;
		}

		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		m_ReciveFunc = std::bind(&RainCloud::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_ReciveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(RAIN_EVENT_GROUP));

		m_Positions.resize(m_GimmickMax);
		m_GimmickUV.resize(m_GimmickMax);
		m_Times.resize(m_GimmickMax);
		m_pRains.resize(m_GimmickMax);
		m_pCollision->ResizeRect(m_GimmickMax);

		for (auto itr = m_Times.begin(); itr != m_Times.end(); itr++)
		{
			(*itr) = -1;
		}

		return true;
	}

	void RainCloud::Finalize()
	{
		for (auto itr = m_pRains.begin(); itr != m_pRains.end(); itr++)
		{
			if ((*itr) != nullptr)	(*itr)->Finalize();
			SafeDelete(*itr);
		}

		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(RAIN_EVENT_GROUP));

		SafeDelete(m_pEventListener);

		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
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

	void RainCloud::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
		}

		for (int i = 0; i < m_GimmickMax; i++)
		{
			if (m_Times[i] != -1)
			{
				m_Times[i]++;
				if (m_Times[i] > 250)
				{
					m_Times[i] = -1;
					m_Positions[i] = D3DXVECTOR2(0, 0);
					m_GimmickUV[i] = D3DXVECTOR2(0.5f, 0);
					m_pRains[i]->Finalize();
					SafeDelete(m_pRains[i]);
					(*m_pCollision->GetRect())[i] = GIMMICK_RECTANGLE();
					m_GimmickNum--;
				}
			}
		}
	}

	void RainCloud::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickMax);
	}

	void RainCloud::AddGimmick(int _x, int _y, int _data)
	{
	}

	void RainCloud::ClearChip()
	{
	}

	bool RainCloud::CreateInstanceBuffer()
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

	void RainCloud::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void RainCloud::ReciveEvent(Lib::EventBase* _pEvent)
	{
		if (_pEvent->GetEventID() != RAIN_EVENT) return;
		if (m_GimmickNum >= m_GimmickMax) return;

		RainChemicalEvent* pEvent = reinterpret_cast<RainChemicalEvent*>(_pEvent);

		int ID = -1;
		for (unsigned int i = 0; i < m_Times.size(); i++)
		{
			if (m_Times[i] == -1)
			{
				ID = i;
				break;
			}
		}

		switch (pEvent->GetChemicalGrade())
		{
		case ChemicalBase::GRADE_NORMAL:
			m_pRains[ID] = new Rain(D3DXVECTOR2(pEvent->GetRainPos().x, 300), Rain::LOW_GRADE);
			m_pRains[ID]->Initialize();
			break;
		case ChemicalBase::GRADE_GOOD:
			m_pRains[ID] = new Rain(D3DXVECTOR2(pEvent->GetRainPos().x, 300), Rain::NORMAL_GRADE);
			m_pRains[ID]->Initialize();
			break;
		case ChemicalBase::GRADE_GREAT:
			m_pRains[ID] = new Rain(D3DXVECTOR2(pEvent->GetRainPos().x, 300), Rain::HIGH_GRADE);
			m_pRains[ID]->Initialize();
			break;
		default:
			OutputErrorLog("薬品のグレードが不正です");
			return;
			break;
		}


		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos = D3DXVECTOR2(0, 300);
		Pos.x = pEvent->GetRainPos().x;

		GIMMICK_RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2,
			ID);

		// ギミックの追加.
		m_Positions[ID] = Pos;
		m_GimmickUV[ID] = D3DXVECTOR2(0.f, 0.f);
		m_Times[ID] = 0;
		(*m_pCollision->GetRect())[ID] = Rect;
		m_GimmickNum++;
	}
}

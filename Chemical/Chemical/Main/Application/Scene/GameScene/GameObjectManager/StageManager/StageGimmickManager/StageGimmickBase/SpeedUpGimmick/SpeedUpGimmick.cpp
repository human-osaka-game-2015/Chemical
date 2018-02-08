/**
 * @file	SpeedUpGimmick.cpp
 * @brief	移動速度上昇ギミッククラス実装
 * @author	kotani
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SpeedUpGimmick.h"

#include "..\..\StageGimmickManager.h"
#include "CollisionManager\CollisionManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\SpeedUpChemical\SpeedUpChemicalEvent\SpeedUpChemicalEvent.h"
#include "EventManager\EventManager.h"
#include "GameDefine.h"
#include <time.h>


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------

	const int SpeedUpGimmick::m_GimmickMax = 10;
	const int SpeedUpGimmick::m_InitialTime = 360;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	SpeedUpGimmick::SpeedUpGimmick() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Water.png", "SpeedUpGimmickGimmick"),
		m_pCollision(new SpeedUpGimmickCollision(SPEEDUP_GIMMICK_COLLISION_ID))
	{
	}

	SpeedUpGimmick::~SpeedUpGimmick()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool SpeedUpGimmick::Initialize()
	{
		m_Size = D3DXVECTOR2(60, 60);

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

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0.1, 0.1), &D3DXVECTOR2(1, 1)))
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

		m_ReciveFunc = std::bind(&SpeedUpGimmick::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_ReciveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(SPEEDUP_EVENT_GROUP));

		m_Positions.resize(m_GimmickMax);
		m_GimmickUV.resize(m_GimmickMax);
		m_Times.resize(m_GimmickMax);
		m_pCollision->ResizeRect(m_GimmickMax);
		m_pCollision->GetGrade()->resize(m_GimmickMax);
		for (auto itr = m_Times.begin(); itr != m_Times.end(); itr++)
		{
			(*itr) = -1;
		}

		for (auto itr = m_Positions.begin(); itr != m_Positions.end(); itr++)
		{
			(*itr) = D3DXVECTOR2(-100, -100);
		}

		for (auto itr = m_GimmickUV.begin(); itr != m_GimmickUV.end(); itr++)
		{
			(*itr) = D3DXVECTOR2(0, 0);
		}

		return true;
	}

	void SpeedUpGimmick::Finalize()
	{
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

	void SpeedUpGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
			if (Data.OtherId == PLAYER_COLLISION_ID)
			{
				auto pRectangles = m_pCollision->GetRect();
				for (unsigned int i = 0; i < pRectangles->size(); i++)
				{
					if ((*pRectangles)[i].ID == Data.Id)
					{
						// プレイヤーと衝突した場合ギミックを削除.
						m_Times[i] = -1;
						m_Positions[i] = D3DXVECTOR2(-100, -100);
						m_GimmickUV[i] = D3DXVECTOR2(0, 0);
						(*m_pCollision->GetRect())[i] = GIMMICK_RECTANGLE();
						m_GimmickNum--;
						break;
					}
				}
			}
		}

		for (int i = 0; i < m_GimmickMax; i++)
		{
			if (m_Times[i] != -1)
			{
				m_Times[i]++;
				if (m_Times[i] > 250)
				{
					m_Times[i] = -1;
					m_Positions[i] = D3DXVECTOR2(-100, -100);
					m_GimmickUV[i] = D3DXVECTOR2(0, 0);
					(*m_pCollision->GetRect())[i] = GIMMICK_RECTANGLE();
					m_GimmickNum--;
				}
			}
		}
	}

	void SpeedUpGimmick::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickMax);
	}

	void SpeedUpGimmick::AddGimmick(int _x, int _y, int _data)
	{
	}

	void SpeedUpGimmick::ClearChip()
	{
	}

	bool SpeedUpGimmick::CreateInstanceBuffer()
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

	void SpeedUpGimmick::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------

	void SpeedUpGimmick::ReciveEvent(Lib::EventBase* _pEvent)
	{
		if (_pEvent->GetEventID() != SPEEDUP_EVENT) return;
		if (m_GimmickNum >= m_GimmickMax) return;

		SpeedUpChemicalEvent* pEvent = reinterpret_cast<SpeedUpChemicalEvent*>(_pEvent);

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
			break;
		case ChemicalBase::GRADE_GOOD:
			break;
		case ChemicalBase::GRADE_GREAT:
			break;
		default:
			OutputErrorLog("薬品のグレードが不正です");
			return;
			break;
		}


		float X = m_Size.x;
		float Y = m_Size.y;

		D3DXVECTOR2 Pos;
		Pos.x = pEvent->GetSpeedUpPos().x;
		Pos.y = pEvent->GetSpeedUpPos().y - Y / 2;

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
		(*m_pCollision->GetGrade())[ID] = pEvent->GetChemicalGrade();
		(*m_pCollision->GetRect())[ID] = Rect;
		m_GimmickNum++;
	}
}

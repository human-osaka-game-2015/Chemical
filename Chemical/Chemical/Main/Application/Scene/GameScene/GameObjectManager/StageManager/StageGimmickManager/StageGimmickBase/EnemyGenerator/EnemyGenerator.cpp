/**
 * @file	EnemyGenerator.cpp
 * @brief	エネミー生成ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyGenerator.h"

#include "..\..\StageGimmickManager.h"
#include "CollisionManager\CollisionManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "EventManager\EventManager.h"
#include <time.h>


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyGenerator::EnemyGenerator() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick4.png", "EnemyGenerator"),
		m_pCollision(new EnemyGeneratorCollision(ENEMYGENERATOR_COLLISION_ID)),
		m_pEvent(new EnemyGeneratorEvent(ENEMY_GENERATE_EVENT))
	{
	}

	EnemyGenerator::~EnemyGenerator()
	{
		SafeDelete(m_pEvent);
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EnemyGenerator::Initialize()
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

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(0.25, 1)))
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

		return true;
	}

	void EnemyGenerator::Finalize()
	{
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

	void EnemyGenerator::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		// 衝突判定処理.
		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
		}

		// エネミー生成処理.
		for (unsigned int i = 0; i < m_Times.size(); i++)
		{
			if ((m_Positions[i] - ScreenPos).x > -100.0f &&
				(m_Positions[i] - ScreenPos).x < 1900.0f)
			{
				m_Times[i]++;
				if (m_Times[i] % 6 == 0)
				{
					if (m_GimmickUV[i].x == 0.5f)
						m_GimmickUV[i].x = 0.0f;
					else
						m_GimmickUV[i].x += 0.25f;
				}

				if (m_Times[i] > 100)
				{
					// イベントの送信.
					srand(unsigned int(time(nullptr)));
					m_pEvent->SetEnemyType(EnemyGeneratorEvent::ENEMY_TYPE(
						rand() % EnemyGeneratorEvent::ENEMY_TYPE_MAX));
					m_pEvent->SetEventPos(m_Positions[i]);
					SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
						m_pEvent,
						TO_STRING(ENEMYGENERATOR_EVENT_GROUP));

					m_Times[i] = 0;
				}
			}
		}
	}

	void EnemyGenerator::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
	}

	void EnemyGenerator::AddGimmick(int _x, int _y, int _data)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		GIMMICK_RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2,
			m_GimmickNum);

		// 初期時間はランダム.
		int Time = 0;
		srand(unsigned(time(NULL) + m_GimmickNum));
		Time = rand() % 100;

		// ギミックの追加.
		m_Positions.emplace_back(Pos);
		m_GimmickUV.emplace_back(0.f, 0.f);
		m_Times.emplace_back(Time);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;
	}

	void EnemyGenerator::ClearChip()
	{
		m_pCollision->ClearRect();
		m_Times.clear();
		m_GimmickUV.clear();
		m_Positions.clear();
	}

	bool EnemyGenerator::CreateInstanceBuffer()
	{
		// ギミックの数が0なら生成しない.
		if (!m_GimmickNum) return true;

		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickNum];
		D3DXVECTOR2* pUV = new D3DXVECTOR2[m_GimmickNum];
		for (int i = 0; i < m_GimmickNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		for (int i = 0; i < m_GimmickNum; i++)	pUV[i] = D3DXVECTOR2(1, 1);
		m_pMultipleVertexUV->CreateInstanceBufferUV(pMat, pUV, m_GimmickNum);

		SafeDeleteArray(pUV);
		SafeDeleteArray(pMat);

		m_pMultipleVertexUV->WriteInstanceBuffer(&m_Positions[0], &m_GimmickUV[0]);

		return true;
	}

	void EnemyGenerator::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}
}

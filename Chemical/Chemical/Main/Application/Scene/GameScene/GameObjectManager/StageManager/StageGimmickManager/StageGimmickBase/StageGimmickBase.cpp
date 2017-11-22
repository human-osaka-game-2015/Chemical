/**
 * @file	StageGimmickBase.cpp
 * @brief	ステージギミック基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageGimmickBase.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\StageGimmickManager.h"
#include "..\..\..\..\CollisionManager\CollisionManager.h"
#include "..\..\..\GameDataManager\GameDataManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageGimmickBase::StageGimmickBase(int _id, LPCTSTR _textureName, LPCTSTR _taskName) :
		m_pCollision(new GimmickCollision(_id)),
		m_TextureName(_textureName),
		m_TaskName(_taskName),
		m_GimmickNum(0)
	{
		m_Size = StageGimmickManager::m_DefaultGimmickSize;
	}

	StageGimmickBase::~StageGimmickBase()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageGimmickBase::Initialize()
	{
		m_pUpdateTask->SetName(m_TaskName);
		m_pDrawTask->SetName(m_TaskName);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			m_TextureName,
			&m_TextureIndex))
		{
			return false;
		}

		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		return true;
	}

	void StageGimmickBase::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void StageGimmickBase::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();

		m_pMultipleVertex->WriteConstantBuffer(-ScreenPos);
	}

	void StageGimmickBase::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}

	void StageGimmickBase::AddGimmick(int _x, int _y)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		m_GimmickNum++;	// ギミックの個数をカウント.
		m_Positions.emplace_back(Pos);
	}

	void StageGimmickBase::ClearChip()
	{
		m_Positions.clear();
	}

	bool StageGimmickBase::CreateInstanceBuffer()
	{
		// ギミックの数が0なら生成しない.
		if (!m_GimmickNum) return true;

		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickNum];
		for (int i = 0; i < m_GimmickNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		m_pMultipleVertex->CreateInstanceBuffer(pMat, m_GimmickNum);

		SafeDeleteArray(pMat);

		m_pMultipleVertex->WriteInstanceBuffer(&m_Positions[0]);

		return true;
	}

	void StageGimmickBase::ReleaseInstanceBuffer()
	{
		m_pMultipleVertex->ReleaseInstanceBuffer();
	}
}


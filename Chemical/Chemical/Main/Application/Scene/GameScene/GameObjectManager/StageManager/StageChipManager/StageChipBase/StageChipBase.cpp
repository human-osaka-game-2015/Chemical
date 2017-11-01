/**
 * @file	StageChipBase.cpp
 * @brief	ステージチップ基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageChipBase.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\CollisionManager\CollisionManager.h"
#include "..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageChipBase::StageChipBase(int _id, LPCTSTR _textureName, LPCTSTR _taskName) :
		m_pCollision(new ChipCollision(_id)),
		m_TextureName(_textureName),
		m_TaskName(_taskName)
	{
	}

	StageChipBase::~StageChipBase()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageChipBase::Initialize()
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

	void StageChipBase::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void StageChipBase::Update()
	{
	}

	void StageChipBase::Draw()
	{
	}

	void StageChipBase::AddChip(int _x, int _y)
	{
		m_Positions.emplace_back(
			_x * StageChipManager::m_DefaultChipSize.x + StageChipManager::m_DefaultChipSize.x / 2,
			_y * StageChipManager::m_DefaultChipSize.y + StageChipManager::m_DefaultChipSize.y / 2);
	}

	void StageChipBase::ClearChip()
	{
		m_Positions.clear();
	}

	bool StageChipBase::CreateInstanceBuffer()
	{
		int Size = m_Positions.size();
		D3DXMATRIX* pMat = new D3DXMATRIX[Size];
		for (int i = 0; i < Size; i++)	D3DXMatrixIdentity(&pMat[i]);
		m_pMultipleVertex->CreateInstanceBuffer(pMat, Size);

		SafeDeleteArray(pMat);

		m_pMultipleVertex->WriteInstanceBuffer(&m_Positions[0]);

		return true;
	}

	bool StageChipBase::CreateCollision()
	{
		return true;
	}

	void StageChipBase::ReleaseInstanceBuffer()
	{
		m_pMultipleVertex->ReleaseInstanceBuffer();
	}

	void StageChipBase::ReleaseCollision()
	{
	}
}

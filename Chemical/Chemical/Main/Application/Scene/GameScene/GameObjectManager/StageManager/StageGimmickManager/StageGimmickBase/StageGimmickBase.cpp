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
#include "..\..\..\GameDataManager\GameDataManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageGimmickBase::StageGimmickBase(LPCTSTR _textureName, LPCTSTR _taskName) :
		m_TextureName(_textureName),
		m_TaskName(_taskName),
		m_GimmickNum(0)
	{
		m_Size = StageGimmickManager::m_DefaultGimmickSize;
	}

	StageGimmickBase::~StageGimmickBase()
	{
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

		return true;
	}

	void StageGimmickBase::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void StageGimmickBase::Update()
	{
	}

	void StageGimmickBase::Draw()
	{
	}

	void StageGimmickBase::AddGimmick(int _x, int _y)
	{
	}

	void StageGimmickBase::ClearChip()
	{
	}

	bool StageGimmickBase::CreateInstanceBuffer()
	{
		return true;
	}

	void StageGimmickBase::ReleaseInstanceBuffer()
	{
	}
}


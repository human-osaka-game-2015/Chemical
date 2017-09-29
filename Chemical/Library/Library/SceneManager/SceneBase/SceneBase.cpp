/**
 * @file	SceneBase.cpp
 * @brief	シーンの基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SceneBase::SceneBase(int _sceneID) :
		m_State(INIT_STATE),
		m_SceneID(_sceneID)
	{
	}

	SceneBase::~SceneBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SceneBase::Initialize()
	{
		return true;
	}

	void SceneBase::Finalize()
	{
	}

	void SceneBase::Update()
	{
	}

}


/**
 * @file	EmptyGimmick.cpp
 * @brief	空ギミック実装クラス
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EmptyGimmick.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EmptyGimmick::EmptyGimmick() :
		StageGimmickBase("", "EmptyGimmick")
	{
	}

	EmptyGimmick::~EmptyGimmick()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EmptyGimmick::Initialize()
	{
		return true;
	}

	void EmptyGimmick::Finalize()
	{
	}

	void EmptyGimmick::Update()
	{
	}

	void EmptyGimmick::Draw()
	{
	}

	void EmptyGimmick::AddGimmick(int _x, int _y)
	{
	}

	void EmptyGimmick::ClearChip()
	{
	}

	bool EmptyGimmick::CreateInstanceBuffer()
	{
		return true;
	}

	void EmptyGimmick::ReleaseInstanceBuffer()
	{
	}
}

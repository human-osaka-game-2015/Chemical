/**
 * @file	EmptyChip.cpp
 * @brief	空チップクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EmptyChip.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EmptyChip::EmptyChip() :
		StageChipBase(EMPTY_COLLISION_ID, "", "EmptyChip")
	{
	}

	EmptyChip::~EmptyChip()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EmptyChip::Initialize()
	{
		return true;
	}

	void EmptyChip::Finalize()
	{
	}

	void EmptyChip::Update()
	{
	}

	void EmptyChip::Draw()
	{
	}

	void EmptyChip::AddChip(int _x, int _y)
	{
	}

	void EmptyChip::ClearChip()
	{
	}

	bool EmptyChip::CreateInstanceBuffer()
	{
		return true;
	}

	void EmptyChip::ReleaseInstanceBuffer()
	{
	}
}

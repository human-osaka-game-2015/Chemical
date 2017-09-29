/**
 * @file	ObjectBase.cpp
 * @brief	オブジェクトの基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ObjectBase::ObjectBase()
	{
	}

	ObjectBase::~ObjectBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ObjectBase::Initialize()
	{
		return true;
	}

	void ObjectBase::Finalize()
	{
	}

	void ObjectBase::UpdateStartUp()
	{
	}

	void ObjectBase::Update()
	{
	}

	void ObjectBase::DrawStartUp()
	{
	}

	void ObjectBase::Draw()
	{
	}
}


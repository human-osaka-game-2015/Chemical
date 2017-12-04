/**
 * @file	EnemyGeneratorCollision.cpp
 * @brief	エネミー生成当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyGeneratorCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyGeneratorCollision::EnemyGeneratorCollision(int _id) :
		GimmickCollision(_id)
	{
	}

	EnemyGeneratorCollision::~EnemyGeneratorCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void EnemyGeneratorCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}

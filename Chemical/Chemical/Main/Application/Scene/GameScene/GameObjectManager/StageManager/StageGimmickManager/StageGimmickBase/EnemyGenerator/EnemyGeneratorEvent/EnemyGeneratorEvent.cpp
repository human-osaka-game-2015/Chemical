/**
 * @file	EnemyGeneratorEvent.cpp
 * @brief	エネミー生成ギミックイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyGeneratorEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyGeneratorEvent::EnemyGeneratorEvent(unsigned int _eventID) : 
		EventBase(_eventID)
	{
	}

	EnemyGeneratorEvent::~EnemyGeneratorEvent()
	{
	}
}

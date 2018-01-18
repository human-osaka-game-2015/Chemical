/**
 * @file	GoalEvent.cpp
 * @brief	ゴールイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GoalEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GoalEvent::GoalEvent(unsigned int _eventID) :
		EventBase(_eventID)
	{
	}

	GoalEvent::~GoalEvent()
	{
	}
}

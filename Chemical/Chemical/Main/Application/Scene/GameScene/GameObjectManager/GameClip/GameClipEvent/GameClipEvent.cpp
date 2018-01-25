/**
 * @file	GameClipEvent.h
 * @brief	ゲームクリップイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameClipEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GameClipEvent::GameClipEvent(unsigned int _eventID) : 
		EventBase(_eventID)
	{
	}

	GameClipEvent::~GameClipEvent()
	{
	}
}

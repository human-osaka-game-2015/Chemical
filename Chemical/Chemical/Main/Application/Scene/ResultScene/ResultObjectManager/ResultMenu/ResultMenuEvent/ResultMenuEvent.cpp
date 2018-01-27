/**
 * @file	ResultMenuEvent.cpp
 * @brief	リザルトイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultMenuEvent.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultMenuEvent::ResultMenuEvent(unsigned int _eventID) : 
		EventBase(_eventID)
	{
	}

	ResultMenuEvent::~ResultMenuEvent()
	{
	}
}

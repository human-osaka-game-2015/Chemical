/**
 * @file	WarpEntranceEvent.cpp
 * @brief	ワープ入り口クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WarpEntranceEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WarpEntranceEvent::WarpEntranceEvent(int _eventID) :
		EventBase(_eventID),
		m_WarpId(0)
	{
	}

	WarpEntranceEvent::~WarpEntranceEvent()
	{
	}
}

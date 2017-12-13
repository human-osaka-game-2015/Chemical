/**
 * @file	WarpExitEvent.cpp
 * @brief	ワープ出口クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WarpExitEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WarpExitEvent::WarpExitEvent(unsigned int _eventID) : 
		EventBase(_eventID),
		m_WarpId(0)
	{
	}

	WarpExitEvent::~WarpExitEvent()
	{
	}
}

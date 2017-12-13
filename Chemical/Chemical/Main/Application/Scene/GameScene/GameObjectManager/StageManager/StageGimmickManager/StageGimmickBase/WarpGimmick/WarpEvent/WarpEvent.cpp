/**
 * @file	WarpEvent.cpp
 * @brief	ワープイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WarpEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WarpEvent::WarpEvent(unsigned int _eventID) :
		EventBase(_eventID),
		m_WarpPos(0, 0)
	{
	}

	WarpEvent::~WarpEvent()
	{
	}
}

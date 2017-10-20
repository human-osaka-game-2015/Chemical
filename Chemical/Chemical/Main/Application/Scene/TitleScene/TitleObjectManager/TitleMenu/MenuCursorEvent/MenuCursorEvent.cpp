/**
 * @file	MenuCursorEvent.cpp
 * @brief	メニューカーソルイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MenuCursorEvent.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MenuCursorEvent::MenuCursorEvent(unsigned int _eventID) : 
		EventBase(_eventID)
	{
	}

	MenuCursorEvent::~MenuCursorEvent()
	{
	}
}

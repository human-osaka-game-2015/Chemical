/**
 * @file	ButtonGimmickEvent.cpp
 * @brief	ボタンギミックイベントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ButtonGimmickEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ButtonGimmickEvent::ButtonGimmickEvent(unsigned int _eventID) : 
		EventBase(_eventID)
	{
	}

	ButtonGimmickEvent::~ButtonGimmickEvent()
	{
	}
}

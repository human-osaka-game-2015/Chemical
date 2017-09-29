/**
 * @file	EventBase.cpp
 * @brief	イベント基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EventBase::EventBase(unsigned int _eventID) : 
		m_EventID(_eventID)
	{
	}

	EventBase::~EventBase()
	{
	}
}


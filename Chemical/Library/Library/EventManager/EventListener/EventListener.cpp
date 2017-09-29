/**
 * @file	EventListener.cpp
 * @brief	イベント受信クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventListener.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	unsigned int EventListener::m_EventListenerCount = 0;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EventListener::EventListener(std::function<void(EventBase*)>* _pFunc) :
		m_EventListenerID(m_EventListenerCount),
		m_pReceiveFunc(_pFunc)
	{
		m_EventListenerCount++;	// オーバーフローは考慮しない.
	}

	EventListener::~EventListener()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void EventListener::EventMessage(EventBase* _pEvent)
	{
		(*m_pReceiveFunc)(_pEvent);
	}
}

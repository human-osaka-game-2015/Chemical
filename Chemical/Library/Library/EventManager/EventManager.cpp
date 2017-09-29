/**
 * @file	EventManager.cpp
 * @brief	イベント管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventManager.h"

#include "EventListener\EventListener.h"
#include "EventBase\EventBase.h"

#include <algorithm>


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EventManager::EventManager()
	{
#ifdef _DEBUG
		m_ConsoleWindow.Initialize(Debugger::TypeToString<EventManager>());
#endif // _DEBUG
	}

	EventManager::~EventManager()
	{
#ifdef _DEBUG
		m_ConsoleWindow.Finalize();
#endif // _DEBUG
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void EventManager::AddEventListener(EventListener* _pEventListener, LPCTSTR _groupName)
	{
		m_pEventListeners[_groupName].push_back(_pEventListener);
	}

	void EventManager::RemoveEventListener(EventListener* _pEventListener, LPCTSTR _groupName)
	{
		auto EventListener = m_pEventListeners[_groupName];

		EventListener.erase(
			std::remove(EventListener.begin(), EventListener.end(), _pEventListener),
			EventListener.end());
	}

	void EventManager::SendEventMessage(EventBase* _pEvent, LPCTSTR _groupName)
	{
#ifdef _DEBUG
		m_ConsoleWindow.Print("\n\n--------------------%s--------------------\n",
			_groupName);
		m_ConsoleWindow.Print("EventName : %s\nEventID : %d\n\n",
			Debugger::TypeToString(_pEvent),
			_pEvent->GetEventID());

		auto EventListener = m_pEventListeners[_groupName];

		for (auto itr = EventListener.begin(); itr != EventListener.end(); itr++)
		{
			(*itr)->EventMessage(_pEvent);
			m_ConsoleWindow.Print("EventListenerID - %d\n", (*itr)->GetEventListenerID());
		}
#else // _DEBUG
		auto EventListener = m_pEventListeners[_groupName];

		for (auto itr = EventListener.begin(); itr != EventListener.end(); itr++)
		{
			(*itr)->EventMessage(_pEvent);
		}
#endif // !_DEBUG	
	}
}


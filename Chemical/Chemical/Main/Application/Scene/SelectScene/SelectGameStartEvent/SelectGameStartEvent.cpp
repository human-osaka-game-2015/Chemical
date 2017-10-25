/**
 * @file   SelectGameStartEvent.cpp
 * @brief  GameStartEventクラスの実装
 * @author kotani
 */
#include "SelectGameStartEvent.h"

namespace Select
{
	GameStartEvent::GameStartEvent(unsigned _eventID) :
		EventBase(_eventID)
	{
	}

	GameStartEvent::~GameStartEvent()
	{
	}
}

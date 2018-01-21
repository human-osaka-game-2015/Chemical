/**
 * @file   CurrentSceneEvent.cpp
 * @brief  シーン遷移演出イベントクラスの実装
 * @author kotani
 */
#include "CurrentSceneEvent.h"

namespace Game
{
	CurrentSceneEvent::CurrentSceneEvent(unsigned int _eventID) :
		EventBase(_eventID)
	{
	}

	CurrentSceneEvent::~CurrentSceneEvent()
	{
	}
}

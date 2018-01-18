/**
 * @file	GoalEvent.h
 * @brief	ゴールイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_GOALEVENT_H
#define GAME_GOALEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** ゴールイベントクラス */
	class GoalEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		GoalEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~GoalEvent();

	};
}


#endif // !GAME_GOALEVENT_H

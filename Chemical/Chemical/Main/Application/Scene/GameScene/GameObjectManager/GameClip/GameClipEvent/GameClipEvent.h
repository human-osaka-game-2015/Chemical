/**
 * @file	GameClipEvent.h
 * @brief	ゲームクリップイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_GAMECLIPEVENT_H
#define GAME_GAMECLIPEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** ゲームクリップイベントクラス */
	class GameClipEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _eventID イベントID
		 */
		GameClipEvent(unsigned int _eventID);

		/*** デストラクタ */
		~GameClipEvent();

	};
}

#endif // !GAME_GAMECLIPEVENT_H

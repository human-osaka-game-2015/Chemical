/**
 * @file	RedButtonGimmickEvent.h
 * @brief	赤ボタンギミックイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_REDBUTTONGIMMICKEVENT_H
#define GAME_REDBUTTONGIMMICKEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** 赤ボタンイベントクラス */
	class RedButtonGimmickEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		RedButtonGimmickEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~RedButtonGimmickEvent();

	};
}


#endif // !GAME_REDBUTTONGIMMICKEVENT_H

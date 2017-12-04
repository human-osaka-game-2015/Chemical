/**
 * @file	ButtonGimmickEvent.h
 * @brief	ボタンギミックイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_BUTTONGIMMICKEVENT_H
#define GAME_BUTTONGIMMICKEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** ボタンイベントクラス */
	class ButtonGimmickEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		ButtonGimmickEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~ButtonGimmickEvent();

	};
}


#endif // !GAME_BUTTONGIMMICKEVENT_H

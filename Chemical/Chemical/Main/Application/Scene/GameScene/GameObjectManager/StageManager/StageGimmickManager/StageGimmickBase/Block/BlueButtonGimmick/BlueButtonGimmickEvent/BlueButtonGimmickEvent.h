/**
 * @file	BlueButtonGimmickEvent.h
 * @brief	青ボタンギミックイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_BLUEBUTTONGIMMICKEVENT_H
#define GAME_BLUEBUTTONGIMMICKEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** 青ボタンイベントクラス */
	class BlueButtonGimmickEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		BlueButtonGimmickEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~BlueButtonGimmickEvent();

	};
}


#endif // !GAME_BLUEBUTTONGIMMICKEVENT_H

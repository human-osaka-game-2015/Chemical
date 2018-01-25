/**
 * @file	TitleBackEvent.h
 * @brief	タイトルバックイベントクラス定義
 * @author	morimoto
 */
#ifndef STAFF_TITLEBACKEVENT_H
#define STAFF_TITLEBACKEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Staff
{
	/*** タイトルバックイベントクラス */
	class TitleBackEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		TitleBackEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~TitleBackEvent();

	};
}


#endif // !STAFF_TITLEBACKEVENT_H

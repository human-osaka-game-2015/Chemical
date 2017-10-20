/**
 * @file	MenuCursorEvent.h
 * @brief	メニューカーソルイベントクラス定義
 * @author	morimoto
 */
#ifndef TITLE_MENUCURSOREVENT_H
#define TITLE_MENUCURSOREVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Title
{
	/**
	 * メニューカーソルイベントクラス
	 */
	class MenuCursorEvent : public Lib::EventBase
	{
	public:
		enum EVENT_TYPE
		{
			START_BUTTON_PUSH,	//!< スタートボタンプッシュイベント.
			OPTION_BUTTON_PUSH,	//!< オプションボタンプッシュイベント.
			STAFF_BUTTON_PUSH,	//!< スタッフボタンプッシュイベント.
			END_BUTTON_PUSH,	//!< 終了ボタンプッシュイベント.
			EVENT_TYPE_MAX
		};

		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		MenuCursorEvent(unsigned int _eventID);

		/**
		 * デストラクタ
		 */
		virtual ~MenuCursorEvent();

		EVENT_TYPE GetEventType(){ return m_EventType; }
		void SetEventType(EVENT_TYPE _type){ m_EventType = _type; }

	private:
		EVENT_TYPE m_EventType;	//!< イベント種類.

	};
}


#endif // !TITLE_MENUCURSOREVENT_H

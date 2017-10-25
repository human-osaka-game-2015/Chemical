/**
 * @file   SelectGameStartEvent.h
 * @brief  GameStartEventクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_GAMESTARTEVENT_H
#define SELECT_GAMESTARTEVENT_H
#include "EventManager\EventBase\EventBase.h"

namespace Select
{
	class GameStartEvent : public Lib::EventBase
	{
	public:
		enum EVENT_TYPE
		{
			START_BUTTON_PUSH,	//!< スタートボタンプッシュイベント.
			EVENT_TYPE_MAX
		};

		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		GameStartEvent(unsigned _eventID);

		/*** デストラクタ */
		virtual ~GameStartEvent();

		/**
		 * EVENT_TYPEの取得
		 * @return EVENT_TYPE
		 */
		EVENT_TYPE GetEventType()
		{
			return m_EventType;
		}

		/**
		 * EVENT_TYPEの取得
		 * @param[in] _type セットするEVENT_TYPE
		 */
		void SetEventType(EVENT_TYPE _type)
		{
			m_EventType = _type; 
		}

	private:
		EVENT_TYPE m_EventType;

	};
}


#endif

/**
 * @file   CurrentSceneEvent.h
 * @brief  シーン遷移演出イベントクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CURRENTSCENEEVENT_H
#define GAME_CURRENTSCENEEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	class CurrentSceneEvent : public Lib::EventBase
	{
	public:
		/*** イベントの種類 */
		enum EVENT_TYPE
		{
			CLEAR_EVENT,
			OVER_EVENT
		};

		/**
		* コンストラクタ
		* @param[in] _eventID イベントのID
		*/
		CurrentSceneEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~CurrentSceneEvent();

		void SetEventType(EVENT_TYPE _event) { m_Type = _event; }
		EVENT_TYPE GetEventType() { return m_Type; }

	private:
		EVENT_TYPE m_Type;

	};
}


#endif

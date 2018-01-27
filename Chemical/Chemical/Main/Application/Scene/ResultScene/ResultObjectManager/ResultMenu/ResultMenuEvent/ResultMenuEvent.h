/**
 * @file	ResultMenuEvent.h
 * @brief	リザルトイベントクラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTMENUEVENT_H
#define RESULT_RESULTMENUEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Result
{
	/*** リザルトイベントクラス */
	class ResultMenuEvent : public Lib::EventBase
	{
	public:
		enum EVENT_TYPE
		{
			STAGESELECT_BACK_EVENT,	//!< ステージセレクトに戻るイベントID.
			RESTART_EVENT			//!< リスタートイベントID.
		};

		/**
		 * コンストラクタ 
		 * @param[in] _eventID イベントのID
		 */
		ResultMenuEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~ResultMenuEvent();

		void SetType(EVENT_TYPE _type) { m_Type = _type; }
		EVENT_TYPE GetType() { return m_Type; }

	private:
		EVENT_TYPE m_Type;

	};
}


#endif // !RESULT_RESULTMENUEVENT_H

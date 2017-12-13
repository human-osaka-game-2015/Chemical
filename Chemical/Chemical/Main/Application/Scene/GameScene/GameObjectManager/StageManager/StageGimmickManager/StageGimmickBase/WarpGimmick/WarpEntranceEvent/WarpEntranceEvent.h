/**
 * @file	WarpEntranceEvent.h
 * @brief	ワープ入り口クラス定義
 * @author	morimoto
 */
#ifndef GAME_WARPENTRANCEEVENT_H
#define GAME_WARPENTRANCEEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** ワープ入り口クラス */
	class WarpEntranceEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		WarpEntranceEvent(int _eventID);

		/*** デストラクタ */
		virtual ~WarpEntranceEvent();

		/*** IDの設定関数 */
		void SetWarpId(int _id){ m_WarpId = _id; }

		/*** IDの取得関数 */
		int GetWarpId(){ return m_WarpId; }

	private:
		int m_WarpId;	//!< イベントを受け取るワープギミックのID.

	};
}


#endif // !GAME_WARPENTRANCEEVENT_H

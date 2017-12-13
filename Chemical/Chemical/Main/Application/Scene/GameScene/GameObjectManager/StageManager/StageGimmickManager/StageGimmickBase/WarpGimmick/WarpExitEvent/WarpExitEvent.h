/**
 * @file	WarpExitEvent.h
 * @brief	ワープ出口クラス定義
 * @author	morimoto
 */
#ifndef GAME_WARPEXITEVENT_H
#define GAME_WARPEXITEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"


namespace Game
{
	/*** ワープ出口クラス */
	class WarpExitEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		WarpExitEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~WarpExitEvent();

		/*** IDの設定関数 */
		void SetWarpId(int _id){ m_WarpId = _id; }

		/*** IDの取得関数 */
		int GetWarpId(){ return m_WarpId; }

	private:
		int m_WarpId;	//!< イベントを受け取るワープギミックのID.

	};
}


#endif // !GAME_WARPEXITEVENT_H

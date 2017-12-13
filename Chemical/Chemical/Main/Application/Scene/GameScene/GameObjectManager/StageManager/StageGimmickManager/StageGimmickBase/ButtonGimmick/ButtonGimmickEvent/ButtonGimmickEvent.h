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

		/*** IDの設定関数 */
		void SetOpenGeteId(int _id){ m_OpenGateId = _id; }

		/*** IDの取得関数 */
		int GetOpenGateId(){ return m_OpenGateId; }

	private:
		int m_OpenGateId;	//!< イベントを受け取る門のID.

	};
}


#endif // !GAME_BUTTONGIMMICKEVENT_H

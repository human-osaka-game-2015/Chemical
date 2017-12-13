/**
 * @file	WarpEvent.h
 * @brief	ワープイベントクラス定義
 * @author	morimoto
 */
#ifndef GAME_WARPEVENT_H
#define GAME_WARPEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"

#include <D3DX11.h>
#include <D3DX10.h>


namespace Game
{
	/*** ワープイベントクラス */
	class WarpEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		WarpEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~WarpEvent();

		/*** ワープ座標の設定関数 */
		void SetWarpPos(D3DXVECTOR2 _pos){ m_WarpPos = _pos; }

		/*** ワープ座標の取得関数 */
		D3DXVECTOR2 GetWarpPos(){ return m_WarpPos; }

	private:
		D3DXVECTOR2 m_WarpPos;

	};
}


#endif // !GAME_WARPEVENT_H

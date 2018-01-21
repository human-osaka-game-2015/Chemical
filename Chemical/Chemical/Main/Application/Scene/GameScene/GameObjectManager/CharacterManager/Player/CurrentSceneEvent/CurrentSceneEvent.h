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
		/**
		* コンストラクタ
		* @param[in] _eventID イベントのID
		*/
		CurrentSceneEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~CurrentSceneEvent();

	};
}


#endif

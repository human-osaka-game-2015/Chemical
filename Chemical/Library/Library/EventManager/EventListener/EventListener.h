/**
 * @file	EventListener.h
 * @brief	イベント受信クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTLISTENER_H
#define LIB_EVENTLISTENER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <functional>


namespace Lib
{
	class EventBase;

	/**
	 * イベント受信クラス
	 */
	class EventListener final
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _pFunc 設定する関数ポインタオブジェクト
		 */
		EventListener(std::function<void(EventBase*)>* _pFunc);

		/**
		 * デストラクタ
		 */
		~EventListener();

		/**
		 * イベントメッセージを受け取る関数
		 * @param[in] _pEvent イベントメッセージ
		 */
		void EventMessage(EventBase* _pEvent);

		/**
		 * EventListenerのIDを取得する関数
		 * @return EventListenerのID
		 */
		unsigned int GetEventListenerID() const
		{
			return m_EventListenerID;
		}

		/**
		 * イベントの通知を受け取る関数を設定
		 * @param[in] _pFunc 設定する関数ポインタオブジェクト
		 */
		void SetReceiveFunc(std::function<void(EventBase*)>* _pFunc)
		{
			m_pReceiveFunc = _pFunc;
		}

		// 比較演算子.
		bool operator == (EventListener* _pListener)
		{
			return m_EventListenerID == _pListener->GetEventListenerID();
		}

	private:
		static unsigned int	m_EventListenerCount;	//!< リスナーオブジェクトの作成数.
		unsigned int		m_EventListenerID;		//!< リスナオブジェクトのユニークID.
		std::function<void(EventBase*)>*	m_pReceiveFunc;		//!< 受信関数ポインタオブジェクト.

	};
}


#endif // !LIB_EVENTLISTENER_H

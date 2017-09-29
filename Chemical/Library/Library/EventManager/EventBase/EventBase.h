/**
 * @file	EventBase.h
 * @brief	イベント基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTBASE_H
#define LIB_EVENTBASE_H


namespace Lib
{
	/**
	 * イベント基底クラス
	 */
	class EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		EventBase(unsigned int _eventID);

		/**
		 * デストラクタ
		 */
		virtual ~EventBase();

		/**
		 * イベントのIDを取得
		 * @return イベントID
		 */
		unsigned int GetEventID()
		{
			return m_EventID;
		}

	private:
		unsigned int m_EventID;	//!< イベントID.

	};
}


#endif // !LIB_EVENTBASE_H

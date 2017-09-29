/**
 * @file	EventManager.h
 * @brief	イベント管理基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTMANAGER_H
#define LIB_EVENTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>
#include <map>

#include "Debugger\Debugger.h"
#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	class EventBase;
	class EventListener;

	/**
	 * イベント管理基底クラス
	 * @tparam Event 通知を受けるEventクラス
	 */
	class EventManager : public SingletonBase<EventManager>
	{
	public:
		friend SingletonBase<EventManager>;

		/**
		 * EventListenerを追加する
		 * @param[in] _pEventListener 追加するEventListener
		 * @param[in] _groupName EvetListenerを追加するグループの名前
		 */
		void AddEventListener(EventListener* _pEventListener, LPCTSTR _groupName);

		/**
		 * EventListenerを削除する
		 * @param[in] _pEventListener 削除するEventListener
		 * @param[in] _groupName EvetListenerを削除するグループの名前
		 */
		void RemoveEventListener(EventListener* _pEventListener, LPCTSTR _groupName);

		/**
		 * イベントを通知する
		 * @param[in] _pEvent 通知するイベント
		 * @param[in] _groupName イベントを通知するグループ名
		 */
		void SendEventMessage(EventBase* _pEvent, LPCTSTR _groupName);

	private:
		/**
		 * LPCTSTR比較用のオブジェクト
		 */
		struct CompareStr
		{
		public:
			bool operator()(LPCTSTR _str1, LPCTSTR _str2)
			{
				return strcmp(_str1, _str2) < 0;
			}
		};

		/**
		 * コンストラクタ
		 */
		EventManager();

		/**
		 * デストラクタ
		 */
		virtual ~EventManager();


		std::map<
			LPCTSTR, 
			std::vector<EventListener*>,
			CompareStr> 
			m_pEventListeners;	//!< イベントリスナを格納するコンテナ.

#ifdef _DEBUG
		Debugger::ConsoleWindow		m_ConsoleWindow;	//!< デバッグ情報を出力するウィンドウ.
#endif // _DEBUG
	};
}


#endif // !LIB_EVENTMANAGER_H

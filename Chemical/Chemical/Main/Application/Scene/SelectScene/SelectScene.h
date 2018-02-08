/**
 * @file   SelectScene.h
 * @brief  SelectSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_SCEME_H
#define SELECT_SCEME_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager\SceneBase\SceneBase.h"

#include "Debugger\Debugger.h"
#include "DirectX11\Font\Dx11Font.h"
#include "EventManager\EventBase\EventBase.h"
#include "EventManager\EventListener\EventListener.h"

namespace Select
{
	class ObjectManager;


	/*** ステージ選択シーンクラス */
	class SelectScene : public Lib::SceneBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _sceneId シーンのID
		 */
		SelectScene(int _sceneId);
	
		/*** デストラクタ */
		virtual ~SelectScene();
	
		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();
	
		/*** 終了処理 */
		virtual void Finalize();
	
		/*** シーンの更新 */
		virtual void Update();

	private:
		/**
		 * イベント受信関数
		 * @param[in] _pEvent 受信したイベント
		 */
		void ReciveEvent(Lib::EventBase* _pEvent);

		ObjectManager*						 m_pObjectManager;
		Lib::EventListener*					 m_pEventListener;
		std::function<void(Lib::EventBase*)> m_pReciveFunc;
		int									m_MainSoundIndex;

	};
}

#endif

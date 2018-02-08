/**
 * @file	TitleMenu.h
 * @brief	タイトルメニュークラス定義
 * @author	morimoto
 */
#ifndef TITLE_MENU_H
#define TITLE_MENU_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"


namespace Title
{
	class MenuButtonBase;
	class MenuCursorEvent;

	/*** タイトルメニュークラス */
	class Menu : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		Menu();

		/*** デストラクタ */
		virtual ~Menu();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		static const int m_ItemMax = 4;	//!< メニューのアイテム数.

		/*** メニューを上方向に移動 */
		void MenuUp();
		
		/*** メニューを下方向に移動 */
		void MenuDown();

		Lib::UpdateTask* m_pUpdateTask;				//!< 更新タスクオブジェクト.
		Lib::Draw2DTask* m_pDrawTask;				//!< 描画タスクオブジェクト.
		MenuCursorEvent* m_pEvent;					//!< メニュー内UIイベント.
		MenuButtonBase* m_pMenuButtons[m_ItemMax];	//!< メニュー内ボタン.

		bool m_IsMenuUp;		//!< メニュー上昇フラグ.
		bool m_IsUp;			//!< 上昇フラグ.
		bool m_IsMenuDown;		//!< メニュー降下フラグ.
		bool m_IsDown;			//!< 降下フラグ.

		int m_SelectSEIndex;
		int m_EnterSEIndex;

	};
}


#endif // !TITLE_MENU_H

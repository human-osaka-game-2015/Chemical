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

	/**
	 * タイトルメニュークラス
	 */
	class Menu : public Lib::ObjectBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		Menu();

		/**
		 * デストラクタ
		 */
		virtual ~Menu();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

		/**
		 * オブジェクトの更新
		 */
		virtual void Update();

		/**
		 * オブジェクトの描画
		 */
		virtual void Draw();

	private:
		static const int m_ItemMax = 4;	//!< メニューのアイテム数.

		/**
		 * メニューを上方向に移動
		 */
		void MenuUp();
		
		/**
		 * メニューを下方向に移動
		 */
		void MenuDown();


		Lib::UpdateTask* m_pUpdateTask;
		Lib::Draw2DTask* m_pDrawTask;
		MenuCursorEvent* m_pEvent;

		MenuButtonBase* m_pMenuButtons[m_ItemMax];

		bool m_IsMenuUp;
		bool m_IsUp;
		bool m_IsMenuDown;
		bool m_IsDown;


	};
}


#endif // !TITLE_MENU_H

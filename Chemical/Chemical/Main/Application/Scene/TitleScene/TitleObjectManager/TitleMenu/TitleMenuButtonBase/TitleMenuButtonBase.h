/**
 * @file	TitleMenuButtonBase.h
 * @brief	タイトルメニューボタン既定クラス定義
 * @author	morimoto
 */
#ifndef TITLE_MENUBUTTONBASE_H
#define TITLE_MENUBUTTONBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"
#include "..\MenuCursorEvent\MenuCursorEvent.h"


namespace Title
{
	/**
	 * タイトルメニューアイテム既定クラス
	 */
	class MenuButtonBase : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		MenuButtonBase();

		/**
		 * デストラクタ
		 */
		virtual ~MenuButtonBase();

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

		/**
		 * 上方に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveUp();

		/**
		 * 下方向に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveDown();

		/**
		 * 左側に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveLeft();

		/**
		 * 右側に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveRight();

		/**
		 * 左中央に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveLeftCenter();

		/**
		 * 右中央に移動する
		 * @return 移動が終了したらtrue
		 */
		bool MoveRightCenter();

		/**
		 * アイテムが持つイベントIDを取得
		 * @return イベントID
		 */
		virtual MenuCursorEvent::EVENT_TYPE GetID() = 0;

	private:
		static const float m_MoveSpeed;			//!< アイテムの移動速度.
		static const float m_UpPos;				//!< 上移動する際の目的座標.
		static const float m_DownPos;			//!< 下移動する際の目的座標.
		static const float m_LeftPos;			//!< 左移動する際の目的座標.
		static const float m_RightPos;			//!< 右移動する際の目的座標.
		static const float m_LeftCenterPos;		//!< 左中央移動する際の目的座標.
		static const float m_RightCenterPos;	//!< 右中央移動する際の目的座標.

	};
}


#endif // !TITLE_MENUBUTTONBASE_H

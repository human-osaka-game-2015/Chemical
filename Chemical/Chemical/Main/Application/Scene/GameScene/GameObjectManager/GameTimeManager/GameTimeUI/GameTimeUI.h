/**
 * @file	GameTimeUI.h
 * @brief	ゲームタイムUIクラス定義
 * @author	morimoto
 */
#ifndef GAME_TIMEUI_H
#define GAME_TIMEUI_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"

#include "DirectX11\Font\Dx11Font.h"


namespace Game
{
	/*** ゲームタイムUIクラス */
	class TimeUI : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		TimeUI();

		/*** デストラクタ */
		virtual ~TimeUI();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * フレームの設定
		 * @param[in] _frame 設定するフレーム
		 */
		void SetFrame(int _frame) { m_Frame = _frame; }

		/**
		 * 時間(秒)設定
		 * @param[in] _minute 設定する時間(秒)
		 */
		void SetSeconds(int _seconds) { m_Seconds = _seconds; }

		/**
		 * 時間(分)の設定
		 * @param[in] _minute 設定する時間(分)
		 */
		void SetMinute(int _minute) { m_Minute = _minute; }

	private:
		static const D3DXVECTOR2 m_DefaultPos;
		static const D3DXVECTOR2 m_DefaultSize;

		Lib::Dx11::Font* m_pFont;

		int m_Frame;
		int m_Seconds;
		int m_Minute;

	};
}

#endif // !GAME_TIMEUI_H

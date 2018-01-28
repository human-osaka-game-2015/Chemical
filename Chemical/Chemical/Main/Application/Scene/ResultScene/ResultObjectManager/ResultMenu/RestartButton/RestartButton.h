/**
 * @file	RestartButton.h
 * @brief	リスタートボタンクラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESTARTBUTTON_H
#define RESULT_RESTARTBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Result
{
	/*** リスタートボタンクラス */
	class RestartButton : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		RestartButton();

		/*** デストラクタ */
		virtual ~RestartButton();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

		void SetIsSelected(bool _select) { m_IsSelect = _select; }
		bool GetIsSelected() { return m_IsSelect; }

	private:
		bool	m_IsSelect;

	};
}


#endif // !RESULT_RESTARTBUTTON_H

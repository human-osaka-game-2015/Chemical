/**
 * @file	BackButton.h
 * @brief	バックボタンクラス定義
 * @author	morimoto
 */
#ifndef RESULT_BACKBUTTON_H
#define RESULT_BACKBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Result
{
	/*** バックボタンクラス */
	class BackButton : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		BackButton();

		/*** デストラクタ */
		virtual ~BackButton();

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
		int		m_TextureIndex2;
		bool	m_IsSelect;

	};
}


#endif // !RESULT_BACKBUTTON_H

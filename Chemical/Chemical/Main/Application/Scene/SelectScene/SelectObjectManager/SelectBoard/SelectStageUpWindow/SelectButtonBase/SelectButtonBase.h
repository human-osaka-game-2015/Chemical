/**
 * @file   SelectButtonBase.h
 * @brief  ButtonBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_BUTTONBASE_H
#define SELECT_BUTTONBASE_H
#include "Object2DBase\Object2DBase.h"

namespace Select
{
	class ButtonBase : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		ButtonBase();

		/*** デストラクタ */
		virtual ~ButtonBase();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize(){ return true; }

		/*** 終了処理 */
		virtual void Finalize(){}

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw(float _alpha);

		/*** 選択された */
		virtual void OnClick() = 0;

		/*** ボタンの上に乗っている */
		void OnCusor()
		{
			m_OnCursor = true;
		}

	private:
		bool		m_OnCursor;
		D3DXVECTOR2 m_OnCursorSize;
		D3DXVECTOR2 m_DefaultSize;

	};
}


#endif

/**
 * @file   SelectReturnButton.h
 * @brief  ReturnButtonクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_RETURN_BUTTON_H
#define SELECT_RETURN_BUTTON_H
#include "../SelectButtonBase.h"

namespace Select
{ 
	class ReturnButton : public ButtonBase
	{
	public:
		/*** コンストラクタ */
		ReturnButton();

		/*** デストラクタ */
		virtual ~ReturnButton();

		/*** 初期化処理 */
		virtual bool Initialize();

		/*** 解放処理 */
		virtual void Finalize();

		/*** 選択された */
		virtual void OnClick();

	};
}


#endif

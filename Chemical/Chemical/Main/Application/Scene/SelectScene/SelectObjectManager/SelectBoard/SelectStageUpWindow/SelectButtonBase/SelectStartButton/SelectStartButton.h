/**
 * @file   SelectStartButton.h
 * @brief  StartButtonクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_START_BUTTON_H
#define SELECT_START_BUTTON_H
#include "../SelectButtonBase.h"

namespace Select
{
	class StartButton : public ButtonBase
	{
	public:
		/*** コンストラクタ */
		StartButton(int _stageNum);
		
		/*** デストラクタ */
		virtual ~StartButton();

		/*** 初期化処理 */
		virtual bool Initialize();

		/*** 解放処理 */
		virtual void Finalize();

		/*** 選択された */
		virtual void OnClick();

	private:
		const int m_StageNum;

	};
}


#endif

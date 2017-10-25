/**
 * @file   SelectRankingButton.h
 * @brief  RankingButtonクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_RANKING_BUTTON_H
#define SELECT_RANKING_BUTTON_H
#include "../SelectButtonBase.h"

namespace Select
{
	class RankingButton : public ButtonBase
	{
	public:
		/*** コンストラクタ */
		RankingButton();

		/*** デストラクタ */
		virtual ~RankingButton();

		/*** 初期化処理 */
		virtual bool Initialize();

		/*** 解放処理 */
		virtual void Finalize();

		/*** 選択された */
		virtual void OnClick();

	};
}


#endif

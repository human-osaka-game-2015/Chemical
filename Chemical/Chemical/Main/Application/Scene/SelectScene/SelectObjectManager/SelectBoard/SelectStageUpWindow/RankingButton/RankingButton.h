/**
 * @file   RankingButton.h
 * @brief  RankingReturnButtonクラスのヘッダファイル
 * @author fujioka
 */
#ifndef SELECT_RANKINGBUTTON_H
#define SELECT_RANKINGBUTTON_H

#include "Object2DBase\Object2DBase.h"

namespace Select
{
	class RankingReturnButton : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		RankingReturnButton();

		/*** デストラクタ */
		virtual ~RankingReturnButton();

		/**
		 * 初期化処理
		 * @return 成功すればtrue
		 */
		virtual bool Initialize();

		/*** 解放処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

	};
}

#endif

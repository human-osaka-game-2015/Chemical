/**
 * @file   RankingWindow.h
 * @brief  RankingWindowクラスのヘッダファイル
 * @author fujioka
 */
#ifndef SELECT_RANKINGWINDOW_H
#define SELECT_RANKINGWINDOW_H

#include "Object2DBase\Object2DBase.h"

namespace Select
{
	class RankingWindow: public Object2DBase
	{
	public:
		/*** コンストラクタ */
		RankingWindow();

		/*** デストラクタ */
		virtual ~RankingWindow();

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

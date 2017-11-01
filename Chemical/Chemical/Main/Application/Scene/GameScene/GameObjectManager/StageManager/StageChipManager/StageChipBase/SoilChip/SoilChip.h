/**
 * @file	SoilChip.h
 * @brief	土チップクラス定義
 * @author	morimoto
 */
#ifndef GAME_SOILCHIP_H
#define GAME_SOILCHIP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageChipBase.h"


namespace Game
{
	/*** 土チップクラス */
	class SoilChip : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		SoilChip();

		/*** デストラクタ */
		virtual ~SoilChip();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	};
}


#endif // !GAME_SOILCHIP_H

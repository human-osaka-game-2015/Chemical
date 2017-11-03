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
#include "..\..\StageChipBase.h"


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

	};
}


#endif // !GAME_SOILCHIP_H

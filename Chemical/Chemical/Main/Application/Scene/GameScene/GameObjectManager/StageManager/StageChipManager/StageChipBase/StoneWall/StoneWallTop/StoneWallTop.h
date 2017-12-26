/**
 * @file	StoneWallTop.h
 * @brief	石壁の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_STONEWALLTOP_H
#define GAME_STONEWALLTOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 石壁の上部クラス */
	class StoneWallTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		StoneWallTop();

		/*** デストラクタ */
		virtual ~StoneWallTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_STONEWALLTOP_H

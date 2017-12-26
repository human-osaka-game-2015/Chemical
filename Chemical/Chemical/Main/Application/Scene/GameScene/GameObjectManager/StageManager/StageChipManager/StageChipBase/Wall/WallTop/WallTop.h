/**
 * @file	WallTop.h
 * @brief	塔壁の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_WALLTOP_H
#define GAME_WALLTOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 塔壁の上部クラス */
	class WallTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		WallTop();

		/*** デストラクタ */
		virtual ~WallTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_WALLTOP_H

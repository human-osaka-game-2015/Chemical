/**
 * @file	SeaTop.h
 * @brief	水中ブロックの上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_SEATOP_H
#define GAME_SEATOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 水中ブロックの上部クラス */
	class SeaTop : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		SeaTop();

		/*** デストラクタ */
		virtual ~SeaTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_SEATOP_H

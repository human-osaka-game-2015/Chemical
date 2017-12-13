/**
 * @file	RockTop.h
 * @brief	岩場の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_ROCKTOP_H
#define GAME_ROCKTOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 岩場の上部クラス */
	class RockTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		RockTop();

		/*** デストラクタ */
		virtual ~RockTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_ROCKTOP_H

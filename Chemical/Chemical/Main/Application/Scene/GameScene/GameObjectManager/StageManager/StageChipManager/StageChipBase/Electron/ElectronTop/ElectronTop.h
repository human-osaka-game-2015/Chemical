/**
 * @file	ElectronTop.h
 * @brief	電子壁の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_ELECTRONTOP_H
#define GAME_ELECTRONTOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 電子壁の上部クラス */
	class ElectronTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		ElectronTop();

		/*** デストラクタ */
		virtual ~ElectronTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_ELECTRONTOP_H

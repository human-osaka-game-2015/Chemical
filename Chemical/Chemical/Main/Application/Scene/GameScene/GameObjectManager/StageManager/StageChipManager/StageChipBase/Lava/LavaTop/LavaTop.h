/**
 * @file	LavaTop.h
 * @brief	溶岩の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_LAVATOP_H
#define GAME_LAVATOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 溶岩の上部クラス */
	class LavaTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		LavaTop();

		/*** デストラクタ */
		virtual ~LavaTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_LAVATOP_H

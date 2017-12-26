/**
 * @file	CaveTop.h
 * @brief	洞窟壁の上部クラス定義
 * @author	morimoto
 */
#ifndef GAME_CAVETOP_H
#define GAME_CAVETOP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 洞窟壁の上部クラス */
	class CaveTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		CaveTop();

		/*** デストラクタ */
		virtual ~CaveTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_CAVETOP_H

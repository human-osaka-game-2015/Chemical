/**
 * @file	WallBottom.h
 * @brief	塔壁の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_WALLBOTTOM_H
#define GAME_WALLBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 塔壁の下部クラス */
	class WallBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		WallBottom();

		/*** デストラクタ */
		virtual ~WallBottom();

		/**
		 * チップの追加
		 * @param[in] _x 追加するチップのx位置
		 * @param[in] _y 追加するチップのy位置
		 */
		virtual void AddChip(int _x, int _y);

		/*** チップのクリア */
		virtual void ClearChip();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_WALLBOTTOM_H

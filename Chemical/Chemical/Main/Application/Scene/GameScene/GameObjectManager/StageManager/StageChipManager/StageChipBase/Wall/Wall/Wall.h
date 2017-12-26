/**
 * @file	Wall.h
 * @brief	塔壁クラス定義
 * @author	morimoto
 */
#ifndef GAME_WALL_H
#define GAME_WALL_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 塔壁クラス */
	class Wall : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Wall();

		/*** デストラクタ */
		virtual ~Wall();

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


#endif // !GAME_WALL_H

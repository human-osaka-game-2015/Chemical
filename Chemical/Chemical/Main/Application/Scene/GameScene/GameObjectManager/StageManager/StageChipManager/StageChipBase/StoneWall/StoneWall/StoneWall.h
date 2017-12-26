/**
 * @file	StoneWall.h
 * @brief	石壁クラス定義
 * @author	morimoto
 */
#ifndef GAME_STONEWALL_H
#define GAME_STONEWALL_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 石壁クラス */
	class StoneWall : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		StoneWall();

		/*** デストラクタ */
		virtual ~StoneWall();

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


#endif // !GAME_STONEWALL_H

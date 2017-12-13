/**
 * @file	Lava.h
 * @brief	溶岩クラス定義
 * @author	morimoto
 */
#ifndef GAME_LAVA_H
#define GAME_LAVA_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 溶岩クラス */
	class Lava : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Lava();

		/*** デストラクタ */
		virtual ~Lava();

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


#endif // !GAME_LAVA_H

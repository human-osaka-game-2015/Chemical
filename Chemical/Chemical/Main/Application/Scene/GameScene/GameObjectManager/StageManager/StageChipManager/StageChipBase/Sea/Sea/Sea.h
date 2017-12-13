/**
 * @file	Sea.h
 * @brief	水ブロッククラス定義
 * @author	morimoto
 */
#ifndef GAME_SEA_H
#define GAME_SEA_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 水ブロッククラス */
	class Sea : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		Sea();

		/*** デストラクタ */
		virtual ~Sea();

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


#endif // !GAME_SEA_H

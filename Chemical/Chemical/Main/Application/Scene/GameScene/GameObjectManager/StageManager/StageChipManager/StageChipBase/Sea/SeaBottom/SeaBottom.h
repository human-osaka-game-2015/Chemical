/**
 * @file	SeaBottom.h
 * @brief	水中ブロックの下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_SEABOTTOM_H
#define GAME_SEABOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 水中ブロックの下部クラス */
	class SeaBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		SeaBottom();

		/*** デストラクタ */
		virtual ~SeaBottom();

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


#endif // GAME_SEABOTTOM_H

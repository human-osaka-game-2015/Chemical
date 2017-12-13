/**
 * @file	RockBottom.h
 * @brief	岩場の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_ROCKBOTTOM_H
#define GAME_ROCKBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 岩場の下部クラス */
	class RockBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		RockBottom();

		/*** デストラクタ */
		virtual ~RockBottom();

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


#endif // !GAME_ROCKBOTTOM_H

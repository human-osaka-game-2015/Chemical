/**
 * @file	StoneWallBottom.h
 * @brief	石壁の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_STONEWALLBOTTOM_H
#define GAME_STONEWALLBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 石壁の下部クラス */
	class StoneWallBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		StoneWallBottom();

		/*** デストラクタ */
		virtual ~StoneWallBottom();

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


#endif // !GAME_STONEWALLBOTTOM_H

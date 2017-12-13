/**
 * @file	LavaBottom.h
 * @brief	溶岩の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_LAVABOTTOM_H
#define GAME_LAVABOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 溶岩の下部クラス */
	class LavaBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		LavaBottom();

		/*** デストラクタ */
		virtual ~LavaBottom();

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


#endif // !GAME_LAVABOTTOM_H

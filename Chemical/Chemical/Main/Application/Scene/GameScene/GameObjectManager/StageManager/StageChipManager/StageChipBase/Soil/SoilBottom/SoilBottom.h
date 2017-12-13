/**
 * @file	SoilBottom.h
 * @brief	土の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_SOILBOTTOM_H
#define GAME_SOILBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 土の下部クラス */
	class SoilBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		SoilBottom();

		/*** デストラクタ */
		virtual ~SoilBottom();

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


#endif // !GAME_SOILBOTTOM_H

/**
 * @file	ElectronBottom.h
 * @brief	電子壁の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_ELECTRONBOTTOM_H
#define GAME_ELECTRONBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 電子壁の下部クラス */
	class ElectronBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		ElectronBottom();

		/*** デストラクタ */
		virtual ~ElectronBottom();

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


#endif // !GAME_ELECTRONBOTTOM_H

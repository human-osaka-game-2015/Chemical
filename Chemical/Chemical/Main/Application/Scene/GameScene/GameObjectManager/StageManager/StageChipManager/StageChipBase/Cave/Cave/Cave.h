/**
 * @file	Cave.h
 * @brief	洞窟壁クラス定義
 * @author	morimoto
 */
#ifndef GAME_CAVE_H
#define GAME_CAVE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 洞窟壁クラス */
	class Cave : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Cave();

		/*** デストラクタ */
		virtual ~Cave();

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


#endif // !GAME_CAVE_H

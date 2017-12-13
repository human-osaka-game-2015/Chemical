/**
 * @file	Rock.h
 * @brief	岩場クラス定義
 * @author	morimoto
 */
#ifndef GAME_ROCK_H
#define GAME_ROCK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 岩場クラス */
	class Rock : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Rock();

		/*** デストラクタ */
		virtual ~Rock();

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


#endif // !GAME_ROCK_H

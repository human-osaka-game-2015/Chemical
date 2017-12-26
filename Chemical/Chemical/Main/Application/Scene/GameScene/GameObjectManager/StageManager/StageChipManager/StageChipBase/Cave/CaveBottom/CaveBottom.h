/**
 * @file	CaveBottom.h
 * @brief	洞窟壁の下部クラス定義
 * @author	morimoto
 */
#ifndef GAME_CAVEBOTTOM_H
#define GAME_CAVEBOTTOM_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 洞窟壁の下部クラス */
	class CaveBottom : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		CaveBottom();

		/*** デストラクタ */
		virtual ~CaveBottom();

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


#endif // !GAME_CAVEBOTTOM_H

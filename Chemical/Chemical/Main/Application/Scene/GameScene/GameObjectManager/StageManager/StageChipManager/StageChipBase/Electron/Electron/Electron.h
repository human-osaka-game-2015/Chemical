/**
 * @file	Electron.h
 * @brief	電子壁クラス定義
 * @author	morimoto
 */
#ifndef GAME_ELECTRON_H
#define GAME_ELECTRON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 電子壁クラス */
	class Electron : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Electron();

		/*** デストラクタ */
		virtual ~Electron();

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


#endif // !GAME_ELECTRON_H

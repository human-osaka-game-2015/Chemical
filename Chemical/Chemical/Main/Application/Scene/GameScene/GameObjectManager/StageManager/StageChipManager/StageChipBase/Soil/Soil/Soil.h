/**
 * @file	Soil.h
 * @brief	土クラス定義
 * @author	morimoto
 */
#ifndef GAME_SOIL_H
#define GAME_SOIL_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 土クラス */
	class Soil : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		Soil();

		/*** デストラクタ */
		virtual ~Soil();

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


#endif // !GAME_SOIL_H

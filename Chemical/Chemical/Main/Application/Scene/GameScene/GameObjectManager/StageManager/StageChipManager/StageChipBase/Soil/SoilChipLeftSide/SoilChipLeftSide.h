/**
 * @file	SoilChipLeftSide.h
 * @brief	土の左端クラス定義
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 土の左端クラス */
	class SoilChipLeftSide : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		SoilChipLeftSide();

		/*** デストラクタ */
		virtual ~SoilChipLeftSide();

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


/**
 * @file	RoadChip.h
 * @brief	道チップクラス定義
 * @author	morimoto
 */
#ifndef GAME_ROADCHIP_H
#define GAME_ROADCHIP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageChipBase.h"


namespace Game
{
	/*** 道チップクラス */
	class RoadChip : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		RoadChip();

		/*** デストラクタ */
		virtual ~RoadChip();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

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


#endif // !GAME_ROADCHIP_H

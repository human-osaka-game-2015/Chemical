/**
 * @file	FireGimmick.h
 * @brief	炎ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_FIREGIMMICK_H
#define GAME_FIREGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"


namespace Game
{
	/*** 炎ギミッククラス */
	class FireGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		FireGimmick();

		/*** デストラクタ */
		virtual ~FireGimmick();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * ギミックの追加 
		 * @param[in] _x 追加するチップのx位置
		 * @param[in] _y 追加するチップのy位置
		 */
		virtual void AddGimmick(int _x, int _y);

		/*** チップのクリア */
		virtual void ClearChip();

	private:
		using RECTANGLE = GimmickCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}


#endif // !GAME_FIREGIMMICK_H

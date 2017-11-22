/**
 * @file	EnemyGenerator.h
 * @brief	エネミー生成ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_ENEMYGENERATOR_H
#define GAME_ENEMYGENERATOR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"


namespace Game
{
	/*** エネミー生成ギミッククラス */
	class EnemyGenerator : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		EnemyGenerator();

		/*** デストラクタ */
		virtual ~EnemyGenerator();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

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


#endif // !GAME_ENEMYGENERATOR_H

/**
 * @file	EnemyUI.h
 * @brief	エネミークラス定義
 * @author	Fujioka
 */
#ifndef GAME_ENEMYUI_H
#define GAME_ENEMYUI_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

namespace Game
{

	class EnemyBase;
	/*** エネミーUIクラス */
	class EnemyUI : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		EnemyUI(EnemyBase* _pEnemyBase);

		/*** デストラクタ */
		virtual ~EnemyUI();

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

	private:
		EnemyBase* m_pEnemyBase;

		int m_MaxHealth;
		int m_OldHealth;

		int m_Frame;

		static const int m_DrawFream;

	};
}


#endif // !GAME_ENEMYUI_H

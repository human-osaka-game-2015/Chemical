/**
* @file	WalkEnemy.h
* @brief	ウォークエネミークラス定義
* @author	fujioka
*/
#ifndef GAME_WALKENEMY_H
#define GAME_WALKENEMY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Application\Scene\GameScene\GameObjectManager\CharacterManager\EnemyManager\EnemyBase\EnemyBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"

namespace Game
{
	class EnemyUI;
	/*** ウォークエネミークラス */
	class WalkEnemy : public EnemyBase
	{
	public:
		/*** コンストラクタ */
		WalkEnemy(D3DXVECTOR2* _pPosotion);

		/*** デストラクタ */
		virtual ~WalkEnemy();

		/**
		* 初期化処理
		* @return 初期化に成功したらtrue 失敗したらfalse
		*/
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの当たり判定更新*/
		virtual void CollisionTaskUpdate();

		/*** 更新処理 */
		virtual void Update();
		/*** 描画処理 */
		virtual void Draw();

	private:

		int						m_AnimationIndex;
		int						m_Frame;

		static const int		m_WalkTime;
		static const int		m_GuardTime;

		bool					m_AiEnable;
		bool					m_OldEnable;

		bool					m_IsGuard;
		Lib::Dx11::IAnimation*	m_pWalkAnimation;
		CollisionTask*			m_pCollisionTask;
		EnemyUI*				m_EnemyUI;

		void GravityUpdate();

		bool AiEnable();
		void EnemyAi();
		void DamageDecision();

	};
}


#endif

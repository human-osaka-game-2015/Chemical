/**
* @file	WalkEnemy.h
* @brief	ウォークエネミークラス定義
* @author	fujioka
*/
#ifndef GAME_THROWENEMY_H
#define GAME_THROWENEMY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "Application\Scene\GameScene\GameObjectManager\CharacterManager\EnemyManager\EnemyBase\EnemyBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"

namespace Game
{
	class EnemyUI;
	class Bullet;
	/*** ウォークエネミークラス */
	class ThrowEnemy : public EnemyBase
	{
	public:
		/*** コンストラクタ */
		ThrowEnemy(D3DXVECTOR2* _pPosotion);

		/*** デストラクタ */
		virtual ~ThrowEnemy();

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
		int						m_BulletSpeed;

		bool					m_AiEnable;
		bool					m_OldEnable;

		Lib::Dx11::IAnimation*	m_pWalkAnimation;
		CollisionTask*			m_pCollisionTask;
		EnemyUI*				m_EnemyUI;

		std::vector<Bullet*>	m_pBullets;

		void GravityUpdate();

		bool AiEnable();
		void EnemyAi();
		void DamageDecision();

	};
}


#endif

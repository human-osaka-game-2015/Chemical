/**
* @file	WalkEnemy.h
* @brief	ウォークエネミークラス定義
* @author	fujioka
*/
#ifndef GAME_FRYENEMY_H
#define GAME_FRYENEMY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Application\Scene\GameScene\GameObjectManager\CharacterManager\EnemyManager\EnemyBase\EnemyBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"

namespace Game
{
	class EnemyUI;
	/*** ウォークエネミークラス */
	class FryEnemy : public EnemyBase
	{
	public:
		/*** コンストラクタ */
		FryEnemy(D3DXVECTOR2* _pPosotion, D3DXVECTOR2* _pmplitude);

		/*** デストラクタ */
		virtual ~FryEnemy();

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
		
		bool					m_Turnaround;

		bool					m_AiEnable;
		bool					m_OldEnable;

		Lib::Dx11::IAnimation*	m_pWalkAnimation;
		CollisionTask*			m_pCollisionTask;
		EnemyUI*				m_EnemyUI;
		D3DXVECTOR2				m_Amplitude;
		D3DXVECTOR2				m_InitialPosition;

		void GravityUpdate();

		bool AiEnable();
		void EnemyAi();
		void DamageDecision();

	};
}


#endif

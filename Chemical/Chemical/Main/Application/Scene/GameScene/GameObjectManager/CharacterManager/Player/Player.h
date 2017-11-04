/**
 * @file	Player.h
 * @brief	プレイヤークラス定義
 * @author	morimoto
 */
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	class PlayerCollision;

	/*** プレイヤークラス */
	class Player : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		Player();

		/*** デストラクタ */
		virtual ~Player();

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
		static const float m_Gravity;
		static const float m_JumpPower;

		/*** 重力制御更新 */
		void GravityUpdate();

		/*** 当たり判定更新 */
		void CollisionUpdate();

		int					   m_AnimationIndex;
		Lib::Dx11::IAnimation* m_pWalkAnimation;
		PlayerCollision*	   m_pCollision;
		float				   m_Acceleration;
		bool				   m_IsLeft;
		bool				   m_IsLanding; //!< 着地しているか?

	};
}


#endif // !GAME_PLAYER_H

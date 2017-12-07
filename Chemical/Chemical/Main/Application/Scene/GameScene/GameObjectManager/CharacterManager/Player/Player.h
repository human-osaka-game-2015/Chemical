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
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"
#include <array>
#include <vector>


namespace Game
{
	class PlayerCollision;
	class PlayerUI;
	class ChemicalBase;

	/*** プレイヤークラス */
	class Player : public Object2DBase
	{
	public:
		struct PlayerState
		{
			D3DXVECTOR2 Pos;
			float Life;
			float ChemicalRemain[2];
			float MixChemicalRemain[2];
		};

		/**
		 * コンストラクタ
		 * @param[in] _worldPos プレイヤーのワールド座標
		 */
		Player(const D3DXVECTOR2& _worldPos);

		/*** デストラクタ */
		virtual ~Player();

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
		enum ANIMATION_STATE
		{
			WALK_ANIMATION,
			WAIT_ANIMATION,
			ANIMATION_MAX
		};

		struct AnimationData
		{
			Lib::Dx11::IAnimation* pData;
			int					   Index;
		};


		using AnimationArray = std::array<AnimationData, ANIMATION_MAX>;
		static const float m_Gravity;
		static const float m_JumpPower;
		static const float m_MoveSpeed;

		/**
		 * アニメーションの読み込み関数
		 * @param[in] _fileName アニメーションファイルの名前
		 * @param[in] _animationState 読み込むアニメーションのenum
		 * @return 読み込みに成功したらtrue 失敗したらfalse
		 */
		bool LoadAnimation(std::string _fileName, ANIMATION_STATE _animationState);

		/*** 重力制御更新 */
		void GravityUpdate();

		/*** 制御用関数ポインタ */
		void (Player::*pControl)();

		/*** 移動・待機時の制御関数 */
		void NormalControl();

		/*** 攻撃時制御関数 */
		void AttackControl();

		PlayerUI*				 m_pPlayerUI;
		PlayerState				 m_PlayerState;
		CollisionTask*			 m_pCollisionTask;
		PlayerCollision*	     m_pCollision;
		D3DXVECTOR2			     m_WorldPos;
		float				     m_Acceleration;
		bool				     m_IsLeft;
		bool				     m_IsLanding; //!< 着地しているか?
		ANIMATION_STATE		     m_AnimationState;
		AnimationArray			 m_Animations;
		std::vector<ChemicalBase*> m_pChemicals;

	};
}


#endif // !GAME_PLAYER_H

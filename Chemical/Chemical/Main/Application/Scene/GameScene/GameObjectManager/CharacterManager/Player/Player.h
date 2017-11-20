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


namespace Game
{
	class PlayerCollision;

	/*** プレイヤークラス */
	class Player : public Object2DBase
	{
	public:
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
			ANIMATION_MAX
		};

		struct AnimationData
		{
			Lib::Dx11::IAnimation* pData;
			int					   Index;
		};

		typedef std::array<AnimationData, ANIMATION_MAX> AnimationArray;
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

		CollisionTask*			m_pCollisionTask;
		PlayerCollision*	    m_pCollision;
		D3DXVECTOR2			    m_WorldPos;
		float				    m_Acceleration;
		bool				    m_IsLeft;
		bool				    m_IsLanding; //!< 着地しているか?
		AnimationArray		    m_Animations;
		ANIMATION_STATE		    m_AnimationState;

	};
}


#endif // !GAME_PLAYER_H

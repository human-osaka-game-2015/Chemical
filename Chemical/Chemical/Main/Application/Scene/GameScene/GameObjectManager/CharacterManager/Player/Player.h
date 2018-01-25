/**
 * @file	Player.h
 * @brief	プレイヤークラス定義
 * @author	kotani
 */
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "ChemicalFactory\ChemicalBase\ChemicalBase.h"
#include "CurrentSceneEvent\CurrentSceneEvent.h"
#include "EventManager\EventBase\EventBase.h"
#include "EventManager\EventListener\EventListener.h"

#include <array>
#include <vector>


namespace Game
{
	class PlayerCollision;
	class PlayerUIManager;

	/*** プレイヤークラス */
	class Player : public Object2DBase
	{
	public:
		struct PlayerState
		{
			D3DXVECTOR2 Pos;
			float Life;
			ChemicalBase::ChemicalData ChemicalData[2];
			ChemicalBase::ChemicalData MixChemicalData[2];
		};

		/**
		 * コンストラクタ
		 * @param[in] _worldPos プレイヤーのワールド座標
		 */
		Player(const D3DXVECTOR2& _worldPos);

		/*** デストラクタ */
		virtual ~Player(){}

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
			MIXIN_ANIMATION,
			SPRINKLE_ANIMATION,
			DOWN_ANIMATION,
			JUMP_ANIMATION,
			GOAL_ANIMATION,
			ANIMATION_MAX
		};

		struct AnimationData
		{
			Lib::Dx11::IAnimation* pData;
			int					   Index;
		};

		using AnimationArray = std::array<AnimationData, ANIMATION_MAX>;
		using ANIMATION_PATTERN = Lib::Dx11::IAnimation::ANIMATION_PATTERN;
		using EventFunction = std::function<void(Lib::EventBase*)>;

		static const float m_Gravity;
		static const float m_JumpPower;
		static const float m_MoveSpeed;
		static const float m_SpeedUpValue;
		static const int   m_MixChemicalStockMax = 2;
		// 合成する前の薬品だけなのでその分引いている.
		static const int   m_NormalChemicalMax = CHEMICAL_EMPTY - CHEMICAL_EXPLOSION;

		/*** イベントの受信関数 */
		void ReciveEvent(Lib::EventBase* _pEvent);

		/**
		 * アニメーションの初期化
		 * @return 読み込みに成功したらtrue 失敗したらfalse
		 */
		bool InitAnimatin();

		/**
		 * アニメーションファイルの読み込み
		 * @param[in] _fileName ファイル名
		 * @param[in] _animationState アニメーションのenum
		 * @param[in] _animationPattern 再生パターン
		 * @param[in] _animationSpeed 再生スピード
		 * @return 読み込みに成功したらtrue 失敗したらfalse
		 */
		bool LoadAnimationFile(
			std::string		  _fileName,
			ANIMATION_STATE   _animationState,
			ANIMATION_PATTERN _animationPattern,
			float			  _animationSpeed);

		/*** 重力制御更新 */
		void GravityUpdate();

		/**
		 * 制御用関数ポインタ 
		 * 下が使用している関数
		 */
		void (Player::*pControl)();

		/*** 移動・待機時の制御関数 */
		void NormalControl();

		/*** 薬品をかける時の制御関数 */
		void SprinkleControl();

		/*** 混ぜた薬品を生成する制御関数 */
		void ChemicalCreateControl();

		/*** 薬品を振っているときの制御関数 */
		void ShakeControl();

		/*** 攻撃を受けた時の制御関数 */
		void DamageControl();

		/*** ゴールした時の制御関数 */
		void GoalControl();

		PlayerUIManager* m_pPlayerUIManager;
		PlayerState		 m_PlayerState;
		float			 m_ChemicalStock[m_NormalChemicalMax];
		ChemicalBase*	 m_pMixChemical[m_MixChemicalStockMax];
		int				 m_SelectChemicalIndex[2];
		int				 m_SelectMixChemicalIndex;
		D3DXVECTOR2		 m_WorldPos;
		float			 m_Acceleration;
		bool			 m_IsLeft;
		bool			 m_IsLanding; //!< 着地しているか?
		D3DXVECTOR2		 m_WarpPos;

		ANIMATION_STATE	 m_AnimationState;
		AnimationArray	 m_Animations;

		CollisionTask*	 m_pCollisionTask;
		PlayerCollision* m_pCollision;

		int				 m_SpeedUpTime;

		Lib::EventListener*	m_pEventListener;
		EventFunction		m_ReciveFunc;
		CurrentSceneEvent*  m_pCurrentSceneEvent;


	};
}


#endif // !GAME_PLAYER_H

/**
 * @file   SpeedUpGimmickCollision.h
 * @brief  移動速度上昇判定クラス定義
 * @author kotani
 */
#ifndef GAME_SPEEDUPGIMMICKCOLLISION_H
#define GAME_SPEEDUPGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\ChemicalBase.h"

namespace Game
{
	/*** 回復ギミッククラス */
	class SpeedUpGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		SpeedUpGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~SpeedUpGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		std::vector<ChemicalBase::GRADE>* GetGrade() { return &m_Grade; }

	private:
		std::vector<ChemicalBase::GRADE> m_Grade;
	};
}


#endif

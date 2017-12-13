/**
 * @file   ChemicalCollision.h
 * @brief  ChemicalCollisionクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICAL_COLLISION_H
#define GAME_CHEMICAL_COLLISION_H

#include "..\RectangleCollisionBase\RectangleCollisionBase.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include <D3DX11.h>
#include <D3DX10.h>

namespace Game
{
	class ChemicalCollision : public RectangleCollisionBase
	{
	public:
		/*** コンストラクタ */
		ChemicalCollision(CHEMICAL_TYPE _chemicalType);

		/*** デストラクタ */
		virtual ~ChemicalCollision();

		/**
		* Collide関数へのDispatch関数
		* @param[in] _pOther 他オブジェクト
		*/
		virtual void Dispatch(CollisionBase* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** 当たり判定の初期化 */
		void ResetCollision()
		{
			m_IsHit = false;
		}

		/**
		 * 当たっているかのフラグを参照する
		 * @return 当たっていたらtrue 当たっていなかったらfalse
		 */
		bool GetHit()
		{
			return m_IsHit;
		}

		/**
		 * 薬品の種類を取得する
		 * @return 薬品の種類
		 */
		CHEMICAL_TYPE GetChemicalType()
		{
			return m_ChemicalType;
		}

	private:
		bool		  m_IsHit;
		CHEMICAL_TYPE m_ChemicalType;

	};
}


#endif

/**
 * @file   ExplosionCollision.h
 * @brief  爆発の当たり判定クラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_EXPLOSIONCOLLISION_H
#define GAME_EXPLOSIONCOLLISION_H

#include "..\CollisionBase.h"
#include <D3DX11.h>
#include <D3DX10.h>


namespace Game
{
	class ExplosionCollision : public CollisionBase
	{
	public:
		struct Circle
		{
			Circle(){}
			Circle(const D3DXVECTOR2& _circle, const float _radius)
			{
				Pos = _circle;
				Radius = _radius;
			}
			D3DXVECTOR2 Pos;
			float		Radius;
		};

		/*** コンストラクタ */
		ExplosionCollision();

		/*** デストラクタ */
		virtual ~ExplosionCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		void SetCircle(const Circle& _circle)
		{
			m_Circle = _circle;
		}

		Circle GetCircle()
		{
			return m_Circle;
		}

	private:
		Circle m_Circle;
	};
}


#endif

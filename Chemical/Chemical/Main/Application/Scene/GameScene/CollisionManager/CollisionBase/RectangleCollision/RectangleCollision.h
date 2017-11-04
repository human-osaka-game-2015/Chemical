/**
 * @file	RectangleCollision.h
 * @brief	矩形衝突判定オブジェクトクラス定義
 * @author	morimoto
 */
#ifndef GAME_RECTANGLECOLLISION_H
#define GAME_RECTANGLECOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\CollisionBase.h"


namespace Game
{
	/*** 矩形衝突判定オブジェクトクラス */
	class RectangleCollision : public CollisionBase
	{
	public:
		/*** 矩形データ構造体 */
		struct RECTANGLE
		{
			RECTANGLE() :
				Left(0),
				Top(0),
				Right(0),
				Bottom(0)
			{}

			RECTANGLE(float _left, float _top, float _right, float _bottom) :
				Left(_left),
				Top(_top),
				Right(_right),
				Bottom(_bottom)
			{}

			float Left;
			float Top;
			float Right;
			float Bottom;
		};

		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		RectangleCollision(int _id);

		/*** デストラクタ */
		virtual ~RectangleCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** 矩形オブジェクトとの当たり判定を行う */
		virtual void Collide(RectangleCollision* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		/**
		 * 矩形の設定
		 * @param[in] _rect 設定する矩形
		 */
		void SetRect(RECTANGLE _rect) { m_Rect = _rect; }

		/**
		 * 矩形の取得
		 * @return 矩形情報
		 */
		RECTANGLE GetRect()	{ return m_Rect; }

	private:
		RECTANGLE m_Rect;	//!< 当たり判定用矩形.

	};
}


#endif // !GAME_RECTANGLECOLLISION_H

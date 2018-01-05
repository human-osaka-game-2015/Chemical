/**
 * @file   ExplosionChemical.h
 * @brief  ExplosionChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_EXPLOSIONCHEMICAL_H
#define GAME_EXPLOSIONCHEMICAL_H
#include "..\ChemicalBase.h"
#include "CollisionManager\CollisionBase\ExplosionCollision\ExplosionCollision.h"

namespace Game
{
	class ExplosionChemical : public ChemicalBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 */
		ExplosionChemical(int _textureIndex);

		/*** デストラクタ */
		virtual ~ExplosionChemical();

		/*** オブジェクトの更新前処理 */
		virtual void UpdateStartUp();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * 薬品をかける
		 * @param[in] _pos プレイヤー座標
		 * @param[in] _isLeft プレイヤーが左を向いているか
		 */
		virtual void Sprinkle(const D3DXVECTOR2& _pos, bool _isLeft);

	private:
		using Circle = ExplosionCollision::Circle;
		enum CONTROL_STATE
		{
			NORMAL_CONTROL,
			EXPLOSION_CONTROL,
			MAX_CONTROL
		};

		/**
		 * 制御用関数ポインタ
		 * 下が使用している関数
		 */
		void (ExplosionChemical::*pControl[MAX_CONTROL])();

		void NormalControl();

		void ExplosionControl();

		int					m_ExplosionTextureIndex;
		int					m_ControlState;
		float				m_Scale;

		ExplosionCollision* m_pExplosionCollision;

	};
}


#endif

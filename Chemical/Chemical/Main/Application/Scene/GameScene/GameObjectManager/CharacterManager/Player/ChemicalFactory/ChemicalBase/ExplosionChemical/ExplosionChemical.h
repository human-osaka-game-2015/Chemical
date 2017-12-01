/**
 * @file   ExplosionChemical.h
 * @brief  ExplosionChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_EXPLOSIONCHEMICAL_H
#define GAME_EXPLOSIONCHEMICAL_H
#include "..\ChemicalBase.h"

namespace Game
{
	class ExplosionChemical : public ChemicalBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 * @param[in] _pos プレイヤーの座標
		 * @param[in] _isLeft プレイヤーの向き
		 */
		ExplosionChemical(int _textureIndex, const D3DXVECTOR2& _pos, bool _isLeft);

		/*** デストラクタ */
		virtual ~ExplosionChemical();

		/*** 更新処理 */
		virtual void Update();

	};
}


#endif

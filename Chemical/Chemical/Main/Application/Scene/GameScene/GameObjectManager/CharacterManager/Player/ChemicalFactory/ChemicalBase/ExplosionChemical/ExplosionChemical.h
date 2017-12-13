﻿/**
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
		 */
		ExplosionChemical(int _textureIndex);

		/*** デストラクタ */
		virtual ~ExplosionChemical();

		/*** 更新処理 */
		virtual void Update();

	};
}


#endif

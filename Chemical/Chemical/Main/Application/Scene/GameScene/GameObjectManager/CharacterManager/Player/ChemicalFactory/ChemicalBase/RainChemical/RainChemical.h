/**
 * @file   RainChemical.h
 * @brief  RainChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_RAINCHEMICAL_H
#define GAME_RAINCHEMICAL_H
#include "..\ChemicalBase.h"

namespace Game
{
	class RainChemical : public ChemicalBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 */
		RainChemical(int _textureIndex);

		/*** デストラクタ */
		virtual ~RainChemical();

		/*** 更新処理 */
		virtual void Update();

	};
}


#endif

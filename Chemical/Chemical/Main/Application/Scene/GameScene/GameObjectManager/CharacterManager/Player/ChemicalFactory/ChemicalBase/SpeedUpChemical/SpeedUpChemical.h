/**
 * @file   SpeedUpChemical.h
 * @brief  SpeedUpChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_MOVEUPCHEMICAL_H
#define GAME_MOVEUPCHEMICAL_H
#include "..\ChemicalBase.h"

namespace Game
{
	class SpeedUpChemical : public ChemicalBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 */
		SpeedUpChemical(int _textureIndex);

		/*** デストラクタ */
		virtual ~SpeedUpChemical();

		/*** 更新処理 */
		virtual void Update();

	};
}


#endif

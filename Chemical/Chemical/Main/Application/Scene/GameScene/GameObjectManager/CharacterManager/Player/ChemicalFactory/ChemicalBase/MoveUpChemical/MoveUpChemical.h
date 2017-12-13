/**
 * @file   MoveUpChemical.h
 * @brief  MoveUpChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_MOVEUPCHEMICAL_H
#define GAME_MOVEUPCHEMICAL_H
#include "..\ChemicalBase.h"

namespace Game
{
	class MoveUpChemical : public ChemicalBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 */
		MoveUpChemical(int _textureIndex);

		/*** デストラクタ */
		virtual ~MoveUpChemical();

		/*** 更新処理 */
		virtual void Update();

	};
}


#endif

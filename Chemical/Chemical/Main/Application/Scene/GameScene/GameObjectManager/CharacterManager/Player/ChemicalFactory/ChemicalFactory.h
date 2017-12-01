/**
 * @file   ChemicalFactory.h
 * @brief  ChemicalFactoryクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICALFACTORY_H
#define GAME_CHEMICALFACTORY_H
#include "ChemicalBase\ChemicalBase.h"

#include <unordered_map>

namespace Game
{
	class ChemicalFactory final
	{
	public:
		/*** 薬品の種類 */
		enum Type
		{
			BLUE,
			RED,
			EXPLOSION
		};

		/*** コンストラクタ */
		ChemicalFactory();

		/*** デストラクタ */
		~ChemicalFactory();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool Initialize();

		/*** 終了処理 */
		void Finalize();

		/**
		 * 2種類を混ぜた薬品を生成する
		 * @param[in] _type1 1つ目の薬品
		 * @param[in] _type2 2つ目の薬品
		 * @param[in] _pos プレイヤーの座標
		 * @param[in] _isLeft プレイヤーの向き
		 * @return 生成されたChemicalクラスのポインタ
		 */
		ChemicalBase* Create(Type _type1, Type _type2, const D3DXVECTOR2& _pos, bool _isLeft);

	private:
		std::unordered_map<Type, int> m_TextureIndex;

	};
}


#endif

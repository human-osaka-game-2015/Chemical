/**
 * @file   ChemicalFactory.h
 * @brief  ChemicalFactoryクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICALFACTORY_H
#define GAME_CHEMICALFACTORY_H
#include "ChemicalBase\ChemicalBase.h"

#include "SingletonBase\SingletonBase.h"

#include <map>
#include <algorithm>

namespace Game
{
	class ChemicalFactory
	{
	public:
		using CreateFunc = ChemicalBase* (*)(int _textureIndex);
		struct Types
		{
			Types(int _type1, int _type2)
			{
				// window.hのmix max関数と名前が衝突するので.
				Type[0] = (std::min)(_type1, _type2);
				Type[1] = (std::max)(_type1, _type2);
			}

			Types(int _type)
			{
				Type[0] = (std::min)(_type, static_cast<int>(CHEMICAL_EMPTY));
				Type[1] = (std::max)(_type, static_cast<int>(CHEMICAL_EMPTY));
			}

			bool operator == (const Types& _obj) const
			{
				return (this->Type[0] == _obj.Type[0] &&
					this->Type[1] == _obj.Type[1]);
			}

			bool operator != (const Types& _obj) const
			{
				return !(this->Type[0] == _obj.Type[0] &&
					this->Type[1] == _obj.Type[1]);
			}

			bool operator < (const Types& _obj) const
			{
				if (this->Type[0] < _obj.Type[0])
				{
					return true;
				}
				else if (this->Type[0] > _obj.Type[0])
				{
					return false;
				}

				if (this->Type[1] < _obj.Type[1])
				{
					return true;
				}
				else if (this->Type[1] > _obj.Type[1])
				{
					return false;
				}

				return false;
			}

			int Type[2];
		};

		ChemicalFactory(const ChemicalFactory&) = delete;
		ChemicalFactory& operator=(const ChemicalFactory&) = delete;
		
		static ChemicalFactory& GetInstance()
		{
			static ChemicalFactory Instance;
			return Instance;
		}

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool Initialize();

		/*** 終了処理 */
		void Finalize();

		/**
		 * 生成関数登録
		 * @param[in] _types 組み合わせ
		 * @param[in] _createFunc 生成関数
		 * @return 既に登録されていたらfalse されていなかったらtrue
		 */
		bool RegisterCreateFunc(Types _types, CreateFunc _createFunc);

		/**
		 * 生成関数削除
		 * @param[in] _types 削除する組み合わせ
		 * @return 存在する組み合わせならtrue 存在しないならfalse
		 */
		bool UnRegisterCreateFunc(Types _types);

		/**
		 * 2種類を混ぜた薬品を生成する
		 * @param[in] _types 薬品の組み合わせ
		 * @return 生成されたChemicalクラスのポインタ
		 */
		ChemicalBase* Create(Types _types);

	private:
		/*** コンストラクタ */
		ChemicalFactory(){};

		/*** デストラクタ */
		~ChemicalFactory(){};

		using CreateFuncMap = std::map<Types, CreateFunc>;

		std::map<Types, int> m_TextureIndex;
		CreateFuncMap		 m_CreateFuncs;

	};
}


#endif

/**
 * @file   ChemicalGauge.h
 * @brief  ChemicalGaugeクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICALGAUGE_H
#define GAME_CHEMICALGAUGE_H

#include "..\GaugeUIBase.h"
#include "..\..\..\Player.h"

namespace Game
{
	class ChemicalGauge : public GaugeUIBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _pPos 表示位置
		 * @param[in] _pChemicalData 薬品の情報
		 * @param[in] _pTextureIndexs 薬品のテクスチャインデックスの配列
		 */
		ChemicalGauge(const D3DXVECTOR2* _pPos,
			const ChemicalBase::ChemicalData* _pChemicalData, 
			std::array<int, CHEMICAL_EMPTY> _textureIndexs);

		/*** デストラクタ */
		virtual ~ChemicalGauge();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	private:
		const ChemicalBase::ChemicalData* m_pChemicaData;
		std::array<int, CHEMICAL_EMPTY>   m_TextureIndexs;

	};
}


#endif

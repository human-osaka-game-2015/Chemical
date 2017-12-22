/**
 * @file   RainChemical.h
 * @brief  RainChemicalクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_RAINCHEMICAL_H
#define GAME_RAINCHEMICAL_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------

#include "..\ChemicalBase.h"

#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2D.h"

namespace Game
{
	class RainChemicalEvent;

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

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

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
		int							 m_ParticleNum;
		Lib::Dx11::MultipleVertex2D* m_pMultipleVertex;
		std::vector<D3DXVECTOR2>	 m_Positions;
		std::vector<float>			 m_Accelerations;
		std::vector<float>			 m_Speeds;
		RainChemicalEvent*			 m_pRainChemicalEvent;

	};
}


#endif

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
	class SpeedUpChemicalEvent;

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

	private:
		SpeedUpChemicalEvent* m_pSpeedUpChemicalEvent;

	};
}


#endif

/**
 * @file   ChemicalBase.h
 * @brief  ChemicalBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICALBASE_H
#define GAME_CHEMICALBASE_H
#include "Object2DBase\Object2DBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\ChemicalCollision\ChemicalCollision.h"

namespace Game
{
	class ChemicalBase : public Object2DBase
	{
	public:
		/*** 薬品の等級 */
		enum GRADE
		{
			GRADE_NORMAL,
			GRADE_GOOD,
			GRADE_GREAT,
			GRADE_BAD
		};

		struct ChemicalData
		{
			CHEMICAL_TYPE Type;
			GRADE		  Grade;
			float		  Remain;
		};

		/**
		 * コンストラクタ
		 * @param[in] _textureIndex 使用するテクスチャのインデックス
		 * @param[in] _pos プレイヤー座標
		 * @param[in] _chemicalType 薬品の種類
		 */
		ChemicalBase(int _textureIndex, CHEMICAL_TYPE _chemicalType);

		/*** デストラクタ */
		virtual ~ChemicalBase();

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
		void Sprinkle(const D3DXVECTOR2& _pos, bool _isLeft);

		/**
		 * 薬品を振る
		 */
		void Shake();

		/**
		 * 当たっているかのflagを取得する 
		 * @return 当たっていたらtrue 当たっていなかったらfalse 
		 */
		bool GetIsHit()
		{
			return m_pCollision->GetHit();
		}

		/**
		 * 薬品の情報を取得する
		 * @return 種類
		 */
		ChemicalData GetChemicalData()
		{
			return m_ChemicalData;
		}

	protected:
		static const float m_Gravity;
		
		/*** 制御用関数ポインタ */
		void (ChemicalBase::*pControl)();

		Lib::UpdateStartUpTask* m_pStartUpTask;
		CollisionTask*			m_pCollisionTask;
		ChemicalCollision*		m_pCollision;
		float					m_Acceleration;
		ChemicalData			m_ChemicalData; //!< 薬品の情報
		bool					m_IsSprinkle;		//!< かけられているか?
		bool					m_IsLeft;			//!< 左に向いているか?

	private:
		int m_ShakeFrame; //!< 何フレーム振っているか?

		
	};
}


#endif

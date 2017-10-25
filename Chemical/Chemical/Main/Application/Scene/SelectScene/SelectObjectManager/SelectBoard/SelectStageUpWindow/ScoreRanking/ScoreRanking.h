/**
 * @file   ScoreRanking.h
 * @brief  ScoreRankingクラスのヘッダファイル
 * @author fujioka
 */
#ifndef SELECT_SCORERANKING_H
#define SELECT_SCORERANKING_H

#include "Object2DBase\Object2DBase.h"
#include "DirectX11\Font\Dx11Font.h"

namespace Select
{
	class ScoreRanking : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		ScoreRanking(int _stageNum);

		/*** デストラクタ */
		virtual ~ScoreRanking();

		/**
		 * 初期化処理
		 * @return 成功すればtrue
		 */
		virtual bool Initialize();

		/*** 解放処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	private:
		typedef struct RANKING_DATA
		{
			int Score;
			char Name[255];
		};

		bool LoadRankingData();
		void ReleaseRankingData();
		
		RANKING_DATA* m_pRankingData;
		FILE *m_pFile;
		D3DXVECTOR2 m_BasePosition;
		Lib::Dx11::Font* m_pFont;
		static const float m_FontSize;
		static const int m_ScoreShift;
		static const int m_NameShift;
		static const int m_VerticalShift;
		static const int m_ScrollSpeed;

		const int m_StageNum;

		int m_RankingNum;

	};
}

#endif

/**
 * @file   SelectStageUpWindow.h
 * @brief  StageUpWindowクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_STAGE_UP_WINDOW_H
#define SELECT_STAGE_UP_WINDOW_H
#include "Object2DBase\Object2DBase.h"
#include <array>

namespace Select
{
	class ButtonBase;
	class ScoreRanking;
	class RankingWindow;
	class RankingReturnButton;

	class StageUpWindow : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		StageUpWindow(int _stageNum);
		
		/*** デストラクタ */
		virtual ~StageUpWindow();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * ステージアップの表示
		 * @param[in] _isEnable 有効か?
		 */
		void SetEneble(const bool _isEnable)
		{
			m_IsEnable = _isEnable;
		}

		/**
		 * ステージアップが表示しているか?
		 * @return 表示していたらtrue
		 */
		bool GetEneble()
		{
			return m_IsEnable;
		}

	private:
		enum BUTTON_STATE
		{
			START_BUTTON,
			RANKING_BUTTON,
			RETURN_BUTTON,
			NONE_BUTTON
		};

		const int				  m_StageNum;
		bool					  m_IsEnable; //!< 有効か?
		bool					  m_IsRankingDraw;
		float					  m_Alpha;
		int						  m_ButtonState;
		std::array<ButtonBase*,3> m_pButtons;

		ScoreRanking*		 m_pScoreRanking;
		RankingWindow*		 m_pRankingWindow;
		RankingReturnButton* m_pRankingButton;
	};
}


#endif

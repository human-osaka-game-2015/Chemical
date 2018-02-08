/**
 * @file   StageSelectManager.h
 * @brief  StageSelectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_SELECT_MANAGER_H
#define STAGE_SELECT_MANAGER_H
#include "SingletonBase\SingletonBase.h"
#include <vector>

namespace Select
{
	class SelectBoard;

	class SelectManager : public Lib::SingletonBase<SelectManager>
	{
		friend Lib::SingletonBase<SelectManager>;
	public:
		enum SELECT_STATE
		{
			STAGE_BOARD_SELECT, //!< ステージボード選択
			STAGE_MENU_SELECT,  //!< ステージボードのボタン選択
			RANKING_SELECT,     //!< ランキング選択
			NONE_SELECT
		};

		bool Initialize();
		void Finalize();

		/**
		 * ステージボードを選択出来る対象に追加する
		 * @param[in] _pSelectBoard 登録するステージボード
		 */
		void AddSelectBoard(SelectBoard* _pSelectBoard);

		/*** 更新関数 */
		void Update();

		/**
		 * 選択状態をセットする
		 * @param[in] _isSelect 選択状態
		 */
		void SetSelectState(const SELECT_STATE _isSelect)
		{
			m_SelectState = _isSelect;
		}

		SELECT_STATE GetSelectState() const
		{
			return m_SelectState;
		}

		int GetSelectStageNum() const
		{
			return m_SelectStageNumber;
		}


	private:
		/*** コンストラクタ */
		SelectManager();

		/*** デストラクタ */
		virtual ~SelectManager();

		std::vector<SelectBoard*> m_pSelectBoardList;
		int						  m_SelectStageNumber; //!< 選択されているステージの番号
		SELECT_STATE			  m_SelectState;

		int m_SelectSEIndex;
		int m_EnterSEIndex;

	};
}


#endif

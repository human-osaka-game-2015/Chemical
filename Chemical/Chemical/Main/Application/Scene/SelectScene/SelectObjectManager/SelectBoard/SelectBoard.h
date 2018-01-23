/**
 * @file   SelectBoard.h
 * @brief  SelectBoardクラスのヘッダファイル
 * @author kotani
 */
#ifndef SELECT_BOARD_H
#define SELECT_BOARD_H
#include "Object2DBase\Object2DBase.h"

namespace Select
{
	class StageUpWindow;

	class SelectBoard : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _defaultPos 初期位置
		 * @param[in] _stageNum ステージの番号
 		 */
		SelectBoard(D3DXVECTOR2* _defaultPos, int _stageNum);

		/*** デストラクタ */
		virtual ~SelectBoard();
		
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

		/*** ステージが選択された */
		void Select();

		/**
		 * パネルが移動する前の座標を取得する
		 * @return パネルが移動する前の座標
		 */
		D3DXVECTOR2 GetDefaultPos() const
		{
			return m_DefaultPos;
		}

		/*** 選択アイコンが上に乗っているとき */
		void OnSelect()
		{
			m_OnSelect = true;
		}


	private:
		/*** パネル回転処理 */
		void SpinControl();

		const int			 m_StageNum;
		const D3DXVECTOR2    m_DefaultPos;
		const float		     m_SpinSpeed;
		const float			 m_MoveSpeed;
		float				 m_TargetDistance;
		float				 m_Alpha;
		int				     m_SpinCount;
		bool			     m_IsReverse;
		float				 m_MoveDistance;
		D3DXVECTOR2		     m_VertexPos[4];
		D3DXVECTOR2			 m_Scale;
		int				     m_BackTextureIndex;
		int					 m_SelectTextureIndex;
		bool			     m_OnSelect;
		bool				 m_IsSelectControl;
		StageUpWindow*       m_pStageUpWindow;

	};
}


#endif

/**
 * @file	RedButtonGimmick.h
 * @brief	赤ボタンギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_REDBUTTONGIMMICK_H
#define GAME_REDBUTTONGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\ButtonGimmickCollision\ButtonGimmickCollision.h"
#include "RedButtonGimmickEvent\RedButtonGimmickEvent.h"
#include "EventManager\EventListener\EventListener.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"


namespace Game
{
	/*** 赤ボタンギミッククラス */
	class RedButtonGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		RedButtonGimmick();

		/*** デストラクタ */
		virtual ~RedButtonGimmick();

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

		/**
		 * ギミックの追加 
		 * @param[in] _x 追加するチップのx位置
		 * @param[in] _y 追加するチップのy位置
		 * @param[in] _data ギミックに対する付加情報
		 */
		virtual void AddGimmick(int _x, int _y, int _data);

		/*** チップのクリア */
		virtual void ClearChip();

		/*** インスタンスバッファの生成 */
		virtual bool CreateInstanceBuffer();

		/*** インスタンスバッファの解放 */
		virtual void ReleaseInstanceBuffer();

	private:
		using GIMMICK_RECTANGLE = GimmickCollision::GIMMICK_RECTANGLE;

		/***
		 * イベント受信関数
		 * @param[in] _pEvent 受信したイベント
		 */
		void ReciveEvent(Lib::EventBase* _pEvent);

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		std::vector<int>					m_GimmickData;	//!< ギミックの付加情報.
		ButtonGimmickCollision*				m_pCollision;	//!< ギミックの当たり判定オブジェクト.
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;

		Lib::EventListener*						m_pEventListener;
		RedButtonGimmickEvent*					m_pEvent;
		std::function<void(Lib::EventBase*)>	m_pReciveFunc;

	};
}


#endif // !GAME_REDBUTTONGIMMICK_H


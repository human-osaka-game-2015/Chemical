/**
* @file	  SpeedUpGimmick.h
* @brief  移動速度上昇ギミッククラス定義
* @author kotani
*/
#ifndef GAME_SPEEDUPGIMMICK_H
#define GAME_SPEEDUPGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\SpeedUpGimmickCollision\SpeedUpGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"
#include "EventManager\EventListener\EventListener.h"


namespace Game
{
	/*** 雨雲ギミッククラス */
	class SpeedUpGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		SpeedUpGimmick();

		/*** デストラクタ */
		virtual ~SpeedUpGimmick();

		/*
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

		/*** イベントの受信関数 */
		void ReciveEvent(Lib::EventBase* _pEvent);

		static const int	m_GimmickMax;	//!< ギミックの最大値.
		static const int	m_InitialTime;	//!< 初期時間.

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		std::vector<int>					m_Times;		//!< ギミックの時間.
		SpeedUpGimmickCollision*			m_pCollision;	//!< ギミックの当たり判定オブジェクト.
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;

		std::function<void(Lib::EventBase*)>	m_ReciveFunc;
		Lib::EventListener*						m_pEventListener;

	};
}


#endif

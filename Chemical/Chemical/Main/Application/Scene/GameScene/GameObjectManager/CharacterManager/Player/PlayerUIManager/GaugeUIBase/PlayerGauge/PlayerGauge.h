/**
 * @file   PlayerGauge.h
 * @brief  PlayerGaugeクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_PLAYERGAUGE_H
#define GAME_PLAYERGAUGE_H

#include "..\GaugeUIBase.h"
#include "..\..\..\Player.h"

namespace Game
{
	class PlayerGauge : public GaugeUIBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _pPlayerState プレイヤーの状態
		 */
		PlayerGauge(const Player::PlayerState* _pPlayerState);
		~PlayerGauge();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

	private:
		const Player::PlayerState* m_pPlayerState;

	};
}


#endif

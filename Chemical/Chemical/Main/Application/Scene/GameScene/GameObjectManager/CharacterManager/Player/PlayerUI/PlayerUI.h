/**
 * @file	PlayerUI.h
 * @brief	プレイヤーUIクラス定義
 * @author	morimoto
 */
#ifndef GAME_PLAYERUI_H
#define GAME_PLAYERUI_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"
#include "..\Player.h"

#include <array>

namespace Game
{
	class GaugeUIBase;

	/*** プレイヤーUIクラス */
	class PlayerUI : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		PlayerUI(const Player::PlayerState* _pPlayerState);

		/*** デストラクタ */
		virtual ~PlayerUI();

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

	private:
		enum Type
		{
			CHEMICAL_GAUGE1,	 //!< 1つ目の薬品ゲージ
			CHEMICAL_GAUGE2,	 //!< 2つ目の薬品ゲージ
			MIX_CHEMICAL_GAUGE1, //!< 1つ目の混ぜた薬品ゲージ
			MIX_CHEMICAL_GAUGE2, //!< 2つ目の混ぜた薬品ゲージ
			PLAYER_GAUGE,		 //!< プレイヤーの体力ゲージ
			MAX_TYPE
		};

		std::array<GaugeUIBase*, MAX_TYPE> m_pGaugeUIs;
		const Player::PlayerState*		   m_pPlayerState;


	};
}


#endif // !GAME_PLAYERUI_H

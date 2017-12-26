/**
 * @file	PlayerUIManager.h
 * @brief	プレイヤーUIクラス定義
 * @author	kotani
 */
#ifndef GAME_PLAYER_UI_MANAGER_H
#define GAME_PLAYER_UI_MANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\Player.h"

#include <array>

namespace Game
{
	class GaugeUIBase;

	/*** プレイヤーUIクラス */
	class PlayerUIManager
	{
	public:
		/*** コンストラクタ */
		PlayerUIManager(const Player::PlayerState* _pPlayerState);

		/*** デストラクタ */
		virtual ~PlayerUIManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	private:
		enum TYPE
		{
			CHEMICAL_GAUGE1,	 //!< 1つ目の薬品ゲージ
			CHEMICAL_GAUGE2,	 //!< 2つ目の薬品ゲージ
			MIX_CHEMICAL_GAUGE1, //!< 1つ目の混ぜた薬品ゲージ
			MIX_CHEMICAL_GAUGE2, //!< 2つ目の混ぜた薬品ゲージ
			PLAYER_GAUGE,		 //!< プレイヤーの体力ゲージ
			MAX_TYPE
		};

		std::array<GaugeUIBase*, MAX_TYPE> m_pGaugeUIs;
		std::array<int, CHEMICAL_EMPTY>    m_TextureIndexs;
		const Player::PlayerState*		   m_pPlayerState;

		/**
		 * ChemicalGaugeに必要なテクスチャを全て読み込む 
		 * @return 読み込みに成功したらtrue 失敗したらfalse
		 */
		bool LoadTextures();

		/**
		* ChemicalGaugeを生成する
		* @return 初期化に成功したらtrue 失敗したらfalse
		*/
		bool CreateGaugeUIs();

	};
}


#endif // !GAME_PlayerUIManager_H

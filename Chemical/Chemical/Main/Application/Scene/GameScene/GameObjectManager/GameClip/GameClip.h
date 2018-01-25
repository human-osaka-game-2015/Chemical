#ifndef GAME_GAMECLIP_H
#define GAME_GAMECLIP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "EventManager\EventListener\EventListener.h"
#include "..\StageManager\StageGimmickManager\StageGimmickBase\Goal\GoalEvent\GoalEvent.h"
#include "GameClipEvent\GameClipEvent.h"

#include <D3D11.h>


namespace Game
{
	class GameClip : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		GameClip();

		/*** デストラクタ */
		virtual ~GameClip();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		/*** イベント受信関数 */
		void ReceiveEvent(Lib::EventBase* _pEvent);

		ID3D11Texture2D*			m_pClipTexture;
		ID3D11RenderTargetView*		m_pClipRenderTarget;
		ID3D11ShaderResourceView*	m_pClipShaderResourceView;
		ID3D11Texture2D*			m_pClipDepthStencilTexture;
		ID3D11DepthStencilView*		m_pClipDepthStencilView;
		D3D11_VIEWPORT				m_ViewPort;

		int		m_VertexShaderIndex;	//!< 頂点シェーダーインデックス.
		int		m_PixelShaderIndex;		//!< ピクセルシェーダーインデックス.
		int		m_CreateTextureVertexShaderIndex;	//!< 頂点シェーダーインデックス.
		int		m_CreateTexturePixelShaderIndex;	//!< ピクセルシェーダーインデックス.

		ID3D11SamplerState* m_pSamplerState;

		int m_TextureIndex2;

		D3DXVECTOR2 m_ClipSize;
		bool m_IsClip;
		bool m_IsFadeIn;
		
		std::function<void(Lib::EventBase*)>	m_ReceiveFunc;
		Lib::EventListener*						m_pEventListener;
		Lib::EventBase*							m_pEvent;

	};
}

#endif // GAME_GAMECLIP_H

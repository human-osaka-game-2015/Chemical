/**
 * @file   MultipleObject2DBase.h
 * @brief  MultipleObject2DBaseクラスの定義
 * @author morimoto
 */
#ifndef MULTIPLEOBJECT2DBASE_H
#define MULTIPLEOBJECT2DBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2D.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"


class MultipleObject2DBase : public Lib::ObjectBase
{
public:
	/*** コンストラクタ */
	MultipleObject2DBase();

	/*** デストラクタ */
	virtual ~MultipleObject2DBase();

	/**
	 * 初期化処理
	 * @return 初期化に成功したらtrue 失敗したらfalse
	 */
	virtual bool Initialize();

	/*** 終了処理 */
	virtual void Finalize();

	/*** オブジェクトの更新前処理 */
	virtual void UpdateStartUp();

	/*** オブジェクトの更新 */
	virtual void Update();

	/*** オブジェクトの描画前処理 */
	virtual void DrawStartUp();

	/*** オブジェクトの描画 */
	virtual void Draw();

protected:
	/**
	 * 2D描画オブジェクトの生成
	 * @return 生成に成功したらtrue 失敗したらfalse
	 */
	bool CreateVertex2D();

	/*** 2D描画オブジェクトの破棄 */
	void ReleaseVertex2D();


	Lib::Draw2DTask*	m_pDrawTask;	//!< 描画タスクオブジェクト.
	Lib::UpdateTask*	m_pUpdateTask;	//!< 更新タスクオブジェクト.

	Lib::Dx11::MultipleVertex2D*	m_pMultipleVertex;	//!< 描画オブジェクト.
	D3DXVECTOR2						m_Size;				//!< 描画サイズ.
	int								m_TextureIndex;		//!< テクスチャのインデックス.

};


#endif // MULTIPLEOBJECT2DBASE_H

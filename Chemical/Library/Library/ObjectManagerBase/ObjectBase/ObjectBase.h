/**
 * @file	ObjectBase.h
 * @brief	オブジェクトの基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_OBJECTBASE_H
#define LIB_OBJECTBASE_H


namespace Lib
{
	/**
	 * オブジェクトの基底クラス
	 */
	class ObjectBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		ObjectBase();

		/**
		 * デストラクタ
		 */
		virtual ~ObjectBase();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

		/**
		 * オブジェクトの更新前処理
		 */
		virtual void UpdateStartUp();

		/**
		 * オブジェクトの更新
		 */
		virtual void Update();

		/**
		 * オブジェクトの描画前処理
		 */
		virtual void DrawStartUp();

		/**
		 * オブジェクトの描画
		 */
		virtual void Draw();

	};
}



#endif // !LIB_OBJECTBASE_H

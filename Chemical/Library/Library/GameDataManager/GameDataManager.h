/**
 * @file	GameDataManager.h
 * @brief	ゲームデータ管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_GAMEDATAMANAGER_H
#define LIB_GAMEDATAMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <map>
#include <string>
#include <Windows.h>

#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	/**
	 * ゲームデータ管理クラス
	 * @tparam Data 管理するデータ型
	 */
	template <typename Data>
	class GameDataManager : public SingletonBase<GameDataManager<Data>>
	{
	public:
		friend SingletonBase<GameDataManager>;

		/**
		 * データの追加
		 * @param[in] _data 追加したデータの初期値
		 * @param[in] _pDataName 追加するデータの名前
		 * @return データの追加に成功したらtrue 既にデータがあればfalse
		 */
		bool AddData(Data _data, TCHAR* _pDataName);

		/**
		 * データの設定
		 * @param[in] _data セットする値
		 * @param[in] _pDataName 値をセットするデータの名前
		 * @return データセットに成功したらtrue データがなければfalse
		 */
		bool SetData(Data _data, TCHAR* _pDataName);

		/**
		 * データの取得
		 * @param[out] _pData データ内の値が出力される
		 * @param[in] _pDataName 値を取得するデータの名前
		 * @return データの取得に成功したらtrue データがなければfalse
		 */
		bool GetData(Data* _pData, TCHAR* _pDataName);

		/**
		 * データの削除
		 * @param[in] _pDataName 削除するデータの名前
		 * @return データの削除に成功したらtrue データがなければfalse
		 */
		bool RemoveData(TCHAR* _pDataName);


		/**
		 * ファイルにゲームデータを書き込む
		 * @param[in] _pSaveFilePath 書き込むファイルの名前
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool SaveGameData(LPCTSTR _pSaveFilePath);

		/**
		 * ファイルからゲームデータを読み込む
		 * @param[in] _pLoadFilePath 読み込むファイルの名前
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool LoadGameData(LPCTSTR _pLoadFilePath);

	private:
		/**
		* コンストラクタ
		*/
		GameDataManager();

		/**
		* デストラクタ
		*/
		virtual ~GameDataManager();


		FILE*							m_pSaveDataFile;	//!< セーブデータファイル.
		std::map<std::string, Data>		m_Datas;			//!< データを管理しているコンテナ.

	};
}


#include "GameDataManager_private.inl"


#endif // !LIB_GAMEDATAMANAGER_H

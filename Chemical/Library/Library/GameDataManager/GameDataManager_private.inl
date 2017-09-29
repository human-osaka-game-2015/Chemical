/**
 * @file	GameDataManager_private.inl
 * @brief	ゲームデータ管理クラス実装
 * @author	morimoto
 */
#ifndef LIB_GAMEDATAMANAGER_PRIVATE_H
#define LIB_GAMEDATAMANAGER_PRIVATE_H


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	template <typename Data>
	GameDataManager<Data>::GameDataManager() :
		m_pSaveDataFile(nullptr)
	{
	}

	template <typename Data>
	GameDataManager<Data>::~GameDataManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template <typename Data>
	bool GameDataManager<Data>::AddData(Data _data, TCHAR* _pDataName)
	{
		if (m_Datas.find(_pDataName) != m_Datas.end())
		{
			return false;	// 既にデータが設定されていたらfalseを返す.
		}

		m_Datas[_pDataName] = _data;

		return true;
	}

	template <typename Data>
	bool GameDataManager<Data>::SetData(Data _data, TCHAR* _pDataName)
	{
		if (m_Datas.find(_pDataName) == m_Datas.end())
		{
			return false;	// データが設定されていなければfalseを返す.
		}

		m_Datas[_pDataName] = _data;

		return true;
	}

	template <typename Data>
	bool GameDataManager<Data>::GetData(Data* _pData, TCHAR* _pDataName)
	{
		if (m_Datas.find(_pDataName) == m_Datas.end())
		{
			return false;	// データが設定されていなければfalseを返す.
		}

		*_pData = m_Datas[_pDataName];

		return true;
	}

	template <typename Data>
	bool GameDataManager<Data>::RemoveData(TCHAR* _pDataName)
	{
		auto itr = m_Datas.find(_pDataName);
		if (itr == m_Datas.end())
		{
			return false;	// データが設定されていなければfalseを返す.
		}

		m_Datas.erase(itr);
	}

	template <typename Data>
	bool GameDataManager<Data>::SaveGameData(LPCTSTR _pSaveFilePath)
	{
		fopen_s(&m_pSaveDataFile, _pSaveFilePath, "w");

		for (auto itr = m_Datas.begin(); itr != m_Datas.end(); itr++)
		{
			fprintf_s(m_pSaveDataFile, "%d:%s;,", itr, itr->first);
		}

		fclose(m_pSaveDataFile);

		return true;
	}

	template <typename Data>
	bool GameDataManager<Data>::LoadGameData(LPCTSTR _pLoadFilePath)
	{
		return true;
	}
}


#endif // !LIB_GAMEDATAMANAGER_PRIVATE_H

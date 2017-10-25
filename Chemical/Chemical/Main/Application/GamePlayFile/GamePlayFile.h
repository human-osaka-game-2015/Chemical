/**
 * @file   GamePlayFile.h
 * @brief  GamePlayFileクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEPLAYFILE_H
#define GAMEPLAYFILE_H
#include <stdio.h>

class GamePlayFile
{
public:
	GamePlayFile() :
		m_SelectStageNum(0)
	{}

	~GamePlayFile(){}

	/**
	 * ファイルを開く。無ければ生成する
	 * @return 成功すればtrue
	 */
	bool Open();

	/**
	 * ファイルを閉じる
	 */
	void Close();

	void SetStageNum(int _stageNum)
	{
		m_SelectStageNum = _stageNum;
	}

	int GetStageNum()
	{
		return m_SelectStageNum;
	}

	/**
	 * 設定したデータを書き込む
	 */
	void Write();

private:
	FILE*  m_pFile;
	int    m_SelectStageNum;

};


#endif

#include "score_manager.hpp"
#include <cstdio>

#include "utils.hpp"

ScoreManager::ScoreManager() : mFilePath("../score.txt")
{
	bool rbool = loadHighScoreFromFile();
	if (!rbool)
	{
		// write 0 to file if
		writeHighScoreToFile();
	}
}

ScoreManager::~ScoreManager() {}


bool ScoreManager::setHighScoreIfValid(int score)
{
	bool rbool = true;
	if (score > mHighScore)
	{
		mHighScore = score;
		rbool = writeHighScoreToFile();
	}
	return rbool;
}


bool ScoreManager::writeHighScoreToFile()
{
	FILE* fp;
	fp = fopen(mFilePath, "w");

	if (fp == NULL)
	{
		log_err("failed to open file: %s", mFilePath);
		fclose(fp);
		return false;
	}

	fprintf(fp, "%d", mHighScore);
	fclose(fp);
	return true;
}


bool ScoreManager::loadHighScoreFromFile()
{
	FILE* fp;
	int sz = 0;

	fp = fopen(mFilePath, "r");
	if (fp == NULL)
	{
		log_err("failed to open file: %s", mFilePath);
		mHighScore = 0;
		return false;
	}

	// get size of file
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if (sz == 0)
	{
		log_info("file %s is empty", mFilePath);
		mHighScore = 0;
	}
	else
	{
		if (fscanf(fp, "%d", &mHighScore) == 1)
		{
			log_info("high score from file is %d", mHighScore);
		}
		else
		{
			log_err("fscanf failed on file: %s", mFilePath);
			mHighScore = 0;
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;

}


#include "score_manager.hpp"
#include <cstdio>
#include <algorithm>

#include "utils.hpp"

ScoreManager::ScoreManager()
	: mFilePath("../score.txt")
	, mScores(1, 0)
{
	bool rbool = loadHighScoreFromFile();
	if (!rbool)
	{
		writeHighScoreToFile();
	}
}

ScoreManager::~ScoreManager() {}


int ScoreManager::getHighScore()
{
	std::sort(mScores.begin(), mScores.end());
	return mScores.back();
}

bool ScoreManager::setHighScoreIfValid(int score)
{
	bool rbool = true;
	if (score > *std::min_element(mScores.begin(), mScores.end()))
	{
		if (mScores.size() <= 10)
		{
			mScores.push_back(score);
		}
		else
		{
			std::sort(mScores.begin(), mScores.end());
			mScores[0] = score; // replace the smallest
		}
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

	// currently only writing a single (highest) score
	fprintf(fp, "%d", *std::max_element( mScores.begin(), mScores.end() ));
	fclose(fp);
	return true;
}


// loads high score from file, should only be executed in ctor
bool ScoreManager::loadHighScoreFromFile()
{
	FILE* fp;
	int sz = 0;

	fp = fopen(mFilePath, "r");
	if (fp == NULL)
	{
		log_err("failed to open file: %s, it may not exist", mFilePath);
		return false;
	}

	// get size of file
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if (sz == 0)
	{
		log_info("file %s is empty", mFilePath);
	}
	else
	{
		// TODO need to load all scores instead of just one
		if (fscanf(fp, "%d", &mScores[0]) == 1)
		{
			log_info("high score from file is %d", *mScores.begin());
		}
		else
		{
			log_err("fscanf failed on file: %s", mFilePath);
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;

}



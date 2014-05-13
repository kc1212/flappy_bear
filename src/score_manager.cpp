#include "score_manager.hpp"
#include <cstdio>
#include <algorithm>

#include "utils.hpp"

ScoreManager::ScoreManager() {}

ScoreManager::ScoreManager(SDL_Renderer* renderer, int x, int y)
	: mFilePath("../score.txt")
	, mTitleView("../assets/Gravity-Light.ttf", renderer, x, y)
	, mScoreView("../assets/Gravity-Light.ttf", renderer, x, y)
{
	loadHighScoreFromFile();
}

ScoreManager::~ScoreManager() {}


int ScoreManager::getHighScore()
{
	return *max_element(mScores.begin(), mScores.end());
}

vector<int> ScoreManager::getHighScores()
{
	return mScores;
}

bool ScoreManager::setHighScoreIfValid(int score)
{
	if (mScores.size() < 10)
	{
		mScores.push_back(score);
	}
	else if (score > *min_element(mScores.begin(), mScores.end()))
	{
		sort(mScores.begin(), mScores.end());
		mScores[0] = score; // replace the smallest
	}
	else
	{
		// not a high score, do nothing
		return true;
	}
	return writeHighScoreToFile();
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

	// (re)write all scores to file
	for (vector<int>::reverse_iterator i = mScores.rbegin(); i != mScores.rend(); ++i)
		fprintf(fp, "%d\n", *i);

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
		int tmp;
		if (fscanf(fp, "%d", &tmp) == 1)
		{
			do
			{
				mScores.push_back(tmp);
				log_info("high score from file is %d", tmp);
			}
			while (fscanf(fp, "%d", &tmp) == 1);
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

bool ScoreManager::render()
{
	// TODO render a high score overlay
	return true;
}



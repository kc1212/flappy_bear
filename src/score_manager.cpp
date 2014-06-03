#include "score_manager.hpp"
#include <cstdio>
#include <algorithm>

#include "utils.hpp"

static bool customCompare (scorePair a, scorePair b)
{
	return a.s < b.s;
}

ScoreManager::ScoreManager()
{
	loadHighScoreFromFile();
}

ScoreManager::ScoreManager(SDL_Renderer* renderer, int x, int y)
	: mFilePath("../score.txt")
	, mTitleView("../assets/Gravity-Light.ttf", renderer, x-40, y)
	, mScoreView("../assets/Gravity-Light.ttf", renderer, x, y+100)
	, mBackground(renderer, 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT)
{
	mTitleView.setWidth(100);
	mTitleView.setHeight(40);
	mScoreView.setWidth(40);
	mScoreView.setHeight(40);
	loadHighScoreFromFile();
}

ScoreManager::~ScoreManager() {}


int ScoreManager::getHighScore()
{
	if (0 == mScores.size())
	{
		return -1;
	}
	return (*max_element(mScores.begin(), mScores.end(), customCompare)).s;
}

scorePair ScoreManager::getHighScoreAndTime()
{
	// TODO check for when mScores is empty or null
	return *max_element(mScores.begin(), mScores.end(), customCompare);
}

vector<scorePair> ScoreManager::getHighScores()
{
	sort(mScores.begin(), mScores.end(), customCompare);
	return mScores;
}

bool ScoreManager::setHighScoreIfValid(int score)
{
	scorePair p = {score, time(NULL)};
	if (0 == score)
	{
		return true;
	}
	else if (mScores.size() < 10)
	{
		mScores.push_back(p);
	}
	else if (score > (*min_element(mScores.begin(), mScores.end(), customCompare)).s)
	{
		sort(mScores.begin(), mScores.end(), customCompare);
		mScores[0] = p; // replace the smallest
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

	if (NULL == fp)
	{
		log_err("failed to open file: %s", mFilePath);
		fclose(fp);
		return false;
	}

	// (re)write all scores to file
	for (vector<scorePair>::reverse_iterator i = mScores.rbegin(); i != mScores.rend(); ++i)
	{
		fprintf(fp, "%d,%ld\n", (*i).s, (*i).t);
	}

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

	if (0 == sz)
	{
		log_info("file %s is empty", mFilePath);
	}
	else
	{
		scorePair p;
		char buffer[1024];
		while (fgets(buffer, 1024, fp))
		{
			if (0 == sscanf(buffer, "%d,%ld", &(p.s), &(p.t)))
			{
				log_err("fscanf failed on file: %s", mFilePath);
				fclose(fp);
				return false;
			}
			mScores.push_back(p);
		}
	}

	fclose(fp);
	return true;

}

bool ScoreManager::render()
{
	// TODO alpha not working
	mBackground.render();

	mTitleView.setText("High Scores:");
	mTitleView.render();

	getHighScores(); // to sort

	if (0 == mScores.size())
	{
		mScoreView.setText("nil");
		mScoreView.render();
	}
	else if (0 == mScores[0].s)
	{
		mScoreView.setText("nil");
		mScoreView.render();
	}
	else
	{
		mScoreView.setText(getHighScores()[0].s);
		mScoreView.render();
	}

	return true;
}



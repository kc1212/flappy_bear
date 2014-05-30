#ifndef _SCORE_MANAGER_HPP_
#define _SCORE_MANAGER_HPP_

#include <vector>
#include <ctime>
#include "texture.hpp"
#include "text_view.hpp"

using namespace std;

const int SCORE_COUNT = 10;

typedef struct {
	int s; // score
	time_t t; // time
} scorePair;

class ScoreManager {

public:
	int getHighScore();
	scorePair getHighScoreAndTime();
	std::vector<scorePair> getHighScores();
	bool setHighScoreIfValid(int score);
	bool loadHighScoreFromFile();
	bool writeHighScoreToFile();
	bool render();
	ScoreManager();
	ScoreManager(SDL_Renderer* renderer, int x = 175, int y = 70);
	~ScoreManager();

private:
	const char* mFilePath;
	std::vector<scorePair> mScores;
	TextView mTitleView;
	TextView mScoreView; // TODO need multiple textviews


};

#endif



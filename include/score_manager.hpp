#ifndef _SCORE_MANAGER_HPP_
#define _SCORE_MANAGER_HPP_

#include <vector>
#include "texture.hpp"
#include "text_view.hpp"
#include "geometry.hpp"

using namespace std;

const int SCORE_COUNT = 10;

class ScoreManager {

public:
	int getHighScore();
	std::vector<int> getHighScores();
	bool setHighScoreIfValid(int score);
	bool loadHighScoreFromFile();
	bool writeHighScoreToFile();
	bool render();
	ScoreManager();
	ScoreManager(SDL_Renderer* renderer, int x = 175, int y = 70);
	~ScoreManager();

private:
	const char* mFilePath;
	std::vector<int> mScores;
	TextView mTitleView;
	TextView mScoreView; // TODO need multiple textviews
	Geometry mBackground;

};

#endif



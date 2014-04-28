#ifndef _SCORE_MANAGER_HPP_
#define _SCORE_MANAGER_HPP_

#include <vector>

using namespace std;

const int SCORE_COUNT = 10;

class ScoreManager {

public:
	int getHighScore();
	std::vector<int> getHighScores();
	// TODO get all scores
	bool setHighScoreIfValid(int score);
	bool loadHighScoreFromFile();
	bool writeHighScoreToFile();
	ScoreManager();
	~ScoreManager();

private:
	const char* mFilePath;
	std::vector<int> mScores;

};

#endif

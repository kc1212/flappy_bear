#ifndef _SCORE_MANAGER_HPP_
#define _SCORE_MANAGER_HPP_

class ScoreManager {

public:
	int getHighScore(){return mHighScore;}
	// TODO get all scores
	bool setHighScoreIfValid(int score);
	bool loadHighScoreFromFile();
	bool writeHighScoreToFile();
	ScoreManager();
	~ScoreManager();

private:
	int mHighScore;
	const char* mFilePath;
};

#endif

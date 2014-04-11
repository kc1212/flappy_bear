#include <fstream>

#ifndef _SCORE_MANAGER_HPP_
#define _SCORE_MANAGER_HPP_

class ScoreManager {

  public:
    int getHighScore(){return mHighScore;}
    void setHighScoreIfValid(int score);
    ScoreManager();
    ~ScoreManager();
  private:
    int mHighScore;
    std::ofstream mFileWriter;
    std::ifstream mFileReader;
    const char * mFilePath;

};

#endif

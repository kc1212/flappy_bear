#include <iostream>
#include "score_manager.hpp"

ScoreManager::ScoreManager()
{
  mFilePath = "../assets/score.txt";
  char fileContent[100];
  mFileReader.open(mFilePath);
  mHighScore = atoi(fileContent);
  mFileReader.close();
}

ScoreManager::~ScoreManager()
{
  mFileWriter.open(mFilePath);
  mFileWriter << mHighScore;
  mFileWriter.close();
}

void ScoreManager::setHighScoreIfValid(int score)
{
  if (score > mHighScore)
  {
    mHighScore = score;
  }
}


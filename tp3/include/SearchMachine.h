#ifndef SEARCHMACHINE_H
#define SEARCHMACHINE_H

#include <string>
#include "InvertedIndex.h"
#include "RankingList.h"

class SearchMachine
{
public:
  SearchMachine(std::string corpusDirPath, std::string stopwordsFilePath, std::string queryFilePath, std::string rankingFilePath);
  ~SearchMachine();
  void execute();

private:
  std::string strToLower(std::string str);

  void preProcessCorpus();
  void recursiveProcessTerm(std::string term, int documentId);
  void processCorpus();
  void processInvertedIndex();
  void processQuery();
  void printResult();

  std::string corpusDirPath;
  std::string stopwordsFilePath;
  std::string queryFilePath;
  std::string rankingFilePath;

  unsigned int corpusSize;
  unsigned int vocabularySize;

  InvertedIndex *invertedIndex;
  RankingList *rankingList;
};

#endif
#include <math.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "SearchMachine.h"
#include "InvertedIndex.h"

SearchMachine::SearchMachine(std::string corpusDirPath, std::string stopwordsFilePath, std::string queryFilePath, std::string rankingFilePath)
{
  if (!std::filesystem::is_directory(corpusDirPath))
  {
    throw "invalid corpus directory";
  }
  if (!std::filesystem::exists(stopwordsFilePath))
  {
    throw "invalid stopwords file";
  }
  if (!std::filesystem::exists(queryFilePath))
  {
    throw "invalid input query file";
  }
  if (!std::filesystem::exists(rankingFilePath))
  {
    throw "invalid output ranking file";
  }

  this->corpusDirPath = corpusDirPath;
  this->stopwordsFilePath = stopwordsFilePath;
  this->queryFilePath = queryFilePath;
  this->rankingFilePath = rankingFilePath;
  this->corpusSize = 0;
  this->vocabularySize = 0;
  this->invertedIndex = nullptr;
  this->rankingList = nullptr;
}

SearchMachine::~SearchMachine()
{
  // delete this->invertedIndex;
}

std::string SearchMachine::strToLower(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

// count the number of terms inside the corpus. it would be better to count just the amount of different terms instead of counting all.
void SearchMachine::preProcessCorpus()
{
  std::fstream corpusFile;
  std::string term;
  for (auto const &corpusFilePath : std::filesystem::directory_iterator{this->corpusDirPath})
  {
    this->corpusSize++;
    corpusFile.open(corpusFilePath.path());
    while (corpusFile >> term)
    {
      this->vocabularySize++;
    }
    corpusFile.close();
  }
}

// this function is recursive to split terms if necessary when there is separators like \n \r \t and others
void SearchMachine::recursiveProcessTerm(std::string term, int documentId)
{
  std::string newTerm;
  bool needsToBeSplitted = false;

  std::fstream stopwordsFile;
  std::string stopword;
  bool isStopword;

  // split term if necessary
  for (unsigned int i = 0; i < term.length(); ++i)
  {
    if (term[i] == '!' || term[i] == '\\' || term[i] == '|' || term[i] == ',' || term[i] == '.' || term[i] == ';' || term[i] == ':' || term[i] == '/' || term[i] == '?')
    {
      if (i < term.length() - 1 && term[i] == '\\' && (term[i + 1] == 'r' || term[i + 1] == 'n' || term[i + 1] == 't'))
      {
        newTerm = term.substr(i + 2);
        term = term.substr(0, i);
        needsToBeSplitted = true;
      }
      else
      {
        newTerm = term.substr(i + 1);
        term = term.substr(0, i);
        needsToBeSplitted = true;
      }
    }
  }

  // if the term is valid, add to the inverted index
  if (term.length() > 0)
  {
    isStopword = false;
    term = this->strToLower(term);
    // for each term, compare with all stopwords and discard the term if it is one. it would be better to save the stopwords on an array before.
    stopwordsFile.open(this->stopwordsFilePath);
    while (stopwordsFile >> stopword)
    {
      stopword = this->strToLower(stopword);
      if (term == stopword)
      {
        isStopword = true;
        break;
      }
    }
    stopwordsFile.close();
    // if the term is not a stopword, add to the inverted index. inverted index is responsible to check if the term exists, document already has it and etc
    if (!isStopword)
    {
      invertedIndex->add(term, documentId);
    }
  }

  // if a new term was found, do the function again with the other part
  if (needsToBeSplitted)
  {
    recursiveProcessTerm(newTerm, documentId);
  }
}

// create a inverted index using the given corpus
void SearchMachine::processCorpus()
{
  this->invertedIndex = new InvertedIndex(this->vocabularySize);

  std::fstream corpusFile;
  std::string term;
  int documentId;

  // for each document, add its terms and frequencies to the inverted index
  for (auto const &corpusFilePath : std::filesystem::directory_iterator{this->corpusDirPath})
  {
    documentId = std::stoi(corpusFilePath.path().stem());
    corpusFile.open(corpusFilePath.path());
    while (corpusFile >> term)
    {
      recursiveProcessTerm(term, documentId);
    }
    corpusFile.close();
  }
}

// after inverted index is created, run this function to calculate wtd of each document-term and each document wd2
void SearchMachine::processInvertedIndex()
{
  // instantiate ranking list. it is gonna be used here just to store data. will do a ranking function just on the next function "processQuery"
  this->rankingList = new RankingList(this->corpusSize);

  // for each term list inside the inverted index, get each term. then for each term, get its frequency list. then for each frequency node inside the frequency list, calculates document term wtd and updates document wd2
  for (unsigned int i = 0; i < this->invertedIndex->getSize(); ++i)
  {
    TermList termList = this->invertedIndex->getAtPosition(i);
    if (termList.getSize() == 0)
    {
      continue;
    }
    TermNode *termNode = termList.getFirst();
    for (unsigned int j = 0; j < termList.getSize(); ++j)
    {
      FrequencyList *frequencyList = termNode->getFrequencyList();
      if (frequencyList->getSize() == 0)
      {
        continue;
      }
      FrequencyNode *frequencyNode = frequencyList->getFirst();
      for (unsigned int k = 0; k < frequencyList->getSize(); ++k)
      {
        // calculate wtd using given formula
        int ftd = frequencyNode->getTermFrequency();
        int D = this->corpusSize;
        int ft = frequencyList->getSize();
        // set wtd for the current document term
        frequencyNode->setWtd(ftd * log(D / ft));
        RankingNode *rankingNode = this->rankingList->search(frequencyNode->getDocumentId());
        // if the document isn't already present on the ranking, add it
        if (rankingNode == nullptr)
        {
          rankingNode = new RankingNode();
          rankingNode->setDocumentId(frequencyNode->getDocumentId());
          this->rankingList->add(rankingNode);
        }
        // updates document wd2 using the wtd calculated
        rankingNode->increaseWd2(pow(frequencyNode->getWtd(), 2));
        frequencyNode = frequencyNode->getNext();
      }
      termNode = termNode->getNext();
    }
  }
}

// process the given query to calculate each document similarity present on the ranking
void SearchMachine::processQuery()
{
  std::fstream queryFile;
  std::string term;

  for (unsigned int i = 0; i < this->rankingList->getCursor(); ++i)
  {
    RankingNode *rankingNode = this->rankingList->getList()[i];
    if (rankingNode == nullptr)
    {
      continue;
    }
    queryFile.open(queryFilePath);
    while (queryFile >> term)
    {
      term = this->strToLower(term);
      TermNode *termNode = this->invertedIndex->search(term);
      if (termNode == nullptr)
      {
        continue;
      }
      FrequencyNode *frequencyNode = termNode->getFrequencyList()->search(rankingNode->getDocumentId());
      if (frequencyNode == nullptr)
      {
        continue;
      }
      rankingNode->setSim(rankingNode->getSim() + frequencyNode->getWtd());
    }
    queryFile.close();
    rankingNode->setSim(rankingNode->getSim() / sqrt(rankingNode->getWd2()));
  }

  // after each document similarity is calculated, order ranking
  this->rankingList->quicksort(0, this->rankingList->getCursor() - 1);
}

// gets the first 10 documents with non-zero similarity and puts into the output file
void SearchMachine::printResult()
{
  std::fstream rankingFile;
  RankingNode **rankingList = this->rankingList->getList();

  rankingFile.open(rankingFilePath);
  for (int i = 0; i < 10; ++i)
  {
    if (rankingList[i]->getSim() <= 0)
    {
      break;
    }
    if (i != 0)
    {
      rankingFile << " ";
    }
    rankingFile << rankingList[i]->getDocumentId();
  }
  rankingFile.close();
}

void SearchMachine::execute()
{
  this->preProcessCorpus();
  this->processCorpus();
  this->processInvertedIndex();
  this->processQuery();
  this->printResult();
}
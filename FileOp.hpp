#ifndef __FILEOP__HPP__
#define __FILEOP__HPP__

#include "common.hpp"
#include "Ialgorithm.hpp"
#include<utility> // for pair

/*
 - Lets make it singleTon
 - To get the wordline, maintain count.. if empty discare
 - Composition of strategy object run time
 - Invoke Display to display based upon worldine's
*/
class Display;
class SearchIndex;
class FileOp{
   std::string wordline; 
   std::ifstream infile;
   mvs collection;	  // the whole string, with wordlineNumber 
   vs FilteredStoreWord;  // the keywords set
   uint64_t key,totalWordline;
  public:
	static FileOp *instance;
	static FileOp *GetFileOp();
	static FileOp *ResetFileOp();
	void ReadFile(std::string);
	void ReadFile(std::string,SearchIndex *&);
	void Show(void);// need to check if we nedd sDisplay class
	void Show(uint64_t pos);
   friend class Display;
   private:
	~FileOp();
	FileOp();
   	FileOp(const FileOp&);
	FileOp& operator=(const FileOp&); 
   private:
	void SplitSentenceAndCount(std::string str);
	void SplitSentenceAndCount(std::string str,char);
	void SplitSentenceAndCount(std::string str,char,SearchIndex *&);
	void Filter(std::string &RawWord);
	void EndsTrim(std::string &);
};

// to contain the text indexed..concerte will implment it
class SearchIndex
{
   ialgorithm *algo;
   //FileOp *DataObject;
  public:
   SearchIndex();
   ~SearchIndex();
   void SetAlgo(ALGO_TYPE);
   void ProcessOnData(FileOp *&DataObject);
   void GetResultantWordLines(const vs &, ResultSet &); // to return the result set 
   void SendTextTokensUpdate2Alog(vs &,uint64_t); //vs, wordlinenum
};
#endif

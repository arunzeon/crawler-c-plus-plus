#include "FileOp.hpp"
#include "Display.hpp"
#include "Search_h.hpp"
#include "Search_s.hpp"

char filterSet[] = "(*);.[]><!'' '''"; // - excluded

FileOp* FileOp::instance = NULL;

FileOp* FileOp::GetFileOp()
{
	if(!instance)
	   instance = new FileOp;
	return FileOp::instance;
}


FileOp* FileOp::ResetFileOp()
{
	delete instance;
	instance = NULL; 
	return instance;
}

FileOp::FileOp()
{
  key = 0;
  totalWordline = 0;
  msg(" FileOp con");
}

FileOp::~FileOp()
{
	msg("FileOp Destructor");
}

void
FileOp::ReadFile(std::string str,SearchIndex *&indexer )
{
    #if DEBUG
	std::cout << "FileOp: " << __FUNCTION__ << " " <<  str << " LEN:" << str.length() << " SIZE:" << str.size() <<   std::endl;
     #endif
    SplitSentenceAndCount(str,SPACE,indexer);
}


void
FileOp::Filter(std::string &RawWord)
{
	// Running my filter set
        for(unsigned int i=0; i< strlen(filterSet); i++)
        {
                RawWord.erase(remove(RawWord.begin(),RawWord.end(), filterSet[i]), RawWord.end());
        }
	
	// transfoming to lower case
	std::transform(RawWord.begin(), RawWord.end(),RawWord.begin(), ::tolower);

	// transforming into all lower
	EndsTrim(RawWord);
}


void
FileOp::EndsTrim(std::string &str)
{
	if(str.empty())
		return;
	
	std::size_t checkpt = str.find_first_not_of(' ');
	std::size_t firstpt = checkpt==std::string::npos?str.length():checkpt;
	std::size_t lastpt = str.find_last_not_of(' ');
	str.substr(firstpt,(lastpt-firstpt)+1);
}

void 
FileOp::SplitSentenceAndCount(std::string str,char Delimit,SearchIndex *&indexer)
{
	vs localStoreWord;
	std::stringstream ss(str);
	std::string tok;
  	while(getline(ss, tok, Delimit))
	{
		if(tok.size() >= QLIMIT)
		{
                        std::string ftemp(tok);
			// Filter the punctions of interes
                        //Filter(ftemp);	
                        GenFilter(ftemp);	
			localStoreWord.push_back(ftemp);
		}
	}
	
	if(DEBUG)msg(" LocalStoe:");
	if(DEBUG)std::cout << "localStoreLEN:" << localStoreWord.size() << std::endl;

	if(localStoreWord.size() != 0)
	{
	   // Lets track thew wordline, store the wordline
	   collection.insert (std::make_pair(key,str));
		#if DEBUG
		loop(localStoreWord,it)
			std::cout << " IN[" << (*it).size() << " ]: " << (*it);
		#endif
	   FilteredStoreWord.insert(FilteredStoreWord.end(), 
				    localStoreWord.begin(),
				    localStoreWord.end());

	  // Filtered keys need to go to indexer.. that is into SearchIndex for processing
	  indexer->SendTextTokensUpdate2Alog(localStoreWord, totalWordline);

	   totalWordline++; 	
	   key++;
	}	
	//return localStoreWord;	
}

void
FileOp::Show(uint64_t pos)
{
	mvs::iterator mitr = collection.find(pos);
	if(mitr != collection.end())
	{
		std::cout << mitr->second << std::endl;
	}
}

void
FileOp::Show()
{
	std::cout << "    SHOW START  " << std::endl;

	std::cout << " Total key      : " << key << std::endl;
	std::cout << " Total WordLines: " << totalWordline << std::endl; 
	std::cout << " Dictionary is  : " << std::endl;
	typedef mvs::iterator miter;
	std::cout << "WorldLine: " << " ------ " << " Sentence:" << std::endl;
	for(miter it = collection.begin(); it != collection.end(); it++)
	{
	std::cout << it->first << " ------- ";
	typedef std::string::iterator valStr;
	for(valStr vt=it->second.begin(); vt != it->second.end(); vt++)
		std::cout << (*vt);
	std::cout << std::endl;
	}

	std::cout << std::endl;	
	std::cout << std::endl;	
	
	std::cout << " keywords collected total= " <<  FilteredStoreWord.size() << std::endl;
	loop(FilteredStoreWord, it)
		std::cout << (*it) << std::endl;
	std::cout << " SHOW DONE " << std::endl;
}

// NEED a functrion, which could seqeeze those individual words to remove exlam !, ? etc  ", ",", "!", "?"
// then hash of input owrds also needs to be done in similar ways
// Optimized: could use two thread , one to read from left amd other from right, i<j and mutex this i, j and vector where push
void 
FileOp::SplitSentenceAndCount(std::string str){
        std::cout << " in Split:" << str << std::endl;
        // Could call Filter to take off, a, the etc
        char *tmpBuff = new char[str.size()+1];
        char *Aword = NULL;
        vs vetWords;
        unsigned int wordCount = 0;
        int index = 0;
        strncpy(tmpBuff,str.c_str(), str.size());
        tmpBuff[str.size()+1] = WEND;
        std::cout << " THE ALL SIZE:" << str.size() << std::endl;
#define LDEBUG 1
        for(unsigned int i=0; i < str.size()+1; i++)
        {
                if(LDEBUG)std::cout << " Here";
                if(tmpBuff[i] == ' ')
                {
                        if(index <= 1 || (Aword == NULL))
                        {
                                if(LDEBUG)std::cout << "D";
                                std::cout << " Not interested words or character::" << std::endl;
                        }else{
                                if(LDEBUG)std::cout << "E"; 
                                Aword[index] = WEND; 
                                if(strlen(Aword) > 0)
                                {
                                                std::cout << " Interested words ::" << std::string(Aword) << std::endl;
						std::cout << " ==== " << std::endl;
                                                std::string ftemp(Aword); // filter out the word
                                                Filter(ftemp);
                                                vetWords.push_back(ftemp);//Aword);
                                                wordCount++;
                                }
                        }

                        if(LDEBUG)std::cout << "F";
			if(Aword)
                        delete [] Aword;
                        Aword = NULL;
                        index = 0;
                }else{
                        if(LDEBUG)std::cout <<  "A";
                        if(Aword == NULL){
                                if(LDEBUG)std::cout << "B";
                                Aword = new char[str.size()+1];
                        }
                        if(LDEBUG)std::cout << " cindex=" << i;
                        Aword[index++] = tmpBuff[i];
                        if((i == str.size()) &&
                           (i > 1))
                        {
				if(LDEBUG) std::cout << " INDEX==" << index << std::endl;
                                Aword[index-1] = WEND;
                                std::cout << " Last Len=" << strlen(Aword) << std::endl;
                                if(strlen(Aword) > 0)
                                {
                                        std::cout << " Last Interested words ::" << std::string(Aword) << std::endl;
                                        std::string ftemp(Aword);
                                        Filter(ftemp);
                                        vetWords.push_back(ftemp);//Aword);
                                        wordCount++;
                                }
                                if(Aword)delete [] Aword;
                                Aword = NULL;
                                index = 0;
                        }
                }
        }
        delete [] tmpBuff;

        std::cout << std::endl;
        std::cout << " End of processing:: wordCount" << wordCount <<  std::endl;
        std::cout << " Words are:" << std::endl;
//	if(Aword)
//	  delete [] Aword;
        for(std::vector<std::string>::iterator it = vetWords.begin(); it != vetWords.end(); it++){
                        std::cout << " ------------:" << (*it) << std::endl;
        }

}

 
void
SearchIndex::ProcessOnData(FileOp *&DataObject)
{
	// Could get the data from FileOp and do Indexing..
	msg(" I am ProcessOnData");
	//DataObject->Show();
	std::cout << std::endl;
	std::cout << std::endl;
	
	if(DEBUG)std::cout << " Startegy:" << std::endl;
	if(DEBUG)std::cout << " Startegy Done:" << std::endl;
}

SearchIndex::SearchIndex():algo(NULL)
{
	msg("I am SearchIndex Con");
	//FileOp *DataObject = FileOp::GetFileOp();
}

SearchIndex::~SearchIndex()
{
	if(algo)
	   delete algo;
	algo = NULL;
}

// dynamcically change the algo, by client
void
SearchIndex::SetAlgo(ALGO_TYPE whichtype)
{
	switch(whichtype)
	{
	case FAST_SEARCH_H:
			algo = new Search_h;
			break;
	case FAST_SEARCH_S:
			algo = new Search_s;
			break;
	case END_SEARCH:
	default:	
		msg(" Invalid algo specified..setting to default");
		algo = new Search_h;
		  
	}
}

void
GenFilter(std::string &RawWord)
{
	// Running my filter set
        for(unsigned int i=0; i< strlen(filterSet); i++)
        {
                RawWord.erase(remove(RawWord.begin(),RawWord.end(), filterSet[i]), RawWord.end());
        }
	
	// transfoming to lower case
	std::transform(RawWord.begin(), RawWord.end(),RawWord.begin(), ::tolower);

	// transforming into all lower
	if(RawWord.empty())
		return;
	
	std::size_t checkpt = RawWord.find_first_not_of(' ');
	std::size_t firstpt = checkpt==std::string::npos?RawWord.length():checkpt;
	std::size_t lastpt = RawWord.find_last_not_of(' ');
	RawWord.substr(firstpt,(lastpt-firstpt)+1);
	
}

void
SearchIndex::SendTextTokensUpdate2Alog(vs &keyset,uint64_t wordlinenum)
{
	// Need to call Specific Algo to have Permanet Index base
	//algo payload
	PayLoad load;
	load.wordlinenum = wordlinenum;
	load.keyset = keyset;

	//algo	
	algo->UpdateIndex(load);
	
	#if DEBUG
	//ResultSet res = algo->ObtainResult();
	//loop(res.RestLine,et)
	//	std::cout <<  "# " << (*et) << std::endl;
	#endif

}

void
SearchIndex::GetResultantWordLines(const vs &queryTokens,ResultSet &resultPos)
{
   msg(" In getReuslt");
   #if DBEUG
   loop(queryTokens, it)
	std::cout << "-->" << (*it) << std::endl;
    #endif
    algo->Run(queryTokens, resultPos); 
}

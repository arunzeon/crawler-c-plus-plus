#include "common.hpp"
#include "Search_h.hpp"

Search_h::Search_h()
{
	msg(" Search_h Con");
}

void
Search_h::Run(const vs &qtokens, ResultSet &resultRecord)
{
	msg("I am SH RUn process me");
	bool flag = false;

	// Set all positions
	bitset<MAXTEXTLN> tmpbits;
	SetAllPositions(tmpbits);
	
        loop(qtokens, it)
 	{
	 	uint64_t hval = hashword((*it));
		if(DEBUG)std::cout << " RUN SH::FOR TOK:" << (*it) <<  " [" << hval << "]" << std::endl;
		mhs::iterator mitr = indexer.find(hval);
		if(mitr != indexer.end())
		{
			flag = true;
			tmpbits = (mitr->second & tmpbits);					
		}
	}
	
	if(flag)
	{
	  #if DEBUG
		  msg(" RUN SH:: BitShow");
		  BitSetShow(tmpbits);
	  #endif
	  std::string resInstr = GetString(tmpbits);
	  resultRecord.RestLine = GetPositions(resInstr);
	}
}

void
Search_h::UpdateIndex(PayLoad &load)
{
   // Lets keey uploading the keyset till complete read of text
   result.keyset.insert(result.keyset.end(),
			load.keyset.begin(),
			load.keyset.end());

   // take each of wrods, hash those, store in indexer
   loop(load.keyset, it)
   {
	uint64_t hval = hashword((*it));
	mhs::iterator mitr = indexer.find(hval);
	if(mitr == indexer.end())
	{
	    #if DEBUG
	       msg(" In UpdateIndex IINSERT");
	       std::cout << "INDEXkey[ABC]:" << (*it) << "[ " << hval << "]" <<  "wordline:" << load.wordlinenum << std::endl; 
	    #endif
	    // update teh value
	    bitset<MAXTEXTLN> tmp;
	    ResetPositions(tmp);  

	    //set the position
            SetPosition(tmp,load.wordlinenum);
	   	    
	    indexer.insert(std::make_pair<uint64_t,std::bitset<MAXTEXTLN> >(hval,tmp));   
	}else{
	     #if DEBUG
	     	msg(" In UpdateIndex UPDATE");
		std::cout << "INDEXkey[XYZ] ===>:" << (*it) << "[ " << hval << "]" << " Wordline:" << load.wordlinenum << std::endl;
	     #endif	
	    // update position
	    SetPosition(mitr->second,load.wordlinenum);
	}
   } 
}

//ratehr than ResultSet.. just let it be bitvect
ResultSet
Search_h::ObtainResult()
{
vi temp;
temp.push_back(101);
temp.push_back(102);
temp.push_back(103);
  ResultSet inst;
	inst.RestLine = temp;
  return inst;
}

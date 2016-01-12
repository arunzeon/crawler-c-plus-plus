#include "Display.hpp"
#include "common.hpp"

Display::Display()
{
  msg("I am display Con"); 
  if(DEBUG)system("clear");
}


const vs&
Display::GetQTokens() const
{
    #if DEBUG
    msg(" In getQToken");
    loop(queryWords, it)
	std::cout << " ::" << (*it) << std::endl;
    #endif
    return queryWords; 
}

bool
Display::ReadQuery(FileOp *&FileObject)
{
    // Flush up old query
    queryWords.clear();

    std::cout << " Type quit to exit..." << std::endl;
    std::cout << " Search : ";
    getline(std::cin, queryString); 
    if(DEBUG) std::cout << " QUERY String: " << queryString << std::endl;
    if(queryString.compare("quit") == 0)
    {
	std::cout << " Thanks for using..." << std::endl;
	return false;
    }else{
	ProcessQuery();
	if(!queryWords.empty())
	{
		// Let SearchIndex do the processing.
		//QueryIndex(FileObject);
	}
    }

//flush of the tokens for next query
//queryWords.clear();

  return true;
	
}

void
Display::QueryIndex(FileOp *&FileObject)
{
    msg("  DISPLAY'S RESULT");
	// using thw queryWords.. and FilObject
	// that is SearcIndex object to get Result Set
	// then call the FileObj..for specia bitsets
  	//FileObject->Show();
}

void
Display::ProcessQuery()
{
	std::stringstream ss(queryString);
	std::string tok;
	while(getline(ss,tok,' '/*SPACE*/))
	{
		if(tok.size() >= QLIMIT)
		{
			std::string ftemp(tok);
			GenFilter(ftemp);
			queryWords.push_back(ftemp);
		}	
	} 

	#if DEBUG
	  msg(" Query Tokens:");
	  loop(queryWords,it)
		std::cout << "->" << (*it) << std::endl;
	#endif
}

void
Display::DisplayRes(FileOp *&FileObject, ResultSet &res)
{
	uint64_t cnt = 1;
	std::cout << "[ Results               :     ]" << std::endl;
	std::cout << "[ * Occurance/Count     :  " << res.RestLine.size() << "  ]" << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	loop(res.RestLine, it)
	{
std::cout << cnt++ << ":";
		FileObject->Show((*it));		
	}            

}

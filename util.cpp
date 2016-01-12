#include "util.hpp"

util::util(){
 msg("wht the f'uk");
}

void 
util::SetAllPositions(bitset<MAXTEXTLN> &bset)
{
	bset.set();
}

void 
util::ResetPositions(bitset<MAXTEXTLN> &bset)
{
	bset.reset();
}

void 
util::SetPosition(bitset<MAXTEXTLN> &bset, uint64_t pos)
{
	// this fellow is wrapping after 63, hence ditcing it
	// bset |= (1ULL << pos);
	bset[pos] = TRUE;
}

vector<uint64_t>
util::GetPositions(string &str)
{
	vector<uint64_t> SearchedLines;
	if(DEBUG)std::cout << " pos:" << std::endl;
	uint64_t cnt = 0;
	for(uint64_t i=str.length() - 1; i>0; i--)		
	{
		if(str.at(i) == '1')
		{
			#if DEBUG 
			  std::cout << " Set at:" << i << "POS:" << cnt <<  std::endl;
			#endif
			SearchedLines.push_back(cnt);
		}
		cnt++;
	}
	
	return SearchedLines;
}

std::string
util::GetString(bitset<MAXTEXTLN> &res)
{
 std::string msstring =
    res.to_string<char,std::string::traits_type,std::string::allocator_type>();

  return msstring;	
}

void
util::BitSetShow(bitset<MAXTEXTLN> &bset)
{
std::string mystring =
    bset.to_string<char,std::string::traits_type,std::string::allocator_type>();

	#if DEBUG	
	 std::cout << "string:" << mystring << std::endl;
	#endif
}

//Dan's djb2 
uint64_t
util::hashword(std::string str)
{
    //unsigned long hash = 5381;
    uint64_t hash = 5381;
    int c;
    char *input = new char[str.length()+1];
    strcpy(input, str.c_str());
    while (c = *input++)
        hash = ((hash << 5) + hash) + c; 

    return hash;
}

#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include "common.hpp"
using namespace std;

class util
{
     util(const util &);
     util& operator=(const util &);
  public:
        uint64_t hashword(std::string str);
	util();
	std::vector<uint64_t> GetPositions(std::string &str);
	void BitSetShow(bitset<MAXTEXTLN> &bset);
	std::string GetString(bitset<MAXTEXTLN> &res);
	void SetPosition(bitset<MAXTEXTLN> &bset, uint64_t pos);
	void ResetPositions(bitset<MAXTEXTLN> &bset);
	void SetAllPositions(bitset<MAXTEXTLN> &bset);
};
#endif

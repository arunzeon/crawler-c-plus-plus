#ifndef __SEARCH_S_HPP__
#define __SEARCH_S_HPP__

#include "Ialgorithm.hpp"

//suffix array based
class Search_s:public ialgorithm{
	PayLoad result;// result vect, need otbe bitvect 
	vis bucket;
	void xsearch(std::vector<std::string> &s, 
			bool &found, std::string &position, 
			std::string &ss);
	void getConStr(const vs &, std::string &);
  public:
	Search_s();
	virtual void Run(const vs &, ResultSet &);
	virtual void UpdateIndex(PayLoad &);
	virtual ResultSet ObtainResult();
};
#endif

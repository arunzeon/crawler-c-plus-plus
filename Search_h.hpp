#ifndef __SEARCH_H_HPP__
#define __SEARCH_H_HPP__

#include "Ialgorithm.hpp"
#include "util.hpp"

//hash based
class Search_h:public ialgorithm,public util{
	PayLoad result; //result vector, need to make bitvect
	mhs  indexer ;// hash -- bitset
   public:
	Search_h();
	virtual void Run(const vs &,ResultSet &);
	virtual void UpdateIndex(PayLoad &);
	virtual ResultSet ObtainResult();
	
}; 
#endif

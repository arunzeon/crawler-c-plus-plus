#ifndef __IALGORITHM_HPP__
#define __IALGORITHM_HPP__
#include "common.hpp"

class ialgorithm{
  public:
	virtual void Run(const vs &, ResultSet &) = 0;
	virtual void UpdateIndex(PayLoad &) = 0;
	virtual ResultSet ObtainResult() = 0;
};
#endif

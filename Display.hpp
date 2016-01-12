#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__
#include"common.hpp"
#include "FileOp.hpp"
#include<string>
// Need to get Wordline's and Display the collected stuff in FileOp
class Display
{
	std::string queryString;
	vs queryWords;   
  public:
	Display();
	bool ReadQuery(FileOp *&);
	const vs &GetQTokens() const;
	void DisplayRes(FileOp *&, ResultSet &);
  private:
	std::string GetQuery();
	//void ProcessQuery(std::string &);
	void ProcessQuery();
	void QueryIndex(FileOp *&);
};
#endif

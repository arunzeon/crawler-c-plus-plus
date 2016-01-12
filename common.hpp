#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<bitset>

#define CHECKBIT(var, pos) ((var) & (1 << (pos)))

#define DEBUG 0 
#define WEND '\0'
#define SPACE ' '
#define QLIMIT 2
#define TRUE 1
#define FALSE 0
// used by biset
#define MAXTEXTLN 1024

typedef std::vector<std::string> vs;
typedef std::vector<uint64_t> vi;
typedef std::map<uint64_t, std::string> mvs;
typedef std::map<uint64_t, std::bitset<MAXTEXTLN> > mhs;
typedef std::vector<std::pair<uint64_t, vs> > vis;
//typedef std::vector<std::pair<uint64_t, vs>>::iterator vpitr;


#define msg(x) \
	if(DEBUG)std::cout << " MSG:" << x << std::endl;

#define loop(c,it) \
        for(typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)

typedef enum ALGO_TYPE
{
	FAST_SEARCH_H = 0,
	FAST_SEARCH_S,
	END_SEARCH = FAST_SEARCH_S + 1
};

typedef struct PayLoad
{
	vs keyset;
	uint64_t wordlinenum;
};

typedef struct ResultSet
{
	vi RestLine;
};

void GenFilter(std::string &);
#endif

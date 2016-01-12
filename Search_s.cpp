#include "common.hpp"
#include "Search_s.hpp"
#include<algorithm>
#include<functional>

#define CHK(ss,vs,f,p)  \
        std::string stmp = vs.substr(0,ss.length()); \
        if(stmp == ss) \
        { \
        std::cout << " FOUND MATCH " << std::endl; \
        position = s.at(p); \
        f = true; \
        return; \
        } \


Search_s::Search_s()
{
	msg(" Search_s con");
}

void
Search_s::xsearch(std::vector<std::string> &s, bool &found, std::string &position, std::string &ss)
{
	if(DEBUG)
	{
		 loop(s,itr)
			std::cout << " sear:"
				  << (*itr) 
				  << std::endl;
	}

        int low = 0;
        int high = s.size()-1;
        int mid;
        while(low < high)
        {
                                mid = (low + high) / 2;
                                std::string tmp = s.at(mid);
                                if(tmp.length() >= ss.length())
                                {
    	                                  CHK(ss,tmp,found,mid)
                                }
                if(ss >= s.at(mid))
                {
                        low = mid+1;
                }else if(ss < s.at(mid))
                {
                        high = mid - 1;
                }else if(ss == s.at(mid)){
                        position = s.at(mid);
                        found = true;
                }else{
                        std::cout << " Shoudl not have come here" << std::endl;
                }

        }

        if(low == high)
        {
                std::string tmp2 = s.at(low);
                if(tmp2.length() >= ss.length())
                {
                      CHK(ss,tmp2,found,low)
                }
        }
        found = false;
}



void
Search_s::Run(const vs &qtokens, ResultSet &resultRecord)
{
	msg(" I am SS Run");
	bool found = false;
        std::string pos;

	std::string t;
	getConStr(qtokens,t);	
	loop(bucket,it)
        {
                found = 0;
                if(DEBUG)std::cout << " t:" << t << " Chceking for worldline:" << it->first <<  std::endl;
                xsearch(it->second, found, pos, t);

                if(found)
                {
                                if(DEBUG)std::cout << " Found match at pos :" << it->first << " pos:" << pos << std::endl;
				resultRecord.RestLine.push_back(it->first);
                }
        }

}


void
Search_s::UpdateIndex(PayLoad &load)
{
  msg(" Search_S  Update Index");
  result.keyset.insert(result.keyset.end(),
		       load.keyset.begin(),
		       load.keyset.end());


  std::string t;
  getConStr(load.keyset,t);	
  vs vsuffixes;
  for(int i = 0; i < t.size();i++)
  {
      vsuffixes.push_back(t.substr(i,t.size()-i));
  }
  sort(vsuffixes.begin(),vsuffixes.end());

  bucket.push_back(std::make_pair(load.wordlinenum,vsuffixes));
 
}


bool printable(char c) { return !isprint((unsigned)c); }

void
Search_s::getConStr(const vs &setStr,std::string &t)
{

  std::stringstream sStr;
  loop(setStr, sitr)
  	sStr << (*sitr);

  t.reserve(sStr.str().length());
  t = sStr.str();
  
  t.erase(remove_if(t.begin(), t.end(), printable),t.end());
}


ResultSet
Search_s::ObtainResult()
{
  msg(" ObtainReusltin Search_S");
 vi temp;
 temp.push_back(201);
 temp.push_back(202);
 temp.push_back(203);
  ResultSet inst;
	inst.RestLine = temp;
  return inst;
}

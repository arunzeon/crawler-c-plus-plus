///local/MV-131224/ip/tools/i686-gnu/bin/i686-montavista-linux-gnu-gdb64
#include<iostream.h>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<typeinfo>
#include<fstream>
#include<iostream>

#include "common.hpp"
#include "FileOp.hpp"
#include "Display.hpp"

using namespace std;

#define handle_error(msg) \
	do { perror(msg); } while (0)

#define MAX_ARG 3 

//convention of cmPurposes
int main(int argc, char **argv)
{
	pid_t child_pid, tpid;
	int exestatus;
	int child_status;
	char *envp[]={NULL};
        FileOp *cmProcessRead = FileOp::GetFileOp();
	SearchIndex *DataIndex = new SearchIndex;
	// Choose algo type
	DataIndex->SetAlgo(FAST_SEARCH_H);
	
	vector<string> args(argv+1, argv + argc);
	loop(args,it)
	   cout << "  " << (*it) << endl;	

	string line;
	ifstream processFile("refined.txt");
	if(processFile.good())
	{
		while(getline(processFile, line))
		{
		  if(!line.empty())
		  {
		     #if DEBUG
			cout << endl <<  " -----------------------------------------------" << endl;
			cout << " LINE:" << line << endl;
			cout << " -----------------------------------------------" << endl;
		      #endif
		      // Should append into Indexer, with wordlines
		      cmProcessRead->ReadFile(line, DataIndex);
		  }
		}
	   processFile.close();
	}else{
		handle_error(" processing file incomplete..bailing");
	}		


	// this needs to be called after ReadQuery	
    	DataIndex->ProcessOnData(cmProcessRead);	
	msg("Done...");

	Display *Render = new Display;
        while(Render->ReadQuery(cmProcessRead))
	{ //After each query flus off the Dispay tokens
		#if 0
		const vs &tmp = Render->GetQTokens();
		loop(tmp, it)
			std::cout << " %%:" << (*it) << std::endl;
		#endif
		ResultSet resultPos;
		DataIndex->GetResultantWordLines(Render->GetQTokens(), resultPos);
		
		Render->DisplayRes(cmProcessRead, resultPos);	
	}
		
	delete DataIndex;
	FileOp::ResetFileOp();
	delete Render;
}

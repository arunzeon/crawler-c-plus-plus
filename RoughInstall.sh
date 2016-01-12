#!/bin/bash
# Usage:
# ./RoughInstall.sh <URI> dontfetch
#   OR 
# ./RoughInstall.sh http://www.google.com
#
#

Cleanup2()
{
if [ -f level1.txt ]
then
  rm level1.txt
fi
if [ -f refined.txt ]
then
  rm refined.txt
fi
}

Cleanup()
{
echo " Cleaup.."
if [ -f phtml.phtml ]
then
	rm pthml.html
fi
Cleanup2
}

Prerequiste()
{
	echo "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
	echo " | prerequiste:						  | "
	echo " |    w3m        browser					  | "
	echo " |    /bin/bash  shell					  | "
	echo " |    python 3 or higher				  | "
	echo "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
	echo "								    "	
	echo "								    "	
}
	
Usage()
{
 	Prerequiste	
	echo "------------------------------------------------------------------------------------------"
	echo "												"
	echo " Please execute the script as ./RoughInstall.sh VALID-URI                                       "
	echo " NOTE:											"
	echo "     1. URI shoudl be fully qualified 							"
	echo "		Example: ./RoughInstall http://www.voidspace.org.uk				"
	echo " 	   2. WIKI considers this as BOT, Hence do no allow page fetch, In Windows python i was "
	echo "        ABLE to fetch page, Hence PRE-PROCESSED and provided a "refined.txt" with package."
	echo "         FOR http://en.wikipedia.org/wiki/Filmfare_Award_for_Best_Actor                   "
	echo "	   3. More details on  are provided in ReadMe.txt					"
	echo "												"
	echo "------------------------------------------------------------------------------------------"
	echo "												"
	echo "Please try again...									"
	echo "												"
}


if [ "$#" -lt 1 ] || [ "$#" -gt 1 ]
then
	Usage
	exit
fi

if [ "$1" == "dontfetch" ]
then
	Cleanup2 
	echo " Bypass dontfetch detected"
	echo "  ************************************************* "
	echo "  -- phtml.html should have bene generated offline  "
	echo "  ************************************************* "
else
	Cleanup
	echo " Fetching URL:  $1"
	python pGetPage.py -i $1
	sleep 2 
fi


# Defaulting to some allwoable page
# inital version
#python urtest.py $1 
# neew version 


if [ -f phtml.html ]
then
	echo " Running Level1 of html filter.............."
	w3m -dump -o display_charset=UTF-8 phtml.html > level1.txt
	echo " Running Level2 of html filter.............."
	sed 's/[!\@#\$%^&*();\"=.,/]//g' level1.txt > refined.txt
	echo " Running Level3 of html filter.............."
	sed -i 's/\[[^][]*\]/ /g' refined.txt
	sed -i 's/[\d128-\d255]//g' refined.txt
	echo " Preprocessing Done for request URI...."

	if [ -f refined.txt ]
	then
	  echo "Starting engine.."
	./Main
	fi
else
	echo " Page is not fetched, please check"
fi

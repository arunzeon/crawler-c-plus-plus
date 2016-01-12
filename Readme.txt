Problem Statement :-
--------------------
2) Create a webserver using existing libraries in C++ or Python.
 

Installation :-
-------------
* To build executable 
    make -f MakeFile
* Set permission of RoughInstall.sh
   chmod +x RoughInstall.sh

Device Details:-
--------------
* Red Hat Enterprise Lnux Server release 5.5(Tikanga)
* Bash version 3.2.25(1)-release (x86-readhat-linux-gnu)
* python 2.7

How to Search:-
--------------
* ./RoughInstall.sh <URI>
    ./RoughInstall.sh http://www.google.com

!!!!!!!!!!!!!!!!!!!!!NOTE:!!!!!!!!!!!!!!!!!!!!!!!
* the URL http://en.wikipedia.org/wiki/Filmfare_Award_for_Best_Actor is  blocked  by wiki
  the wiki website consider's this as bot.
  < tired change the user agent , but did not have much time on this>
  
  -- In windows, the script was able to fetch above specified URL, hence used as input.
  -- Please find the refined.txt file , for the URL in question.
  -- For the above URL , move the wikirefined.txt to refined.txt AND run like
      ./Main  
 
Results:-
---------
*
Expected Run on the http://en.wikipedia.org/wiki/Filmfare_Award_for_Best_Actor
Refer snapshot:-

 -- ResultSnapShot.png

*
How to Run and General other webpage Run such as http://www.google.com 
Refer snapshot:-
 
  -- HowToRun_Or_Install_SnapShot.png
 

  

Breif About Implementation:-
---------------------------
*Designed such that algorithm can be loosely coupled on the data set.
*Implementation uses strategy design pattern Ialgorithm.hpp for interface for the class which wishes
 implment new algorithm
* Debug options, and other parameters can be set in common.hpp file.
* Have implemented Hash based and not so good suffix array as algorithm ,
  namely Search_h referes to hash based and Search_s for suffix array based.
 


from __future__ import print_function
import urllib2
import sys

#total number of arguments
total = len(sys.argv)

print(" Total number of arguments: %d", total)
# argument list
scriptName = str(sys.argv[0])
FirstArg = str(sys.argv[1])
print(" First arg:%s",FirstArg)

term  = urllib2.quote("'{}'".format(FirstArg))
#log = open("pyouthtml.html", "w")
log = open("phtml.html", "w")
req = urllib2.Request('http://www.voidspace.org.uk');
#http://www.google.com');
#http://www.voidspace.org.uk')
#FirstArg)
#'http://www.voidspace.org.uk')
#https:://en.wikipedia.org/wiki/Filmfare_Award_for_Best_Actor')
response = urllib2.urlopen(req)
the_page = response.read()
print(the_page, file = log)


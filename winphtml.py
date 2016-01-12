import urllib2
import sys
req = urllib2.Request('http://en.wikipedia.org/wiki/Filmfare_Award_for_Best_Actor')
response = urllib2.urlopen(req)
the_page = response.read()
print the_page
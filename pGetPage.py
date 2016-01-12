import urllib2
import sys
from pprint import pprint

import sys, getopt


def main(argv):
	log = open("phtml.html", "wb")
	infile = 'http://www.google.com'
	
	ofile = ''
	try:
	  opts, args = getopt.getopt(argv, "hi:",["ifile=","ofile="])
	except getopt.GetoptError:
		print 'pGetPage.py -i <url>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'pGetPage.py -i <url>'
			sys.exit()
		elif opt in ("-i", "--ifile"):
			infile = str(sys.argv[2])
	print ' Requested URL Is  :', infile
	req = urllib2.Request(infile);
	#'http://www.voidspace.org.uk');
	response = urllib2.urlopen(req)
	
	the_page = response.read().decode('utf-8')
	##print(the_page)
	print >> log,the_page
	#pprint(the_page)
	##print(the_page, file = log)
	log.close()
	

if __name__=="__main__":
	main(sys.argv[1:])

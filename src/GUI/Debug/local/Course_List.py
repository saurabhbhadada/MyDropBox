from urllib2 import urlopen
from HTMLParser import HTMLParser

entry = raw_input("Entry no.? ");

prefix = "http://ldap1.iitd.ernet.in/LDAP/courses/"
resp = urlopen(prefix + 'gpaliases.html');
html = resp.read();
links = {}
courses = []
found = False

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    temp = ""
    recording = 0
    
    def handle_starttag(self, tag, attrs):
        if(tag == 'a'):
            self.recording = 1
            
            for name,val in attrs:
                if name=='href':
                    self.temp = val
                    break;

            #print "Encountered a start tag:", tag    
        
    def handle_endtag(self, tag):
        if(tag == 'a' and self.recording == 1):
            self.recording = 0
        #print "Encountered an end tag :", tag

    def handle_data(self, data):
        if(self.recording == 1):
            links[data] = self.temp
            
        #print "Encountered some data  :", data

class CourseHTMLParser(HTMLParser):
    def handle_data(self, data):
        global found
        
        if(data == entry):
            found = True;
            #print "found"
        
        #print data, entry
        #print (data == entry)

# instantiate the parser and fed it some HTML
parser = MyHTMLParser()
parser.feed(html);

# Got the links, init parsing within links
for name,link in links.items():
    found = False
    #print "Quering",link
    
    resp = urlopen(prefix + link);
    html = resp.read();

    parser2 = CourseHTMLParser()
    parser2.feed(html);

    #print found;
    if(found == True):
        courses.append(name)
        print "Person enrolled in " + name;
    

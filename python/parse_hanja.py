#!/usr/bin/env python


from HTMLParser import HTMLParser

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.mc = {}
        self.mv = []
        self.script_found = False
        self.hanja_found = False
        self.um_found = False
        self.start_hanja = False
        self.stroke_found = False
        self.hangul = ""
        self.hanja = ""
        self.um = ""
        self.stroke = ""
 
    def reset_flags(self):
        self.script_found = False
        self.hanja_found = False
        self.um_found = False
        self.start_hanja = False
        self.stroke_found = False
        self.hangul = ""
        self.hanja = ""
        self.um = ""
        self.stroke = ""
        self.mv = []
  
    def handle_starttag(self, tag, attrs):
        if tag == 'script':
            self.script_found = True
        elif tag == 'dt' and attrs != []:
            self.hanja_found = True
            self.start_hanja = True
        elif tag == 'span' and self.start_hanja:
            self.um_found = True
        elif tag == 'br' and self.start_hanja:
            self.stroke_found = True

    def handle_endtag(self, tag):
        pass

    def handle_data(self, data):
        if self.script_found:
            self.get_hangul(data)
            self.script_found = False
        elif self.hanja_found:
            self.get_hanja(data)
            self.hanja_found = False
        elif self.um_found:
            self.get_um(data)
            self.um_found = False
        elif self.stroke_found:
            self.get_stroke(data)
            self.start_hanja = False
            self.stroke_found = False
            self.mv.append((self.hanja, self.um, self.stroke))

    def get_hangul(self, data):
        index = data.find('value:')
        hangul = data[index + 7: index + 10]
        if (len(hangul) != 3):
            return
        
        self.hangul = hangul

    def get_hanja(self, data):
        if (len(data) != 3):
            self.hanja = "NA"
        else:
            self.hanja =  data

    def get_um(self, data):
        self.um =  data

    def get_stroke(self, data):
        r = str(int(data[-8:-6]))
        self.stroke = r


# instantiate the parser and fed it some HTML
parser = MyHTMLParser()

def process_file(file_name):
    parser.reset_flags()
    s = ''
    with open(file_name, "r") as rf:
        s = rf.read()

    parser.feed(s);
    m = parser.mc.get(parser.hangul)
    if m is None:
        parser.mc[parser.hangul] =  parser.mv
    else:
        parser.mc[parser.hangul] = m + parser.mv

if __name__ == '__main__':
    for i in range (555):
        process_file(str(i) + '.txt')
    for i in range (45):
        if i == 0 or i == 9:
            continue
        process_file('a-' + str(i) + '.html')
    for k in parser.mc:
        print "***" + k
        for e in parser.mc[k]:
            print "%s:%s:%s" %e
    print 'Done'



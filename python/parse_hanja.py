#!/usr/bin/env python


from HTMLParser import HTMLParser

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.script_found = False
        self.hanja_found = False

    def handle_starttag(self, tag, attrs):
        if tag == 'script':
            self.script_found = True
        elif tag == 'dt' and attrs != []:
            self.hanja_found = True

    def handle_endtag(self, tag):
        pass

    def handle_data(self, data):
        if self.script_found:
            self.get_hangul(data)
            self.script_found = False
        elif self.hanja_found:
            self.get_hanja(data)
            self.hanja_found = False

    def get_hangul(self, data):
        index = data.find('value:')
        hangul = data[index + 7: index + 10]
        print hangul

    def get_hanja(self, data):
        print data


def process_file(file_name):
    
    # instantiate the parser and fed it some HTML
    parser = MyHTMLParser()

    s = ''
    with open(file_name, "r") as rf:
        s = rf.read()

    parser.feed(s);

if __name__ == '__main__':
    process_file('3.txt')
    print 'Done'



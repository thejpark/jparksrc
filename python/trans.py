#!/usr/bin/env python

import urllib
import urllib2
import threading
import time

def load():
    r = ''
    with open('final.txt', 'r') as rf:
        for line in rf:
            if line[:3] == '***':
                r += ']\n'
                r += '"' + line[3:-1] + '":['
            else:
                s = line.split(':')
                if len(s) == 3:
                    r += '("' + s[0] + '","' + s[1] + '",' + s[2][:-1] + '),\n'
                else:
                    print 'parsing error at line'
                    print line
                    return

    return r

if __name__ == '__main__':
    l = load()

    print l


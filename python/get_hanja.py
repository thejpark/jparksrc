#!/usr/bin/env python

import urllib
import urllib2
import threading
import time

def load():
    r = {}
    with open('rf.txt', 'r') as rf:
        for line in rf:
            s = line.split(':', 1)
            r[s[0]] = s[1]

    return r

def get(k, i):
    url = 'http://www.miso.co.kr/main/resource/hanja'
    values = {}
    values['word'] = k
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data)
    response = urllib2.urlopen(req)
    the_page = response.read()

    fname = str(i) + '.txt'
    with open(fname, 'w') as wf:
        for line in the_page:
            wf.write(line)

if __name__ == '__main__':
    kv = load()
    i = 0
    for k in kv:
        get(k, i)
        i = i + 1
        time.sleep(60 * 2)

    print 'Done'


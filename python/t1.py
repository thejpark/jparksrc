#file t1.py
'''
Module __doc__ string
this is my test python file
'''

def foo(a, b):
    return a + b


def bar(c):
    return c + 1

class base:
    def foo(self, a):
        return a + 2
        

def print10():
    for i in range(10):
        print i


def askname():
    name = raw_input('name?')
    print name

def print10():
    n = range(10)
    for x in n[:-2]:
        print x


def test110():
    for el in range(-10, 110):
        exec('x = %d' %el)
        exec('y = %d' %el)
        print el, x is y


from decimal import *


def printAccurate():
    e = Decimal('0.0')
    delta = Decimal('0.00001')
    for k in range(100000):
        e += delta
    print e


def printInAccurate():
    e = 0.0
    delta = 0.00001
    for k in range(100000):
        e += delta
    print e


def striptest():
    n = '   spam and ham   '
    print 'before: ', n
    print 'after : ', n.strip()

def splittest():
    s = '''
    first line
    seconds line
    third line'''

    n = s.splitlines();
    n.remove('')
    r = []
    for e in n:
        r.append(e.strip())

    k = ':'.join(r)
    print k

def unicodetest():
    "this is unicode test"
    print u'Spam \uB610 Egg'
    print u'Spam and Egg'
    x = 'a' + u'bc' == u'abc'
    print x
    print ord('A')
    print chr(65)
    h =  '한글과 세종대왕'
    print h, len(h)


    
    
def splittest1():
    n = 'this/is/a/directory'
    s = n.split('/')
    for e in s:
        print e


def splittest2():
    n = 'this/is/a/directory'
    s = n.rsplit('/', 1)
    print s

def replacetest1():
    n = 'a123.'
    for c in n:
        if c.isalpha():
            n.replace(c, "")
    # n is immutable, so it is still same. replace does not change original string.
    print n


def replacetest2():
    n = 'a123.'
    r = ''
    for c in n:
        if not c.isalpha():
            r += c
    print r


def fastconcattest():
    t = []
    for k in range(100000):
        t.append('spam')
    s = ''.join(t)

def slowconcattest():
    s = ''
    for k in range(100000):
        s += 'spam'


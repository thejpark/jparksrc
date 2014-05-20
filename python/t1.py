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


def badorgood():
    # bad
    my_container = ['Larry', 'Moe', 'Curly']
    index = 0
    for element in my_container:
        print ('{} {}'.format(index, element))
        index += 1
    # good
    my_container = ['Larry', 'Moe', 'Curly']
    for index, element in enumerate(my_container):
        print ('{} {}'.format(index, element))

    foo, bar = (1, 2)
    # bad
    temp = foo
    foo = bar
    bar = temp

    #good
    (foo, bar) = (bar, foo)

    #bad
    list_from_comma_separated_value_file = ['dog', 'Fido', 10] 
    animal = list_from_comma_separated_value_file[0]
    name = list_from_comma_separated_value_file[1]
    age = list_from_comma_separated_value_file[2]

    #good
    list_from_comma_separated_value_file = ['dog', 'Fido', 10] 
    (animal, name, age) = list_from_comma_separated_value_file

    #bad
    result_list = ['True', 'False', 'File not found']
    result_string = ''
    for result in result_list:
        result_string += result

    #good
    result_list = ['True', 'False', 'File not found']
    result_string = ''.join(result_list)

    #bad
    # log_severity = None
    # if 'severity' in configuration:
    #     log_severity = configuration['severity']
    # else:
    #     log_severity = log.Info

    #good
    # log_severity = configuration.get('severity', log.Info)

    #bad
    # file_handle = open(path_to_file, 'r')
    # for line in file_handle.readlines():
    #     if some_function_that_throws_exceptions(line):
    #         # do something
    # file_handle.close()

    #good
    # with open(path_to_file, 'r') as file_handle:
    #     for line in file_handle:
    #         if some_function_that_throws_exceptions(line):
    #             # do something
    # No need to explicitly call 'close'. Handled by the File context manager

    #bad
    if name == 'Tom' or name == 'Dick' or name == 'Harry':
        is_generic_name = True

    #good
    if name in ('Tom', 'Dick', 'Harry'):
        is_generic_name = True

    #bad
    some_other_list = range(1, 100)
    my_weird_list_of_numbers = list()
    for element in some_other_list:
        if (element % 3) == 0:
            my_weird_list_of_numbers.append(element+5)

    #good
    some_other_list = range(1, 100)
    my_weird_list_of_numbers = [element + 5 for element in some_other_list if (element % 3) == 0]

    #bad
    my_list = ['Larry', 'Moe', 'Curly']
    index = 0
    while index < len(my_list):
        print (my_list[index])
        index+=1

    #good
    my_list = ['Larry', 'Moe', 'Curly']
    for element in my_list:
        print element

#!/usr/bin/env python

# the above makes python script

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


# generator
# http://www.jeffknupp.com/blog/2013/04/07/improve-your-python-yield-and-generators-explained/

#decorator
#http://www.jeffknupp.com/blog/2013/11/29/improve-your-python-decorators-explained/

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


# https://docs.python.org/2/library/subprocess.html
# Use subprocess module instead of os wrapper (fork, etc) because it is much simpler.
# The child process receives the same SIGINT as your parent process because it's in the same process group. You can put the child in its own process group by calling os.setpgrp() in the child process. Popen's preexec_fn argument is useful here:

# subprocess.Popen(['nohup', 'my_command'],
#                  stdout=open('/dev/null', 'w'),
#                  stderr=open('logfile.log', 'a'),
#                  preexec_fn=os.setpgrp
#                  )
# (preexec_fn is for un*x-oids only. There appears to be a rough equivalent for Windows "creationflags=CREATE_NEW_PROCESS_GROUP", but I've never tried it.)

# subprocess.check_output provide output of the program in string format.


# example of using pexpect
# # This connects to the openbsd ftp site and
# # downloads the recursive directory listing.
# import pexpect
# child = pexpect.spawn('ftp ftp.openbsd.org')
# child.expect('Name .*: ')
# child.sendline('anonymous')
# child.expect('Password:')
# child.sendline('noah@example.com')
# child.expect('ftp> ')
# child.sendline('lcd /tmp')
# child.expect('ftp> ')
# child.sendline('cd pub')
# child.expect('ftp> ')
# child.sendline('get README')
# child.expect('ftp> ')
# child.sendline('bye')


# main and argument. sys.argv also provides access to arguments of the python script

def main():
    return 0

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="A tool",
        epilog="EX: A -cp COM5 cam.ufb",
        formatter_class=argparse.RawDescriptionHelpFormatter)

    parser.add_argument("-cp", dest="num_port",
                        default="4",
                        help="port number (defaults to 4)")

    parser.add_argument("-ft", dest="file_type",
                        default="0",
                        help="Not used on CAM upgrade utility")

    parser.add_argument("-fgt", dest="fg_type",
                        default="0",
                        help="Not used on CAM upgrade utility")

    parser.add_argument("-r", "--data-rate", dest="data_rate",
                        default=DEFAULT_TX_RATE_BYTES_PER_SECOND, type=int,
                        help="TX data rates in bytes per second")

    parser.add_argument("-v", "--verbose", dest="verbose", action="store_true",
                        help="Show debug information")

    parser.add_argument("upgrade_file_name")

    main_args = parser.parse_args()
    # you can call main directly. or do this to check return code using 'echo $?'
    sys.exit(main())


# python args (list arguments) and kwargs(dictionary arguments) are always used
# in callee/caller as *args and **kwargs.



# list also have count method to get the number of elements in the list.
a = [1, 2, 3]
b = [e * 2 for e in a]

isinstance(1, int)
type(1)
int(1.0)

#list operations
# extend, append, +, index, del, insert, remove, pop
# ... or you can use 'in' to check
# whether item is in the list

# string, tuple are not mutable. So if you need constant than you can use
# tuple

# set can be created using list. a = {} makes a as a dictionary type not set.
a_set = set([1, 2, 3])
a_set = set()
# set has add and update method to add elements. remove , discard, pop, and clear will delete elements in the set
# set has union, intersection, difference, symmetric_difference
# issubset and issuperset check subset

# construct a path name
import os
x = os.path.join(os.path.expanduser('~'), 'a', 'b', 'c.txt')
dirname, file = os.path.split(x)
name, ext = os.path.splitext(file)

# get directory list or file list
import glob
glob.glob('*')

# find all files (absolute path) having .txt extensin.
[os.path.realpath(e) for e in glob.glob('*.txt')]

# find file with ext and size
[f for f in glob.glob('*.py') if os.stat(f).st_size > 6000]

#os.path.realpath(filename) gives absolute path (with  filemame)


# python book: dive into python
# http://getpython3.com/diveintopython3/your-first-python-program.html



# how to add python module search path?

# sys.path shows current search path in list, and
# sys.path.insert(0, some_path) will insert a new one


# ''' is for multiline string
s = '한글'
len(s)
# in python3 it will return 2, but in 2.7 it will return 6


# PEP 3101: Advanced String Formatting, “The rules for parsing an item key are
# very simple. If it starts with a digit, then it is treated as a number,
# otherwise it is used as a string.
s = ['a', 'b']
x = {'key', 'val'}
'sample test {0[0]} and {1[key]}'.format(s, x)

# string related methods: split, splitlines. split('=', 1) means use '=' for split,
# but split only once.


# if you want mutable string, use bytearray method (similar to stringbuffer)
s = 'abc'
b = bytearray(s)
b[0] = 'c'

# bytes objects have a decode() method that takes a character encoding
# and returns a string, and strings have an encode() method that takes
# a character encoding and returns a bytes object


# print key/value of dictionary
x = {'a': 1, 'b': 2}
for k, v in x.iteritems():
    print k, v

#
#
# using re
#
#
#
import re

s = 'U72 8-10 Boundary ROAD'
re.sub('ROAD$', 'RD', s)
# \b means word boundary. So the following is much stronger as it just replace
# ROAD regardless of its position (only if it is its own)
re.sub(r'\bROAD\b', 'RD.', s)
# r prefix before string makes raw sring.
# python need to escape the escape character itself, so it is
re.sub('\\bROAD\\b', 'RD.', s)

#when working with re, use raw string. It is simpler

s = r'\bWord\b'
>>> s
'\\bWord\\b'
>>> repr(s)
"'\\\\bWord\\\\b'"

pattern = '^(a? | b)$'
# a? means optionally match single a.
re.search(pattern, 'abc')

# The followgin patter, {0, 3}  means 0 ~ 3 Ms
pattern = '^M{0,3}$'
# equal to ^M?M?M?$

# \d means digit, \d{3} is any 3 digits
# phonePattern = re.compile(r'^(\d{3})-(\d{3})-(\d{4})$')
# phonePattern.search('800-555-1212').groups()
# ('800', '555', '1212')


# The square brackets mean “match exactly one of these characters.
# So [sxz] means “s, or x, or z”, but only one of them.

# The ^ as the first character inside the square brackets means
# something special: negation. [^abc] means “any single character except a, b, or c
def plural(noun):
    if re.search('[sxz]$', noun):
        return re.sub('$', 'es', noun)
    elif re.search('[^aeioudgkprt]h$', noun):
        return re.sub('$', 'es', noun)
    elif re.search('[^aeiou]y$', noun):
        return re.sub('y$', 'ies', noun)
    else:
        return noun + 's'

# import matplotlib.pyplot as plt
# plt.plot([1,2,3,4,3,2,1]) plt.show()


# match and apply method hand in hand
def match_sxz(noun):
    return re.search('[sxz]$', noun)

def apply_sxz(noun):
    return re.sub('$', 'es', noun)

def match_h(noun):
    return re.search('[^aeioudgkprt]h$', noun)

def apply_h(noun):
    return re.sub('$', 'es', noun)

def match_y(noun):
    return re.search('[^aeiou]y$', noun)

def apply_y(noun):
    return re.sub('y$', 'ies', noun)

def match_default(noun):
    return True

def apply_default(noun):
    return noun + 's'

rules = ((match_sxz, apply_sxz),
         (match_h, apply_h),
         (match_y, apply_y),
         (match_default, apply_default)
         )

#plural function is now simplified. more extensible.

def plural(noun):
    for matches_rule, apply_rule in rules:
        if matches_rule(noun):
            return apply_rule(noun)



# a solution to create rules using pattern list
patterns = \
  (
    ('[sxz]$',           '$',  'es'),
    ('[^aeioudgkprt]h$', '$',  'es'),
    ('(qu|[^aeiou])y$',  'y$', 'ies'),
    ('$',                '$',  's')
  )
rules = [build_match_and_apply_functions(pattern, search, replace)
         for (pattern, search, replace) in patterns]

def build_match_and_apply_functions(pattern, search, replace):
    def matches_rule(word):
        return re.search(pattern, word)
    def apply_rule(word):
        return re.sub(search, replace, word)
    return (matches_rule, apply_rule)

# we can use the same plural functgion
#
# def plural(noun):
#     for matches_rule, apply_rule in rules:
#         if matches_rule(noun):
#             return apply_rule(noun)


# use a file to store pattern
with open('plural4-rules.txt', encoding='utf-8') as pattern_file:
    for line in pattern_file:
        pattern, search, replace = line.split(None, 3)
        rules.append(build_match_and_apply_functions(
                pattern, search, replace))


#
#
# A fibonacci generator
#
#
def fib(max):
    a, b = 0, 1          
    while a < max:
        yield a          
        a, b = b, a + b  


# how to use?
for n in fib(1000):
    print(n, end=' ')



# Fib class implemented as an iterator
class Fib:                  
    def __init__(self, max):
        self.max = max

    # this initialises iteration, when someone calls iter() method (i.e., for loop)
    def __iter__(self):     
        self.a = 0
        self.b = 1
        return self

    # this is called for every loop, when someone calls next() method
    def __next__(self):     
        fib = self.a
        if fib > self.max:
            raise StopIteration                  
        self.a, self.b = self.b, self.a + self.b
        return fib   

for n in Fib(1000):
    print(n, end=' ')


# class variable and instance varialbe

class A:
    name = 'A'
    def __init__(self):
        pass
    def foo(self, x):
        return x + 1

a = A()
a.name   ---> 'A'

# add instance variable 'name' to a. This is differnt from class variable.
a.name = 'a'

>>> a.name
>>> 'a'

# why? lexical scoping. 
# when we read a variable, if there is no instance variable, then python will 
# look up the name in the class level. This is same as function or method. 
# if we define a method in a class, that method is defined in a class level.
# so, if we call a method in an instance, because there is no such method for
# the instance, python look up the method in the class level.
# in the class level, we should use 'self' to access instances. So python
# probably replace that instance.func(x) with func(instance, x) defined in the
# class. But you can add func (just a normal function not accessing self 
# like this:


>>> a.foo(1)
>>> 2
# add a method to a
a.foo =  lambda x: x + 2

>>> a.foo(1) 
>>> 3


# you can change the definition of foo in the class level:
a.__class__.foo = lambda self, x: x  + 10


# simple map-reduce in python
# http://mikecvet.wordpress.com/2010/07/02/parallel-mapreduce-in-python/

# simple map-reduce test
a = [1, 2, 3]
b = [4, 5, 6, 7]
c = [8, 9, 1, 2, 3]
L = map(lambda x:len(x), [a, b, c])
 
# L == [3, 4, 5]
N = reduce(lambda x, y: x+y, L)
# N == 12
# Or, if we want to be fancy and do it in one line
N = reduce(lambda x, y: x+y, map(lambda x:len(x), [a, b, c]))


# sorted
student_objects = [
        Student('john', 'A', 15),
        Student('jane', 'B', 12),
        Student('dave', 'B', 10),
]
>>> sorted(student_objects, key=lambda student: student.age)   # sort by age
[('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]


# sort works for list, but sorted works other container (i.e., dictionary) as well.
# sort mutate, but sorted create a new 
# use can add comparer like list.sort(comparer) 

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
    def __init__(self, x):
        self.val = x

    def foo(self, a):
        return a + self.val


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


# string.lstrip deletes left most delimeter
# string.rstrip deletes right most delimeter
>>> s = 'this is \n'
>>> s.rstrip()
'this is'
>>> s = 'this is'
>>> s.rstrip()
'this is'

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

# https://docs.quantifiedcode.com/python-anti-patterns/

def badorgood():
    # using global is bad

    #using wild card import is bad
    # from math import *

    # good if import is more specific
    # from math import ceil

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

    #bad because function returns multiple type
    def bad_get_secret_code(password):
        if password != "bicycle":
            return None
        else:
            return "42"

    def get_secret_code(password):
        if password != "bicycle":
            raise ValueError
        else:
            return "42"

    # bad
    # Not using else where appropriate in a loop
    l = [1, 2, 3]
    magic_number = 4
    found = False

    for n in l:
        if n == magic_number:
            found = True
            print("Magic number found")
            break

    if not found:
        print("Magic number not found")

    #good
    l = [1, 2, 3]
    magic_number = 4

    for n in l:
        if n == magic_number:
            print("Magic number found")
            break
    else:
        print("Magic number not found")

    #bad
    #initialise key/val manually

    #good
    # Use defaultdict() to initialize dict keys
    from collections import defaultdict

    # every key automatically initializes to 6
    d = defaultdict(lambda : 6)
    d["k"] += 1

    print(d["k"])  # 7

    #bad - mutable default argument
    def append(number, number_list=[]):
        number_list.append(number)
        print(number_list)
        return number_list

    #good the keyword None is the sentinel value representing empty list
    def append(number, number_list=None):
        if number_list is None:
            number_list = []
        number_list.append(number)
        print(number_list)
        return number_list


# https://docs.python.org/2/library/subprocess.html
# Use subprocess module instead of os wrapper (fork, etc) because it is much simpler.
# The child process receives the same SIGINT as your parent process because it's
# in the same process group. You can put the child in its own process group by
# calling os.setpgrp() in the child process. Popen's preexec_fn argument is useful here:

# subprocess.Popen(['nohup', 'my_command'],
#                  stdout=open('/dev/null', 'w'),
#                  stderr=open('logfile.log', 'a'),
#                  preexec_fn=os.setpgrp
#                  )
# (preexec_fn is for un*x-oids only. There appears to be a rough equivalent for
# Windows "creationflags=CREATE_NEW_PROCESS_GROUP", but I've never tried it.)

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

#other way

for e in x:
    print e, x[e]



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



# implement __str__ to give something like toString in Java

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


# an empty class
class a: pass

# decorator
# @decorator
# def foo():
#    pass
#
# is equal to foo = decorator(foo)
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


# assert len(unique_characters) <= 10, 'Too many letters'
#
# is equivalent to
#
# if len(unique_characters) > 10:
#    raise AssertionError('Too many letters')


>>> [chr(c) for c in [69, 70, 71]]
['E', 'F', 'G']
>>> g = chr(c) for c in [69, 70, 71]
#generator expression. This is more compact than generator function.
>>> g = (chr(c) for c in [69, 70, 71])
>>> g
<generator object <genexpr> at 0xffee1234>
>>> next(g)
'E'
>>> next(g)
'F'
>>> next(g)
'G'


# using generator function
>>> def chr_map(a):
...     for c in a:
...         yield chr(c)
...
>>> chr_map([69, 70, 71])
<generator object chr_map at 0xffee11e4>
>>> g = chr_map([69, 70, 71])
>>> next(g)
'E'
>>> next(g)
'F'


# permutation tool
>>> import itertools
>>> perms = itertools.permutations([1, 2, 3], 2)
>>> next(perms)
(1, 2)
>>> next(perms)
(1, 3)
>>> next(perms)
(2, 1)
>>> next(perms)
(2, 3)
>>> next(perms)
(3, 1)
>>> next(perms)
(3, 2)
>>> next(perms)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration

# try this
>>> list(itertools.permutations('ABC', 3))
>>> list(itertools.product('ABC', '123'))


>>> names = ['Alex', 'Anne', 'Chris', 'Dora', 'Ethan']
>>> for length, iter in groups:
...     print('names with {0:d} letters:'.format(length))
...     for name in iter:
...         print name
...
names with 5 letters:
Chris
names with 4 letters:
Dora
names with 5 letters:
Ethan

# The itertools.chain() function takes two iterators and returns an
# iterator that contains all the items from the first iterator, followed
# by all the items from the second iterator.

>>> list(zip(range(0, 3), range(10, 13)))
[(0, 10), (1, 11), (2, 12)]
>>> list(zip(range(0, 3), range(10, 14)))
[(0, 10), (1, 11), (2, 12)]
>>> list(itertools.zip_longest(range(0, 3), range(10, 14)))
[(0, 10), (1, 11), (2, 12), (None, 13)]
>>> list(zip([1, 2, 3], ['a', 'b', 'c']))
[(1, 'a'), (2, 'b'), (3, 'c')]
>>> dict(zip([1, 2, 3], ['a', 'b', 'c']))
{1: 'a', 2: 'b', 3: 'c'}


# another way of replace in string
>>> translation_table
{65: 79}
>>> 'MARK'.translate(translation_table)
'MORK'



# how to implement unittest case?

import unittest
class ToRomanBadInput(unittest.TestCase):
    def test_too_large(self):
        '''to_roman should fail with large input'''
        self.assertRaises(roman3.OutOfRangeError, roman3.to_roman, 4000)

# there is more assert methods like assertEqual(a, b)

<<<<<<< HEAD
line_number = 0
with open('examples/favorite-people.txt', encoding='utf-8') as a_file:
    for a_line in a_file:
        line_number += 1
        # The format specifier {:>4} means “print this argument right-justified
        # within 4 spaces.
        print('{:>4} {}'.format(line_number, a_line.rstrip()))

# io redirect emample

class RedirectStdoutTo:
    def __init__(self, out_new):
        self.out_new = out_new

    def __enter__(self):
        self.out_old = sys.stdout
        sys.stdout = self.out_new

    def __exit__(self, *args):
        sys.stdout = self.out_old

print('A')
with open('out.log', mode='w', encoding='utf-8') as a_file, RedirectStdoutTo(a_file):
    print('B')
print('C')
=======
# pickle is python serialization module. pickle.dump, pickle.load, etc.
# pickle has a method to store python object in json format.
# if the python object does not transformed to json, we need to define a method
# to do it.
# http://getpython3.com/diveintopython3/serializing.html

# why inherit object? such as 'class Studeny(object):'
# http://stackoverflow.com/questions/4015417/python-class-inherits-object
# Python 3.x:
# class MyClass(object): = new-style class
# class MyClass: = new-style class (implicitly inherits from object)

# Python 2.x:
# class MyClass(object): = new-style class
# class MyClass: = OLD-STYLE CLASS

# Explanation:

# When defining base classes in Python 3.x, you’re allowed to drop the object from
# the definition. However, this can open the door for a seriously hard to track problem…

# Python introduced new-style classes back in Python 2.2, and by now old-style
# classes are really quite old. Discussion of old-style classes is buried in the
# 2.x docs, and non-existent in the 3.x docs.

# The problem is, the syntax for old-style classes in Python 2.x is the same as
# the alternative syntax for new-style classes in Python 3.x. Python 2.x is still
# very widely used (e.g. GAE, Web2Py), and any code (or coder) unwittingly bringing
# 3.x-style class definitions into 2.x code is going to end up with some seriously
# outdated base objects. And because old-style classes aren’t on anyone’s radar,
# they likely won’t know what hit them.

# So just spell it out the long way and save some 2.x developer the tears.

# how to use filter

>>> def odd(n):                 1
...     return n % 2
...     
>>> li = [1, 2, 3, 5, 9, 10, 256, -3]
>>> filter(odd, li)             2
[1, 3, 5, 9, -3]
>>> [e for e in li if odd(e)]   3
>>> filteredList = []
>>> for n in li:                4
...     if odd(n):
...         filteredList.append(n)
...     
>>> filteredList
[1, 3, 5, 9, -3]


>>> def double(n):
...     return n*2
...     
>>> li = [1, 2, 3, 5, 9, 10, 256, -3]
>>> map(double, li)                       1
[2, 4, 6, 10, 18, 20, 512, -6]
>>> [double(n) for n in li]               2
[2, 4, 6, 10, 18, 20, 512, -6]
>>> newlist = []
>>> for n in li:                          3
...     newlist.append(double(n))
...     
>>> newlist
[2, 4, 6, 10, 18, 20, 512, -6]


# python equality comparison
>>> s1 = 'public'
>>> s2 = 'public'
>>> s2 is s1
True
>>> a = 'pub'
>>> b = ''.join(['p', 'u', 'b'])
>>> a == b
True
>>> a is b
False

# is is the id(a) == id(b)
# s is used for identity comparison, while == is used for equality comparison
# If you use is, the result will be true if and only if the object is the same
# object. However, == will be true any time the values of the object are the same.

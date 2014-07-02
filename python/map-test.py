#!/usr/bin/env python


from multiprocessing import Pool
import subprocess
import os

def foo(x):
    r = subprocess.Popen(['ls', '-la', '../{}'.format(x)])
    r.wait()

if __name__ == '__main__':
    p = Pool(2)
    print(p.map(foo, ['java', 'cpp']))

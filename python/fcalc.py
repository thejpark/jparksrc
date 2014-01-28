def dept(source, interest, momths):
    return months * source * interest


def dept_year(source, interest):
    return dept(source, interest, 12)

def kor_aus_src(source, ratio):
    return source * ratio

import random

def gen_rand_num(x, y):
    r = []
    random.seed()
    for i in range(0, x * y):
        r.append(random.randint(1, 45))
    for i in range(0, y):
        print(sorted(r[i * x: i * x + x]))

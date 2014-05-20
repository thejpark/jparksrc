def dept(source, interest, momths):
    return months * source * interest


def dept_year(source, interest):
    return dept(source, interest, 12)

def kor_aus_src(source, ratio):
    return source * ratio

import random

def gen_rand_num(x, y):
    random.seed()
    for i in range(0, y):
        r = []
        while len(r) is not x:
            k = random.randint(1, 45)
            if k not in r:
                r.append(k)
        print(sorted(r))

def dept(source, interest, momths):
    return months * source * interest


def dept_year(source, interest):
    return dept(source, interest, 12)

def compound(base, interest, months, contribution = 0):
    for i in range(months):
        base = base * (1.0 + interest)
        base = base + contribution
    return base


def get_comp_month(base, target, interest):
    i = 0
    while base < target :
        base = base * (1.0 + interest)
        i += 1
    return (i, base)


# much complicated.
# 
# def get_comp_interest(base, target, months):
#     return

def reverse_compound(target, interest, months):
    for i in range(months):
        target = target / (1.0 + interest)
    return target

def reverse_interest(sum, interest):
    return sum / interest


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

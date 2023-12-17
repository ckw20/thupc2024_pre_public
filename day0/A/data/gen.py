import yaml
import os
import random
import math
import numpy as np

datapath = os.path.dirname(__file__)
probpath = os.path.dirname(datapath)

def randomCategory(len, sum, weight = None):
    """
        Generate a random array of given length and sum
    """
    if weight == None:
        weight = [1] * len
    arr = random.choices(range(len), weights=weight, k = sum)
    from collections import Counter
    counter = Counter(arr)
    return [counter.get(i, 0) for i in range(len)]

np.random.seed(8889)
random.seed(8889)

with open(os.path.join(probpath, 'conf.yaml'), mode='r', encoding='UTF-8') as f:
    file = yaml.safe_load(f)

MAXN = file['args']['n']
CASEID = 0

def generate(arr):
    global CASEID
    CASEID = CASEID + 1
    with open("%d.in" % CASEID, "w") as f:
        f.write(str(len(arr)) + "\n")
        for index, elem in enumerate(arr):
            f.write(str(elem) + ("\n" if index == len(arr) - 1 else " "))
    os.system("std.exe < %d.in > %d.ans" % (CASEID, CASEID))
    print("Case %d Finished." % CASEID)

def randomdata(n):
    arr = list(range(1, n+1))
    random.shuffle(arr)
    generate(arr)
randomdata(1)
randomdata(2)
randomdata(3)
randomdata(10)

def special(n, sp):
    arr = list(range(1, n+1))
    if sp == 1:
        arr.reverse()
    elif sp >= 2 and sp <= 4:
        for index in range(sp - 1, n, sp):
            arr[index], arr[index - (sp - 1)] = arr[index - (sp - 1)], arr[index]
    generate(arr)

def random_rotate(n, num):
    arr = list(range(1, n+1))
    for _ in range(num):
        pos = None
        while pos == None:
            pos = random.choices(range(n), k=4)
            pos.sort()
            if pos[1] == pos[2]:
                pos = None
        i, j, k, l = pos
        arr = arr[:i] + arr[k: l + 1] + arr[j + 1: k] + arr[i: j + 1] + arr[l + 1:]
    generate(arr)

function_pot = [(lambda n, c=c: special(n, c)) for c in [0,1,2,3,4]] + [randomdata, randomdata, randomdata] + [(lambda n, c=c: random_rotate(n, num=c)) for c in [1, 5, 20, 100, 500, 1000, 1500]]
size_pot = [2000]

for size in size_pot:
    for function in function_pot:
        function(n= size - random.randint(0, int(math.sqrt(size))))
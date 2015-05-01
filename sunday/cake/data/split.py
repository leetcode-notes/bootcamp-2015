#!/usr/bin/env python3
from sys import stdin

k = int(stdin.readline())
for t in range(k):
#    assert(stdin.readline()=='\n')
    with open('split-3{}.in'.format(t),'w') as f:
        nstr = stdin.readline()
        print(nstr,file=f,end="")
        n = int(nstr.split()[2])
        for i in range(n):
            print(stdin.readline(),file=f,end="")

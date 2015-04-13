#!/usr/bin/env python3
from sys import stdin

k = int(stdin.readline())
for t in range(k):
    assert(stdin.readline()=='\n')
    with open('split-{}.in'.format(t),'w') as f:
        nstr = stdin.readline()
        print(nstr,file=f,end="")
        n = int(nstr)
        for i in range(n):
            print(stdin.readline(),file=f,end="")

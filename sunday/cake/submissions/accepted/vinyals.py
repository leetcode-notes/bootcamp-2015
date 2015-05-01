#!/usr/bin/env python3

from __future__ import print_function
from sys import stdin
from collections import defaultdict

p,q,n=map(int,stdin.readline().split())
roses=[tuple(map(int,stdin.readline().split())) for _ in range(n)]
ydict = defaultdict(list)
for (x,y) in roses:
    ydict[x].append(y)
xx = sorted(ydict.keys()) + [p+1]
for i,x in enumerate(xx[:-1]):
    startx = x if i else 1
    endx = xx[i+1]-1
    yy = sorted(ydict[x]) + [q+1]
    for j,y in enumerate(yy[:-1]):
        starty = y if j else 1
        endy = yy[j+1]-1
        print(startx,starty,endx,endy)
print(0)

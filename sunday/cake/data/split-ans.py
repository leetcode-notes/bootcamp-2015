#!/usr/bin/env python3
from sys import stdin
import sys

t=0
while(1):
    with open('split-3{}.ans'.format(t),'w') as f:
        while(1):
            nstr = stdin.readline()
            if (not nstr) : sys.exit(0)
            print(nstr,file=f,end="")
            if (nstr=='0\n'):
                t+=1
                break

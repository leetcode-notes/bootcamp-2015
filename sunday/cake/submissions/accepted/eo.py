p,q,n = map(int, raw_input().split())
xy = sorted([map(int, raw_input().split()) for i in range(n)])
a = 1
ai = 0
while ai < n:
    bi = ai
    while bi < n-1 and xy[bi][0] == xy[bi+1][0]:
        bi += 1
    c = a if bi < n-1 else p
    b = 1
    for i in range(ai, bi+1):
        d = xy[i][1] if i < bi else q
        print a,b,c,d
        b = d+1
    a += 1
    ai = bi+1
print 0

n = int(raw_input())
a = [int(r) for r in range(n) for r in raw_input().split()]
print sum(map(lambda l:sum(map(abs,map(sum,zip(sorted(l),range(-1,-n-1,-1))))),(a[0::2],a[1::2])))

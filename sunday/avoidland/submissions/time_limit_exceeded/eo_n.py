# O(n) solution. Works with a time limit of 5s
n = int(raw_input())
a = [0]*2*n
for l in range(n):
    x,y = map(int, raw_input().split())
    a[x-1] += 1
    a[n+y-1] += 1
print reduce(lambda x,y: (x[0]+1, x[1]+y, x[2]+abs(x[0]-x[1]-y)), a, (1,0,0))[2]

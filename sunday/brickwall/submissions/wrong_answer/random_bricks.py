import random
import time

def try_path(bricks, path):
    pos = 0
    while pos < len(path)-1:
        choices = []
        for i in range(3):
            if bricks[i] and pos+i+1 < len(path) and path[pos+i+1]:
                choices.append(i)
        if not choices:
            return False
        b = choices[random.randrange(len(choices))]
        pos += b+1
        bricks[b] -= 1
    return True

START_TIME = time.time()
TIME_LIMIT = 1.0

N,c1,c2,c3 = map(int, raw_input().split())
b = map(int, raw_input().split())
path = [True]
for brick in b:
    for i in range(brick-1):
        path.append(True)
    path.append(False)
path[-1] = True
good = False
while time.time() - START_TIME < (test+1)*TIME_SPLIT:
    if try_path([c1,c2,c3], path):
        good = True
        break
print "YES" if good else "NO"

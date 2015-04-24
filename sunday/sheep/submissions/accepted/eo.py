import math

def test_radius(r, sides):
    a = 0
    for side in sides:
        a += math.acos(1-(side**2/(2*r**2)))
    return a

def solve(sides):
    if len(sides) < 3:
        return 0
    if test_radius(sides[-1]/2, sides) >= 2*math.pi:
        # Whole circle covered
        t = sum(sides)
        lo = sides[-1]/2
        hi = t/4
        for i in range(50):
            mid = (lo+hi)/2
            if test_radius(mid, sides) < 2*math.pi:
                hi = mid
            else:
                lo = mid
        r = lo
        A = 0
        for side in sides:
            p = (side+2*r)/2
            A += math.sqrt(p*abs(p-r)*abs(p-r)*abs(p-side))
        return A
    else:
        # Circle party covered
        lo = sides[-1]/2
        hi = 1000000
        for i in range(50):
            mid = (lo+hi)/2
            if test_radius(mid, sides[:-1]) <= test_radius(mid, sides[-1:]):
                lo = mid
            else:
                hi = mid
        r = lo
        A = 0
        for side in sides[:-1]:
            p = (side+2*r)/2
            A += math.sqrt(p*abs(p-r)*abs(p-r)*abs(p-side))
        for side in sides[-1:]:
            p = (side+2*r)/2
            A -= math.sqrt(p*abs(p-r)*abs(p-r)*abs(p-side))
        return A

k = int(raw_input())
for test in range(k):
    sides = sorted(map(float, raw_input().split())[1:])
    while sides and sides[-1] >= sum(sides[:-1]):
        sides.pop()
    res = solve(sides)
    if sides:
        sides.pop()
    res = max(res, solve(sides))
    print res

import bisect

n, q = map(int, input().split())

mileage = list(map(int, input().split()))
mileage.sort()

for _ in range(q):
    m = int(input())

    idx = bisect.bisect_left(mileage, m)

    if idx != n and m == mileage[idx]:
        print(idx * (n - idx - 1))
    else:
        print(0)
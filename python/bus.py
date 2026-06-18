#통근버스 출발순서 검증하기

import sys

n = int(input())
a = list(map(int, input().split()))

total = 0

for i in range(n):
    more = 0

    for k in range(i + 1, n):
        if a[i] < a[k]:
            more += 1
        else:
            total += more

print(total)
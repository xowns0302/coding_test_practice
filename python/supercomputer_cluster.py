#슈퍼컴퓨터 클러스터

import sys

input = sys.stdin.readline

n, b = map(int, input().split())
a = list(map(int, input().split()))

def test(x):
    cost = 0

    for i in range(n):
        if a[i] < x:
            cost += (x - a[i]) * (x - a[i])

    return cost <= b


low = 1
high = 2 * 10 ** 9

while low <= high:
    mid = (low + high) // 2

    if test(mid):
        low = mid + 1
    else:
        high = mid - 1

print(high)
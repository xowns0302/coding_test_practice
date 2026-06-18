#성적 평가

import sys

n = int(input())
total = [0] * n

def computeRanking(arr):
    ranking = [0] * n
    ans = [0] * n

    for i in range(n):
        arr[i] = [arr[i], i]

    arr.sort(reverse=True)

    cnt = 1
    ranking[0] = 1

    for i in range(1, n):
        if arr[i][0] != arr[i - 1][0]:
            cnt = i + 1
        ranking[i] = cnt

    for i in range(n):
        ans[arr[i][1]] = ranking[i]

    for i in range(n):
        print(ans[i], end=' ')
    print()

for _ in range(3):
    scores = list(map(int, input().split()))

    for i in range(n):
        total[i] += scores[i]

    computeRanking(scores)

computeRanking(total)
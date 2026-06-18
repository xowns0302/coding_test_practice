#트럭


import sys

input = sys.stdin.readline

N = int(input())
offers = []  # [size, payment, buyer_id]

for buyer_id in range(N):
    data = list(map(int, input().split()))
    A = data[0]

    for j in range(A):
        size = data[2 * j + 1]
        payment = data[2 * j + 2]
        offers.append((size, payment, buyer_id))

M = int(input())
Q = list(map(int, input().split()))

queries = []
for i in range(M):
    queries.append((Q[i], i))  # [목표 매출, 원래 인덱스]

offers.sort()
queries.sort()

best_payment = [0] * N
revenue = 0
answer = [-1] * M

q_idx = 0

for size, payment, buyer_id in offers:
    if payment > best_payment[buyer_id]:
        revenue += payment - best_payment[buyer_id]
        best_payment[buyer_id] = payment

    while q_idx < M and queries[q_idx][0] <= revenue:
        original_idx = queries[q_idx][1]
        answer[original_idx] = size
        q_idx += 1

print(*answer)
#교차로

from collections import deque

n = int(input())

car = []
for i in range(n):
    t, d = input().split()
    car.append([i, int(t), d])

ans = [-1] * n
deq = [deque() for _ in range(4)]

counter = 0
carIdx = 0

while counter <= 1000000000:
    if carIdx >= n:
        empty = True
        for i in range(4):
            if deq[i]:
                empty = False
                break

        if empty:
            break

    if carIdx < n and deq[0] == deque() and deq[1] == deque() and deq[2] == deque() and deq[3] == deque():
        counter = max(counter, car[carIdx][1])

    tempCar = car[carIdx] if carIdx < n else None

    while carIdx < n and tempCar[1] <= counter:
        if tempCar[2] == 'A':
            deq[0].append(tempCar)
        elif tempCar[2] == 'B':
            deq[1].append(tempCar)
        elif tempCar[2] == 'C':
            deq[2].append(tempCar)
        else:
            deq[3].append(tempCar)

        carIdx += 1

        if carIdx < n:
            tempCar = car[carIdx]

    if deq[0] and deq[1] and deq[2] and deq[3]:
        break

    if not deq[0] and not deq[1] and not deq[2] and not deq[3]:
        continue

    outCar = []

    for i in range(4):
        if deq[i] and not deq[(i - 1) % 4]:
            outCar.append(i)

    for i in outCar:
        number, time, direction = deq[i].popleft()
        ans[number] = counter

    counter += 1

for i in range(n):
    print(ans[i])
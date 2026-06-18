#업무처리

import sys

def merge(lst1, lst2):
    lst = []
    for i in range(len(lst1)):
        lst.append(lst1[i])
        lst.append(lst2[i])
    return lst

h, k, r = map(int, input().split())

tasks = []
for _ in range(2 ** h):
    tasks.append(list(map(int, input().split())))

for i in range(1, h + 1):
    tasks2 = []
    for j in range(2 ** (h - i)):
        if j % 2:
            tasks2.append(merge(tasks[2 * j + 1], tasks[2 * j]))
        else:
            tasks2.append(merge(tasks[2 * j], tasks[2 * j + 1]))
    tasks = tasks2

answer = sum(tasks[0][:max(0, r - h)])

print(answer)
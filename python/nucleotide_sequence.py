#염기서열 커버

import sys

n, m = map(int, input().split())

dna = []
for _ in range(n):
    dna.append(list(input()))

superDNA = [None for _ in range(2 ** n)]
superDNA[0] = ['.'] * m

def merge(dna1, dna2):
    if dna1 == [] or dna2 == []:
        return []

    dna = []
    for i in range(m):
        if dna1[i] == '.':
            dna.append(dna2[i])
        elif dna2[i] == '.':
            dna.append(dna1[i])
        elif dna1[i] == dna2[i]:
            dna.append(dna1[i])
        else:
            return []
    return dna

def genSuperDNA(index):
    loc = 0
    tempIndex = index

    while tempIndex % 2 == 0:
        tempIndex = tempIndex // 2
        loc += 1

    superDNA[index] = merge(dna[loc], superDNA[index - 2 ** loc])

for i in range(1, 2 ** n):
    genSuperDNA(i)

answer = [n + 1] * (2 ** n)
answer[0] = 0

def genAnswer(index):
    if answer[index] != n + 1:
        return answer[index]

    bit = []
    number1 = number2 = 0
    tempIndex = index

    while tempIndex > 0:
        bit.append(tempIndex % 2)
        tempIndex = tempIndex // 2

    for i in range(len(bit)):
        if bit[i] == 1:
            number1 += 2 ** i

    while True:
        number2 = index - number1

        if superDNA[number1] != []:
            temp = genAnswer(number2) + 1
            if answer[index] > temp:
                answer[index] = temp

        number1 = (number1 - 1) & index

        if number1 == 0:
            break

    return answer[index]

print(genAnswer(2 ** n - 1))
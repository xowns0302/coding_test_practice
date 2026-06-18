#플레이페어 암호

import sys

def keyGen(keyString):
    keyString = keyString.replace('J', 'I')

    key = [[None for _ in range(5)] for _ in range(5)]
    keyPos = {}

    r, c = 0, 0

    for ch in keyString:
        if ch == 'J':
            ch = 'I'

        if ch not in keyPos:
            key[r][c] = ch
            keyPos[ch] = (r, c)

            c += 1
            if c == 5:
                r += 1
                c = 0

    for i in range(26):
        ch = chr(ord('A') + i)

        if ch == 'J':
            continue

        if ch not in keyPos:
            key[r][c] = ch
            keyPos[ch] = (r, c)

            c += 1
            if c == 5:
                r += 1
                c = 0

    return key, keyPos


def encode(first, second):
    rf, cf = keyPos[first]
    rs, cs = keyPos[second]

    if rf == rs:
        first = key[rf][(cf + 1) % 5]
        second = key[rs][(cs + 1) % 5]

    elif cf == cs:
        first = key[(rf + 1) % 5][cf]
        second = key[(rs + 1) % 5][cs]

    else:
        first = key[rf][cs]
        second = key[rs][cf]

    return first + second


def encrypt(msg):
    i = 0
    ans = []

    while i < len(msg):
        if i == len(msg) - 1:
            first = msg[i]
            second = 'X'
            i += 1

        else:
            first = msg[i]
            second = msg[i + 1]

            if first == second:
                if first == 'X':
                    second = 'Q'
                else:
                    second = 'X'
                i += 1
            else:
                i += 2

        ans.append(encode(first, second))

    return ''.join(ans)


msg = input().strip()
keyString = input().strip()

key, keyPos = keyGen(keyString)

cipherText = encrypt(msg)

print(cipherText)
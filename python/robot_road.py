#로봇이 지나간 경로


h, w = map(int, input().split())
matrix = [list(input()) for _ in range(h)]

directionMark = ['^', '<', 'v', '>']

dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]


def findDirection(x, y):
    count = 0
    direction = -1

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if 0 <= nx < h and 0 <= ny < w and matrix[nx][ny] == '#':
            direction = i
            count += 1

    return direction if count == 1 else -1


def findStart(matrix):
    startX = -1
    startY = -1
    startDir = -1

    for x in range(h):
        for y in range(w):
            if matrix[x][y] == '#':
                direction = findDirection(x, y)

                if direction != -1:
                    startX = x
                    startY = y
                    startDir = direction

    return startX, startY, startDir


def navigate(x, y, direction):
    prevDir = direction
    newDir = direction

    matrix[x][y] = '.'

    while True:
        while newDir == prevDir:
            print('A', end='')

            x = x + dx[newDir]
            y = y + dy[newDir]
            matrix[x][y] = '.'

            x = x + dx[newDir]
            y = y + dy[newDir]
            matrix[x][y] = '.'

            prevDir = newDir
            newDir = findDirection(x, y)

            if newDir == -1:
                return

        if (newDir - prevDir) % 4 == 1:
            print('L', end='')
        elif (newDir - prevDir) % 4 == 3:
            print('R', end='')

        prevDir = newDir


x, y, direction = findStart(matrix)

print(x + 1, y + 1)
print(directionMark[direction])
navigate(x, y, direction)
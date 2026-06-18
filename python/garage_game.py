#garage game


n = int(input())

garage = []
for _ in range(3 * n):
    garage.append(list(map(int, input().split())))

answer = 0

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]


def dfs(x, y, color, visit, cells):
    visit[x][y] = True
    cells.append((x, y))

    left = right = y
    top = bottom = x

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if 2 * n <= nx < 3 * n and 0 <= ny < n:
            if not visit[nx][ny] and garage[nx][ny] == color:
                l, r, t, b = dfs(nx, ny, color, visit, cells)
                left = min(left, l)
                right = max(right, r)
                top = min(top, t)
                bottom = max(bottom, b)

    return left, right, top, bottom


def remove(cells):
    for x, y in cells:
        garage[x][y] = 0


def fill():
    for col in range(n):
        temp = []

        for row in range(3 * n - 1, -1, -1):
            if garage[row][col] != 0:
                temp.append(garage[row][col])

        idx = 0
        for row in range(3 * n - 1, -1, -1):
            if idx < len(temp):
                garage[row][col] = temp[idx]
                idx += 1
            else:
                garage[row][col] = 0


def simulate(round, total):
    global answer, garage

    if round == 3:
        answer = max(answer, total)
        return

    visit = [[False for _ in range(n)] for _ in range(3 * n)]

    for x in range(2 * n, 3 * n):
        for y in range(n):
            if garage[x][y] == 0 or visit[x][y]:
                continue

            backup = [row[:] for row in garage]

            cells = []
            color = garage[x][y]

            left, right, top, bottom = dfs(x, y, color, visit, cells)

            count = len(cells)
            area = (right - left + 1) * (bottom - top + 1)

            remove(cells)
            fill()

            simulate(round + 1, total + count + area)

            garage = backup


simulate(0, 0)
print(answer)
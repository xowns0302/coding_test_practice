#안전운전을 도와줄 차세대 지능형 교통 시스템

n, t = map(int, input().split())

signal = []

for row in range(n):
    temp = []
    for col in range(n):
        temp.append(list(map(int, input().split())))
    signal.append(temp)

signalInfo = [[[0 for _ in range(4)] for _ in range(4)] for _ in range(13)]

signalInfo[1][0][1] = signalInfo[1][0][2] = signalInfo[1][0][3] = 1
signalInfo[2][1][0] = signalInfo[2][1][2] = signalInfo[2][1][3] = 1
signalInfo[3][2][0] = signalInfo[3][2][1] = signalInfo[3][2][3] = 1
signalInfo[4][3][0] = signalInfo[4][3][1] = signalInfo[4][3][2] = 1

for i in range(4):
    signalInfo[5 + i][i][(i + 1) % 4] = 1
    signalInfo[5 + i][i][(i + 2) % 4] = 1

for i in range(4):
    signalInfo[9 + i][i][(i + 2) % 4] = 1
    signalInfo[9 + i][i][(i + 3) % 4] = 1

junction = [[[0 for _ in range(4)] for _ in range(n)] for _ in range(n)]
junction2 = [[[0 for _ in range(4)] for _ in range(n)] for _ in range(n)]
visited = [[0 for _ in range(n)] for _ in range(n)]

junction[0][0][1] = 1
visited[0][0] = 1

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

for time in range(t):
    for row in range(n):
        for col in range(n):
            for inDir in range(4):
                if junction[row][col][inDir] == 1:
                    sig = signal[row][col][time % 4]

                    for outDir in range(4):
                        if signalInfo[sig][inDir][outDir] == 1:
                            nr = row + dx[outDir]
                            nc = col + dy[outDir]

                            if 0 <= nr < n and 0 <= nc < n:
                                junction2[nr][nc][(outDir + 2) % 4] = 1
                                visited[nr][nc] = 1

                    junction[row][col][inDir] = 0

    junction, junction2 = junction2, junction

count = 0

for row in range(n):
    for col in range(n):
        if visited[row][col] == 1:
            count += 1

print(count)
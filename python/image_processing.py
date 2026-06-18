#이미지프로세싱

# #dfs 문제인듯
#(x,y,c) 입력 받으면 (x,y)에서 상하좌우에 동일한 색상인 블럭을 전부 c색깔로 변경하는문제
#재귀함수로 탐색해서 같은 색깔 찾기
import sys
sys.setrecursionlimit(10**5)

def color(x,y,c):
    oldc = image[x][y]
    image[x][y] = c
    if image[x+1][y] == oldc:
        color(x+1,y,c)
    if image[x][y+1] == oldc:
        color(x,y+1,c)
    if image[x-1][y] == oldc:
        color(x-1,y,c)
    if image[x][y-1] == oldc:
        color(x,y-1,c)

h,w =map(int, input().split())
image = [[0]*(w+2)] #0번째 행은 0으로 초기화
for i in range(h): #좌표값 활용을 위해서 0인덱스 삭제 
    temp =list(map(int, input().split()))
    image.append([0]+temp+[0])
image.append([0]*(w+2))
q = int(input())

for i in range(q):
    x,y,c = map(int, input().split())
    color(x,y,c)
    
for i in range(1,h+1):
    for j in range(1,w+1):
        print(image[i][j],end=' ')
    print()